#pragma once

#include <memory>
#include <string>

#include "bus.h"
#include "cartridge.h"
#include "cpu.h"
#include "gfx/ppu.h"
#include "io.h"
#include "utils/common.h"

constexpr int T_CYCLES_PER_M_CYCLES = 4;

class Gameboy {
   public:
    Gameboy(Cartridge& cartridge);

    void Init();
    void Step();

    /* Getters */
    bool IsRunning() const { return m_Running; }
    bool IsPaused() const { return m_Paused; }
    u32 GetTicks() const { return m_Ticks; }
    std::string_view GetLoadedGame() const;
    Bus* GetBus() const { return m_Bus.get(); }
    PPU* GetPPU() const { return m_IO->GetPPU(); }

    void VerboseLog(bool enable);
    static void InitLog();

   private:
    bool m_Running;
    bool m_Paused;
    u32 m_Ticks;
    Cartridge& m_Cartridge;
    std::unique_ptr<CPU> m_CPU;
    std::unique_ptr<Bus> m_Bus;
    std::unique_ptr<IO> m_IO;

    void HandleAsyncExit();
    static void signal_callback_handler(int signum);
};