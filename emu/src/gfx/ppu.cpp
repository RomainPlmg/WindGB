#include "ppu.h"

#include "core/io.h"
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
    m_CurrentMode = Mode::OAMSCAN;
    m_ModeClock = 0;
    m_LY = 0;
    m_TileMap1 = std::make_unique<TileMap>(m_Bus, TILEMAP1_ADDR);
    m_TileMap2 = std::make_unique<TileMap>(m_Bus, TILEMAP2_ADDR);
    m_TileSet = std::make_unique<TileSet>(m_Bus);
    m_FramebufferReady = false;
}

void PPU::Init() {
    m_CurrentMode = Mode::OAMSCAN;
    m_ModeClock = 0;
    m_LY = 0;
}

void PPU::Step(int cycles) {
    m_ModeClock += cycles;

    // The PPU state machine
    switch (m_CurrentMode) {
        case Mode::HBLANK:
            if (m_ModeClock >= PPU_HBLANK_CYCLES) {
                m_ModeClock -= PPU_HBLANK_CYCLES;
                m_LY++;
                if (m_LY == PPU_NB_LCD_SCANLINES) {     // All 144 scanlines have been drawn, swith to 10 VBLANK scanlines
                    m_FrameBuffer = m_TempFrameBuffer;  // Flush the framebuffer
                    m_CurrentMode = Mode::VBLANK;
                    // Set the VBLANK interrupt
                    u8 IF = m_Bus.Read(INTERRUPT_FLAGS_ADDR);
                    IF |= (1 << 0);
                    m_Bus.Write(INTERRUPT_FLAGS_ADDR, IF);
                } else {  // Start to draw the next scanline
                    m_CurrentMode = Mode::OAMSCAN;
                }
            }
            break;

        case Mode::VBLANK:
            if (m_ModeClock >= PPU_SCANLINE_CYCLES) {
                m_ModeClock -= PPU_SCANLINE_CYCLES;
                m_LY++;
                if (m_LY > PPU_NB_SCANLINES - 1) {  // All scanlines have been drawn
                    m_LY = 0;
                    m_FramebufferReady = true;
                    m_CurrentMode = Mode::OAMSCAN;
                }
            }
            break;

        case Mode::OAMSCAN:
            m_FramebufferReady = false;
            if (m_ModeClock >= PPU_OAMSCAN_CYCLES) {
                m_ModeClock -= PPU_OAMSCAN_CYCLES;
                m_CurrentMode = Mode::DRAWING;
            }
            break;

        case Mode::DRAWING:
            if (m_ModeClock >= PPU_DRAWING_CYCLES) {
                m_ModeClock -= PPU_DRAWING_CYCLES;
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

    // Revelant registers
    u8 SCX = m_Bus.Read(LCD_SCX_ADDR);
    u8 SCY = m_Bus.Read(LCD_SCY_ADDR);
    u8 WX = m_Bus.Read(LCD_WX_ADDR);
    u8 WY = m_Bus.Read(LCD_WY_ADDR);
    u8 LCDC = m_Bus.Read(INTERRUPT_FLAGS_ADDR);

    // LCDC bits
    bool bgTileMapSel = GET_BIT(LCDC, LCDC_BG_TILE_MAP);      // Background uses Tilemap1 or Tilemap2
    bool windowEn = GET_BIT(LCDC, LCDC_WINDOW_EN);            // Show window
    bool winTileMapSel = GET_BIT(LCDC, LCDC_WINDOW_TILEMAP);  // Window uses Tilemap1 or Tilemap2

    // Revelant variables for background
    int bgOffsetY = (SCY + m_LY) % 256;                // The offset of the scanline to draw in the background tilemap
    int bgTileCoordY = (bgOffsetY / TILE_WIDTH) % 32;  // Y coordinate of the background tile to print

    // Revelant variables for window
    int winOffsetY = WY;
    int winTileCoordY = ((m_LY - winOffsetY) / TILE_WIDTH) % 32;

    for (int x = 0; x < 160; x++) {  // For each pixel
        // Calculate background tile coordinates X
        int bgOffsetX = (SCX + x) % 256;
        int bgTileCoordX = (bgOffsetX / TILE_WIDTH) % 32;

        // Calculate window tile coordinate X
        int winOffsetX = WX - 7;
        int winTileCoordX = ((x - winOffsetX) / TILE_WIDTH) % 32;

        // Recover the correct tilemap
        int tileCoordX = bgTileCoordX;
        int tileCoordY = bgTileCoordY;
        int offsetX = bgOffsetX;
        int offsetY = bgOffsetY;
        int pixelX = offsetX % TILE_WIDTH;
        int pixelY = offsetY % TILE_WIDTH;
        TileMap* tileMap = bgTileMapSel ? m_TileMap2.get() : m_TileMap1.get();

        if (windowEn && m_LY >= WY && x >= WX - 7) {  // LCD is parsing the window & not the background
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
