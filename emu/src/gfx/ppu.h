#pragma once

#include "utils/common.h"
#include "core/bus.h"


constexpr u32 PPU_SCANLINE_CYCLES = 456;
constexpr u32 PPU_OAMSCAN_CYCLES = 80;
constexpr u32 PPU_DRAWING_CYCLES = 172;
constexpr u32 PPU_HBLANK_CYCLES = PPU_SCANLINE_CYCLES - PPU_OAMSCAN_CYCLES - PPU_DRAWING_CYCLES;
constexpr u32 PPU_NB_SCANLINES = 154;
constexpr u32 PPU_NB_LCD_SCANLINES = 144;

class PPU {
   public:
    PPU(Bus& memBus);
    enum class Mode { HBLANK = 0, VBLANK, OAMSCAN, DRAWING };

    void Init();
    void Step(u8 cycles);

   private:
    Mode m_CurrentMode;
    u32 m_ModeClock;
    u32 m_LY;
    Bus& m_Bus;
};