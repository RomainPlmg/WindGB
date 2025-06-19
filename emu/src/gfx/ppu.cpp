#include "ppu.h"

#include "events/EventApp.h"
#include "tile.h"
#include "utils/exit_codes.h"
#include "utils/log.h"

static constexpr std::array<std::array<u8, 4>, 4> GB_COLORS = {{
    {224, 248, 208, 255},  // color_id = 0
    {136, 192, 112, 255},  // color_id = 1
    {52, 104, 86, 255},    // color_id = 2
    {8, 24, 32, 255},      // color_id = 3
}};

PPU::PPU(Bus& memBus, EventBus& eventBus) : m_Bus(memBus), m_EventBus(eventBus) {
    m_TileMap1 = std::make_unique<TileMap>(m_Bus, TILEMAP1_ADDR);
    m_TileMap2 = std::make_unique<TileMap>(m_Bus, TILEMAP2_ADDR);
    m_TileSet = std::make_unique<TileSet>(m_Bus);
}

void PPU::Reset() {
    m_CurrentMode = Mode::OAMSCAN;
    m_ModeClock = 0;
    m_WindowLineCounter = 0;

    // Registers
    m_LCDC = 0;
    m_STAT = 0;
    m_SCY = 0;
    m_SCX = 0;
    m_LY = 0;
    m_LYC = 0;
    m_DMA = 0;
    m_BGP = 0;
    m_OBP0 = 0;
    m_OBP1 = 0;
    m_WY = 0;
    m_WX = 0;

    m_FramebufferReady = false;
}

void PPU::Step() {
    if (const bool ppu_enable = GET_BIT(m_LCDC, 7); !ppu_enable) {
        m_ModeClock = 0;
        m_LY = 0;
        m_WindowLineCounter = 0;
        m_CurrentMode = Mode::HBLANK;
        return;
    }

    m_ModeClock++;

    u8 old_LY = m_LY;

    // The PPU state machine
    switch (m_CurrentMode) {
        case Mode::HBLANK:
            if (m_ModeClock == PPU_HBLANK_CYCLES) {
                m_ModeClock = 0;
                IncrementLY();
                if (m_LY == PPU_NB_LCD_SCANLINES) {  // All 144 scanlines have been drawn, switch to 10 VBLANK scanlines
                    m_WindowLineCounter = 0;
                    m_FrameBuffer = m_TempFrameBuffer;  // Flush the framebuffer
                    m_CurrentMode = Mode::VBLANK;
                    m_FramebufferReady = true;
                    // Set the VBLANK interrupt
                    u8 IF = m_Bus.Read(REG_IF_ADDR);
                    IF |= (1 << 0);
                    m_Bus.Write(REG_IF_ADDR, IF);
                } else {  // Start to draw the next scanline
                    m_CurrentMode = Mode::OAMSCAN;
                    UpdateWindowLineCounter();
                }
            }
            break;

        case Mode::VBLANK:
            if (m_ModeClock == PPU_SCANLINE_CYCLES) {
                m_ModeClock = 0;
                IncrementLY();
                if (m_LY > PPU_NB_SCANLINES - 1) {  // All scanlines have been drawn
                    m_LY = 0;
                    m_CurrentMode = Mode::OAMSCAN;
                }
            }
            break;

        case Mode::OAMSCAN:
            if (m_ModeClock == PPU_OAMSCAN_CYCLES) {
                m_ModeClock = 0;
                EvaluateSprites();
                m_CurrentMode = Mode::DRAWING;
            }
            break;

        case Mode::DRAWING:
            if (m_ModeClock == PPU_DRAWING_CYCLES) {
                m_ModeClock = 0;
                RenderScanline();
                m_CurrentMode = Mode::HBLANK;
            }
            break;

        default:
            LOG_CRITICAL("Unknown PPU mode. Abort.");
            exit(EXIT_INTERNAL_ERROR);
    }
}

