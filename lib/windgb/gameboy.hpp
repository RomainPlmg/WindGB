#pragma once

#include "bus.hpp"
#include "cartridge.hpp"
#include "cpu.hpp"
#include "io.hpp"
#include "ppu.hpp"
#include "ram.hpp"
#include "timer.hpp"

namespace WindGB {

class GameBoy {
   public:
    GameBoy();

    void insert(Cartridge* cartridge);
    void init();
    uint32_t step();

    PPU& get_ppu() { return ppu_; }
    IO& get_io() { return io_; }

   private:
    Bus bus_;
    CPU cpu_;
    WRAM wram_;
    HRAM hram_;
    VRAM vram_;
    OAM oam_;
    IO io_;
    Timer timer_;
    PPU ppu_;

    // Components
    Cartridge* cartridge_ = nullptr;  // External component
};

}  // namespace WindGB