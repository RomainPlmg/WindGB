#pragma once

#include <memory>
#include <string>

#include "bus.h"
#include "cartridge.h"
#include "cpu.h"
#include "gfx/ppu.h"
#include "timer.h"
#include "utils/common.h"

struct GameboyContext {};

class Gameboy {
   public:
    Gameboy(int argc, char const* argv[]);
    void Init();
    void Step();

    /* Getters */
    bool IsRunning() const { return m_Running; }
    bool IsPaused() const { return m_Paused; }
    u32 GetTicks() const { return m_Ticks; }
    std::string_view GetLoadedGame() const;
    Bus* GetBus() const { return m_Bus.get(); }
    PPU* GetPPU() const { return m_PPU.get(); }

   private:
    bool m_Running;
    bool m_Paused;
    u32 m_Ticks;
    std::unique_ptr<Cartridge> m_Cartridge;
    std::unique_ptr<CPU> m_CPU;
    std::unique_ptr<PPU> m_PPU;
    std::unique_ptr<Timer> m_Timer;
    std::unique_ptr<Bus> m_Bus;

    void HandleAsyncExit();
    static void signal_callback_handler(int signum);
};