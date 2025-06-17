#include "ppu.h"

#include "tile.h"
#include "utils/exit_codes.h"
#include "utils/log.h"

static constexpr std::array<std::array<u8, 4>, 4> GB_COLORS = {{
    {37, 37, 37, 255},     // colorID = 0
    {70, 70, 70, 255},     // colorID = 1
    {130, 130, 130, 255},  // colorID = 2
    {180, 180, 180, 255}   // colorID = 3
}};

PPU::PPU(Bus& memBus) : m_Bus(memBus) {
    m_TileMap1 = std::make_unique<TileMap>(m_Bus, TILEMAP1_ADDR);
    m_TileMap2 = std::make_unique<TileMap>(m_Bus, TILEMAP2_ADDR);
    m_TileSet = std::make_unique<TileSet>(m_Bus);
}

void PPU::Reset() {
    m_CurrentMode = Mode::OAMSCAN;
    m_ModeClock = 0;
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
    m_ModeClock++;

    // The PPU state machine
    switch (m_CurrentMode) {
        case Mode::HBLANK:
            if (m_ModeClock == PPU_HBLANK_CYCLES) {
                m_ModeClock = 0;
                m_LY++;
                if (m_LY == PPU_NB_LCD_SCANLINES) {     // All 144 scanlines have been drawn, swith to 10 VBLANK scanlines
                    m_FrameBuffer = m_TempFrameBuffer;  // Flush the framebuffer
                    m_CurrentMode = Mode::VBLANK;
                    m_FramebufferReady = true;
                    // Set the VBLANK interrupt
                    u8 IF = m_Bus.Read(REG_IF_ADDR);
                    IF |= (1 << 0);
                    m_Bus.Write(REG_IF_ADDR, IF);
                } else {  // Start to draw the next scanline
                    m_CurrentMode = Mode::OAMSCAN;
                }
            }
            break;

        case Mode::VBLANK:
            if (m_ModeClock == PPU_SCANLINE_CYCLES) {
                m_ModeClock = 0;
                m_LY++;
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
    bool bgTileMapSel = GET_BIT(m_LCDC, 3);   // Background uses Tilemap1 or Tilemap2
    bool windowEn = GET_BIT(m_LCDC, 5);       // Show window
    bool winTileMapSel = GET_BIT(m_LCDC, 6);  // Window uses Tilemap1 or Tilemap2

    // Revelant variables for background
    int bgOffsetY = (m_SCY + m_LY) % 256;              // The offset of the scanline to draw in the background tilemap
    int bgTileCoordY = (bgOffsetY / TILE_WIDTH) % 32;  // Y coordinate of the background tile to print

    // Revelant variables for window
    int winOffsetY = m_WY;
    int winTileCoordY = ((m_LY - winOffsetY) / TILE_WIDTH) % 32;

    // === BG/WINDOW DRAWING ===
    for (int x = 0; x < 160; x++) {  // For each pixel
        // Calculate background tile coordinates X
        int bgOffsetX = (m_SCX + x) % 256;
        int bgTileCoordX = (bgOffsetX / TILE_WIDTH) % 32;

        // Calculate window tile coordinate X
        int winOffsetX = m_WX - 7;
        int winTileCoordX = ((x - winOffsetX) / TILE_WIDTH) % 32;

        // Recover the correct tilemap
        int tileCoordX = bgTileCoordX;
        int tileCoordY = bgTileCoordY;
        int offsetX = bgOffsetX;
        int offsetY = bgOffsetY;
        int pixelX = offsetX % TILE_WIDTH;
        int pixelY = offsetY % TILE_WIDTH;
        TileMap* tileMap = bgTileMapSel ? m_TileMap2.get() : m_TileMap1.get();

        if (windowEn && m_LY >= m_WY && x >= m_WX - 7) {  // LCD is parsing the window & not the background
            tileMap = winTileMapSel ? m_TileMap2.get() : m_TileMap1.get();
            tileCoordX = winTileCoordX;
            tileCoordY = winTileCoordY;
            offsetX = winOffsetX;
            offsetY = winOffsetY;
            pixelX = (x - offsetX) % TILE_WIDTH;
            pixelY = (m_LY - offsetY) % TILE_WIDTH;
        }

        u16 tileAddr = tileMap->GetTileAddr(tileCoordX, tileCoordY);
        const Tile* p_tile = m_TileSet->GetTile(tileAddr);

        // Recover the pixel in the tile

        const u8* tileData = p_tile->GetData();
        u8 pixelID = *(tileData + pixelX + pixelY * TILE_WIDTH);

        // Populate the framebuffer
        u32 fbIndex = (x + m_LY * 160) * 4;
        const auto& color = GB_COLORS[pixelID];
        m_TempFrameBuffer[fbIndex + 0] = color[0];
        m_TempFrameBuffer[fbIndex + 1] = color[1];
        m_TempFrameBuffer[fbIndex + 2] = color[2];
        m_TempFrameBuffer[fbIndex + 3] = color[3];
    }
}

void PPU::EvaluateSprites() {
    m_ScanlineSprites.clear();  // Remove all sprites for the new scanline

    const bool sprite_height = GET_BIT(m_LCDC, 2) ? 16 : 8;
    u32 sprite_count = 0;

    for (u16 i = 0; i < 40; i++) {              // Max 40 sprite per scanline
        u16 oam_addr = OAM_ADDR_START + i * 4;  // OAM sprite takes 4 bytes in memory

        // Recover sprite data
        u8 y = m_Bus.Read(oam_addr);
        u8 x = m_Bus.Read(oam_addr + 1);
        u8 tile = m_Bus.Read(oam_addr + 2);
        u8 attr = m_Bus.Read(oam_addr + 3);

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

    // Optional: Sort sprites by X growing
    std::sort(m_ScanlineSprites.begin(), m_ScanlineSprites.end(), [](const Sprite& a, const Sprite& b) { return a.x < b.x; });
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
        case REG_DMA_ADDR:
            m_DMA = data;
            break;
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
