#include "gameboy.hpp"

#include "common.hpp"
#include "logger.hpp"
#include "ppu.hpp"
#include "timer.hpp"

namespace WindGB {

GameBoy::GameBoy() : cpu_(bus_, io_), timer_(bus_, io_), ppu_(bus_, io_) {}

void GameBoy::insert(Cartridge* cartridge) { cartridge_ = cartridge; }

void GameBoy::init() {
    bus_.link(cartridge_, 0x0000, 0x7FFF, "Cartridge ROM");
    bus_.link(cartridge_, 0xA000, 0xBFFF, "Cartridge RAM");
    bus_.link(&wram_, WRAM_ADDR_START, WRAM_ADDR_END, "WRAM");
    bus_.link(&wram_, WRAM_ECHO_ADDR_START, WRAM_ECHO_ADDR_END, "Echo WRAM", 0x2000);
    bus_.link(&hram_, HRAM_ADDR_START, HRAM_ADDR_END, "HRAM");
    bus_.link(&vram_, VRAM_ADDR_START, VRAM_ADDR_END, "VRAM");
    bus_.link(&oam_, OAM_ADDR_START, OAM_ADDR_END, "OAM");
    bus_.link(&io_, IO_ADDR_START, IO_ADDR_END, "IO");

    bus_.link_ppu(&ppu_);
    bus_.link_timer(&timer_);

    cpu_.init();
    ppu_.init();
    timer_.init();

    LOG_INFO(bus_.memap_to_string());
    LOG_INFO("Gameboy initialized");
}

uint32_t GameBoy::step() { return cpu_.step(); }

}  // namespace WindGB