void PPU::RenderScanline() {
    m_TileSet->Update();

    // m_LCDC bits
    const bool bg_enable = GET_BIT(m_LCDC, 0);             // Background enable
    const bool obj_enable = GET_BIT(m_LCDC, 1);            // Objects enable
    const u8 sprite_height = GET_BIT(m_LCDC, 2) ? 16 : 8;  // Sprite size if 8px or 16px
    const bool bg_tilemap_sel = GET_BIT(m_LCDC, 3);        // Background uses Tilemap1 or Tilemap2
    const bool win_enable = GET_BIT(m_LCDC, 5);            // Show window
    const bool win_tilemap_sel = GET_BIT(m_LCDC, 6);       // Window uses Tilemap1 or Tilemap2

    // Relevant variables for background
    const int bg_offset_y = (m_SCY + m_LY) % 256;           // The offset of the scanline to draw in the background tilemap
    const int bg_tile_y = (bg_offset_y / TILE_WIDTH) % 32;  // Y coordinate of the background tile to print

    // Relevant variables for window
    const int win_offset_y = m_WY;
    const int win_tile_y = (m_WindowLineCounter / TILE_WIDTH) % 32;
    int offset_y = bg_offset_y;
    int tile_y = bg_tile_y;
    int pixel_y = offset_y % TILE_WIDTH;

    // === BG/WINDOW DRAWING ===
    u8 pixel_id = 0;
    for (int x = 0; x < 160; x++) {  // For each pixel
        const u32 framebuffer_index = (x + m_LY * 160) * 4;
        if (bg_enable) {
            // Calculate background tile coordinates X
            const int bg_offset_x = (m_SCX + x) % 256;
            const int bg_tile_x = (bg_offset_x / TILE_WIDTH) % 32;

            // Calculate window tile coordinate X
            const int win_offset_x = m_WX - 7;
            const int win_tile_x = ((x - win_offset_x) / TILE_WIDTH) % 32;

            // Recover the correct tilemap
            int tile_x = bg_tile_x;
            int offset_x = bg_offset_x;
            int pixel_x = offset_x % TILE_WIDTH;
            TileMap* tile_map = bg_tilemap_sel ? m_TileMap2.get() : m_TileMap1.get();

            if (win_enable && m_LY >= m_WY && x >= m_WX - 7) {  // LCD is parsing the window & not the background
                tile_map = win_tilemap_sel ? m_TileMap2.get() : m_TileMap1.get();
                tile_x = win_tile_x;
                tile_y = win_tile_y;
                offset_x = win_offset_x;
                offset_y = win_offset_y;
                pixel_x = (x - offset_x) % TILE_WIDTH;
                pixel_y = (m_LY - offset_y) % TILE_WIDTH;
            }

            const u16 tile_addr = tile_map->GetTileAddr(tile_x, tile_y);
            const Tile* p_tile = m_TileSet->GetTile(tile_addr);

            // Recover the pixels in the tile
            const u8* tile_data = p_tile->GetData();
            pixel_id = *(tile_data + pixel_x + pixel_y * TILE_WIDTH);
        }

        // Populate the framebuffer
        const u8 color_id = (m_BGP >> (pixel_id * 2)) & 0x03;
        const auto& color = GB_COLORS[color_id];
        m_TempFrameBuffer[framebuffer_index + 0] = color[0];
        m_TempFrameBuffer[framebuffer_index + 1] = color[1];
        m_TempFrameBuffer[framebuffer_index + 2] = color[2];
        m_TempFrameBuffer[framebuffer_index + 3] = color[3];
    }

    // === SPRITES DRAWING ===
    if (!obj_enable) return;
    for (const auto& sprite : m_ScanlineSprites) {
        u8 sprite_y = m_LY + (sprite.y - 16);  // The relative scanline of the sprite
    }
}

