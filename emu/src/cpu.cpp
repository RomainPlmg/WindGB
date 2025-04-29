#include "cpu.h"

#include <iostream>

#include "bus.h"
#include "instructions.h"
#include "log.h"
#include "registers.h"

CPU::CPU(Bus& memBus) : m_Bus(memBus) { m_Registers = std::make_unique<Registers>(); }

void CPU::Reset() {  // Init registers
    // LOG_INFO("Reset CPU");
    m_Registers->A = 0x01;
    m_Registers->F = 0xB0;  // Flag Z = 1
    m_Registers->B = 0x00;
    m_Registers->C = 0x13;
    m_Registers->D = 0x00;
    m_Registers->E = 0xD8;
    m_Registers->H = 0x01;
    m_Registers->L = 0x4D;
    m_Registers->SP = 0xFFFE;
    m_Registers->PC = 0x0100;  // Jump to the game entry point

    m_Cycles = 0;
    m_IME = false;
    m_EnableIMEAfterInstruction = false;
    m_Halted = false;
}

void CPU::Step() {
    if (!m_Halted) {
        if (m_IME && (m_Bus.Read(IO_REG_INTERRUPT_FLAGS) & m_Bus.Read(INTERRUPT_ENABLE_ADDR))) {
            LOG_INFO("Interrupt !!!");
        }

        u16 debugPC = m_Registers->PC;

        u8 opcode = Fetch8();
        Instruction curInst = InstructionTable[opcode];
        if (opcode == 0xCB) {
            opcode = Fetch8();
            curInst = PrefixInstructionTable[opcode];
        }

        LOG_DEBUG("Executing instruction '{}'\tPC = 0x{:02X}", curInst.name, m_Registers->PC);
        GBD_LOG_DEBUG("A:{:02x} F:{:02x} B:{:02x} C:{:02x} D:{:02x} E:{:02x} H:{:02x} L:{:02x} SP:{:04x} PC:{:04x} PCMEM:{:02x},{:02x},{:02x},{:02x}",
                  m_Registers->A, m_Registers->F, m_Registers->B, m_Registers->C, m_Registers->D, m_Registers->E, m_Registers->H, m_Registers->L,
                  m_Registers->SP, debugPC, m_Bus.Read(debugPC), m_Bus.Read(debugPC + 1), m_Bus.Read(debugPC + 2), m_Bus.Read(debugPC + 3));

        curInst.Execute(*this, m_Bus);

        // For EI instruction, enable interrupt flag after the instruction was executed
        if (m_EnableIMEAfterInstruction) {
            SetIME(true);
            m_EnableIMEAfterInstruction = false;
        }
    }
}

u8 CPU::Fetch8() {
    u8 value = m_Bus.Read(m_Registers->PC);
    m_Registers->PC++;
    return value;
}

u16 CPU::Fetch16() {
    u16 low = Fetch8();
    u16 high = Fetch8();
    return (high << 8) | low;
}

u8 CPU::Pop8Stack() { return m_Bus.Read(m_Registers->SP++); }

u16 CPU::Pop16Stack() {
    u8 low = m_Bus.Read(m_Registers->SP++);
    u8 high = m_Bus.Read(m_Registers->SP++);

    return (high << 8) | low;
}

void CPU::Push8Stack(u8 value) { m_Bus.Write(--m_Registers->SP, value); }

void CPU::Push16Stack(u16 value) {
    u8 high = (value >> 8) & 0xFF;
    u8 low = value & 0xFF;

    m_Bus.Write(--m_Registers->SP, high);
    m_Bus.Write(--m_Registers->SP, low);
}

void CPU::HandleInterrupts() {}
