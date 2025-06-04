#pragma once

#include <array>
#include <memory>

#include "timer.h"
#include "gfx/ppu.h"
#include "utils/common.h"

class IO {
   public:
    IO(Bus& memBus);

    void Reset();

    u8 Read(u16 addr) const;
    const u8* GetPointerTo(u16 address) const;
    void Write(u16 addr, u8 data);

    /* Getters */
    Timer* GetTimer() { return m_Timer.get(); }
    PPU* GetPPU() { return m_PPU.get(); }

   private:
    Bus& m_Bus;
    std::unique_ptr<Timer> m_Timer;
    std::unique_ptr<PPU> m_PPU;
    std::array<u8, 0x80> m_Data;
};