void PPU::EvaluateSprites() {
    m_ScanlineSprites.clear();  // Remove all sprites for the new scanline

    const u16 sprite_height = GET_BIT(m_LCDC, 2) ? 16 : 8;
    u32 sprite_count = 0;

    for (u16 i = 0; i < 40; i++) {                    // OAM store up to 40 sprites
        const u16 oam_addr = OAM_ADDR_START + i * 4;  // OAM sprite takes 4 bytes in memory

        // Recover sprite data
        const u8 y = m_Bus.Read(oam_addr);
        const u8 x = m_Bus.Read(oam_addr + 1);
        const u8 tile = m_Bus.Read(oam_addr + 2);
        const u8 attr = m_Bus.Read(oam_addr + 3);

        // Check if the scanline intercept the sprite position
        if (m_LY >= y - 16 && m_LY < y - 16 + sprite_height) {
            Sprite sprite(x, y, tile);
            sprite.bg_priority = GET_BIT(attr, 7);
            sprite.y_flip = GET_BIT(attr, 6);
            sprite.x_flip = GET_BIT(attr, 5);
            sprite.palette = GET_BIT(attr, 4);
            sprite.oam_addr = oam_addr;

            m_ScanlineSprites.push_back(sprite);
            sprite_count++;

            if (sprite_count == 10) break;  // Max 10 sprites per scanline
        }
    }

    // Sort sprites by X growing
    std::sort(m_ScanlineSprites.begin(), m_ScanlineSprites.end(), [](const Sprite& a, const Sprite& b) { return a.x < b.x; });
}

void PPU::IncrementLY() {
    if (m_LY < PPU_NB_SCANLINES) m_LY++;
    // LCD STAT
    if (m_LY == m_LYC) {
        m_STAT |= (1 << 2);
        if (GET_BIT(m_STAT, 6)) {
            u8 IF = m_Bus.Read(REG_IF_ADDR);
            IF |= (1 << 1);
            m_Bus.Write(REG_IF_ADDR, IF);
        }
    } else {
        m_STAT &= ~(1 << 2);
    }
}
void PPU::UpdateWindowLineCounter() {
    if (GET_BIT(m_LCDC, 5) && m_LY > m_WY && m_WX <= 166) {
        m_WindowLineCounter++;
    }
}

u8 PPU::Read(u16 addr) const {
    switch (addr) {
        case REG_LCDC_ADDR:
            return m_LCDC;
        case REG_STAT_ADDR:
            return m_STAT;
        case REG_SCY_ADDR:
            return m_SCY;
        case REG_SCX_ADDR:
            return m_SCX;
        case REG_LY_ADDR:
            return m_LY;
        case REG_LYC_ADDR:
            return m_LYC;
        case REG_DMA_ADDR:
            return m_DMA;
        case REG_BGP_ADDR:
            return m_BGP;
        case REG_OBP0_ADDR:
            return m_OBP0;
        case REG_OBP1_ADDR:
            return m_OBP1;
        case REG_WY_ADDR:
            return m_WY;
        case REG_WX_ADDR:
            return m_WX;

        default:
            LOG_ERROR("Invalid addr {:02X} for PPU read.", addr);
            return 0xFF;
    }
}

void PPU::Write(u16 addr, u8 data) {
    switch (addr) {
        case REG_LCDC_ADDR:
            m_LCDC = data;
            break;
        case REG_STAT_ADDR:
            m_STAT = data;
            break;
        case REG_SCY_ADDR:
            m_SCY = data;
            break;
        case REG_SCX_ADDR:
            m_SCX = data;
            break;
        case REG_LY_ADDR:
            LOG_ERROR("Cannot write into LY register, read-only.");
            break;
        case REG_LYC_ADDR:
            m_LYC = data;
            break;
        case REG_DMA_ADDR: {
            m_DMA = data;
            // Start DMA transfer from data * 0x100 to 0xFE00
            m_EventBus.Send(DMATransfertEvent(data * 0x100));
        } break;
        case REG_BGP_ADDR:
            m_BGP = data;
            break;
        case REG_OBP0_ADDR:
            m_OBP0 = data;
            break;
        case REG_OBP1_ADDR:
            m_OBP1 = data;
            break;
        case REG_WY_ADDR:
            m_WY = data;
            break;
        case REG_WX_ADDR:
            m_WX = data;
            break;

        default:
            LOG_ERROR("Invalid addr {:02X} for PPU read.", addr);
            break;
    }
}

bool PPU::ConsumeFrameBufferFlag() {
    if (m_FramebufferReady) {
        m_FramebufferReady = false;
        return true;
    }
    return false;
}
