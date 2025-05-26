#include "ppu.h"

#include "utils/exit_codes.h"
#include "utils/log.h"

PPU::PPU(Bus& memBus) : m_Bus(memBus) {}

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
                // TODO: Render scanline
                m_CurrentMode = Mode::HBLANK;
            }
            break;

        default:
            LOG_CRITICAL("Unknown PPU mode. Abort.");
            exit(EXIT_INTERNAL_ERROR);
    }
}