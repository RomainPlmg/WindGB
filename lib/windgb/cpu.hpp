#pragma once

#include <array>
#include <cstdint>

#include "interrupt.hpp"
#include "registers.hpp"

namespace WindGB {

class Instruction;
class Bus;
class IO;

class CPU {
   public:
    explicit CPU(Bus& bus, IO& io);

    void init();
    uint32_t step();

    uint8_t fetch8();
    uint16_t fetch16();
    uint8_t pop8();
    uint16_t pop16();
    void push8(uint8_t data);
    void push16(uint16_t data);

    void request_ime_en() { request_ime_en_ = true; }

    InterruptHandler& get_interrupt_handler() { return interrupt_handler_; }
    void halt() { halted_ = true; }

    Registers regs;

   private:
    Bus& bus_;
    InterruptHandler interrupt_handler_;

    bool request_ime_en_ = false;
    bool halted_ = false;
    bool halt_bug_ = false;

    bool handle_interrupts();
};

}  // namespace WindGB