#include "cpu.hpp"

#include <array>
#include <cstdint>
#include <iostream>

#include "bus.hpp"
#include "instructions.hpp"
#include "interrupt.hpp"
#include "logger.hpp"

namespace WindGB {

static std::array<uint16_t, 5> INTERRUPT_VECTOR = {0x0040, 0x0048, 0x0050, 0x0058, 0x0060};

CPU::CPU(Bus& bus, IO& io) : bus_(bus), interrupt_handler_(bus, io) {}

void CPU::init() {
    regs.A = 0x01;
    regs.F = 0xB0;
    regs.B = 0x00;
    regs.C = 0x13;
    regs.D = 0x00;
    regs.E = 0xD8;
    regs.H = 0x01;
    regs.L = 0x4D;
    regs.SP = 0xFFFE;
    regs.PC = 0x0000;  // Jump to the boot rom entry point

    interrupt_handler_.ime = false;
    request_ime_en_ = false;
    halted_ = false;

    LOG_INFO("CPU initialized");
}

uint32_t CPU::step() {
    const uint64_t last_tick = bus_.get_tick();

    if (halted_) {
        if (interrupt_handler_.has_pending()) {
            halted_ = false;
            if (!interrupt_handler_.ime) {
                halt_bug_ = true;
                bus_.cycles(1);
                return bus_.get_tick() - last_tick;
            }
        } else {
            bus_.cycles(1);
            return bus_.get_tick() - last_tick;
        }
    }

    if (!handle_interrupts()) {
        uint8_t opcode = bus_.read(regs.PC);
        if (halt_bug_) {
            halt_bug_ = false;
        } else {
            regs.PC++;
        }
        const auto* current_instruction = &instruction_table[opcode];
        if (opcode == 0xCB) {  // Prefix instructions
            opcode = fetch8();
            current_instruction = &prefix_instruction_table[opcode];
        }

        current_instruction->execute(*this, bus_);

        if (request_ime_en_) {
            interrupt_handler_.ime = true;
            request_ime_en_ = false;
        }
    }

    return bus_.get_tick() - last_tick;
}

uint8_t CPU::fetch8() {
    const uint8_t value = bus_.read(regs.PC);
    regs.PC++;
    return value;
}

uint16_t CPU::fetch16() {
    const uint16_t low = fetch8();
    const uint16_t high = fetch8();
    return (high << 8) | low;
}

uint8_t CPU::pop8() { return bus_.read(regs.SP++); }

uint16_t CPU::pop16() {
    const uint8_t low = bus_.read(regs.SP++);
    const uint8_t high = bus_.read(regs.SP++);

    return (high << 8) | low;
}

void CPU::push8(const uint8_t data) { bus_.write(--regs.SP, data); }

void CPU::push16(const uint16_t data) {
    const uint8_t high = (data >> 8) & 0xFF;
    const uint8_t low = data & 0xFF;

    bus_.write(--regs.SP, high);
    bus_.write(--regs.SP, low);
}

bool CPU::handle_interrupts() {
    if (interrupt_handler_.ime && interrupt_handler_.has_pending()) {
        const uint8_t id = interrupt_handler_.get_next_pending();
        bus_.cycles(2);
        if (id != 0xFF) {
            interrupt_handler_.ime = false;
            push16(regs.PC);
            interrupt_handler_.clear_flag(id);
            regs.PC = INTERRUPT_VECTOR[id];
            bus_.cycles(1);
        }
        return true;
    }
    return false;
}

}  // namespace WindGB