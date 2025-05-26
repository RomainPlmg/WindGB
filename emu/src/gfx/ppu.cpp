#include "ppu.h"

#include "core/io_reg.h"
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
}

void PPU::Init() {
    m_CurrentMode = Mode::OAMSCAN;
    m_ModeClock = 0;
    m_LY = 0;
}

void PPU::Step(u8 cycles) {
    m_ModeClock += cycles;

    // The PPU state machine
    switch (m_CurrentMode) {
        case Mode::HBLANK:
            if (m_ModeClock >= PPU_HBLANK_CYCLES) {
                m_ModeClock -= PPU_HBLANK_CYCLES;
                m_LY++;
                if (m_LY == PPU_NB_LCD_SCANLINES) {  // All 144 scanlines have been drawn, swith to 10 VBLANK scanlines
                    m_CurrentMode = Mode::VBLANK;
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
                    m_CurrentMode = Mode::OAMSCAN;
                }
            }
            break;

        case Mode::OAMSCAN:
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
    // Get scroll registers for background
    u8 SCX = m_Bus.Read(LCD_SCX_ADDR);
    u8 SCY = m_Bus.Read(LCD_SCY_ADDR);

    // Get LCD Control register
    u8 LCDC = m_Bus.Read(IO_REG_LCD_START);

    // Control bits
    bool bgTileMap = GET_BIT(LCDC, LCDC_BG_TILE_MAP);  // Background use Tilemap1 or Tilemap2

    u8 bgY = (SCY + m_LY) % 256;  // The offset of the scanline to draw in the background tilemap
    u8 tileY = bgY / TILE_WIDTH;
    tileY %= 32;

    for (int x = 0; x < 160; x++) {  // For each pixel
        u8 bgX = (SCX + x) % 256;
        u8 tileX = bgX / TILE_WIDTH;
        tileX %= 32;
        TileMap* tileMap = bgTileMap ? m_TileMap2.get() : m_TileMap1.get();
        Tile tile = tileMap->GetTile(tileX, tileY);
        u8* p_tileFramebuffer = tile.GetFramebuffer();

        u8 pixelX = bgX % TILE_WIDTH;
        u8 pixelY = bgY % TILE_WIDTH;
        u8 pixelID = *(p_tileFramebuffer + pixelX + pixelY * TILE_WIDTH);

        u32 fbIndex = (x + m_LY * 160) * 4;

        const auto& color = GB_COLORS[pixelID];
        m_FrameBuffer[fbIndex + 0] = color[0];
        m_FrameBuffer[fbIndex + 1] = color[1];
        m_FrameBuffer[fbIndex + 2] = color[2];
        m_FrameBuffer[fbIndex + 3] = color[3];
    }
    LOG_INFO("Finish scanline");
}
