#include "cpu.h"

#include <iostream>

#include "bus.h"
#include "instructions.h"
#include "registers.h"
#include "utils/log.h"

CPU::CPU(Bus& memBus) : m_Bus(memBus) {
    m_Registers = std::make_unique<Registers>();
    m_Interrupt = std::make_unique<InterruptHandler>(memBus);
}

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
    m_Interrupt->SetIME(false);
    m_EnableIMECountdown = -1;
    m_Halted = false;
}

int CPU::Step() {
    if (m_Halted) {
        if (m_Interrupt->HasPending()) {
            m_Halted = false;
            if (!m_Interrupt->GetIME()) m_Cycles++;
        } else {
            return 1;
        }
    }

    // Gameboy Doctor log
    GBD_LOG_DEBUG("A:{:02x} F:{:02x} B:{:02x} C:{:02x} D:{:02x} E:{:02x} H:{:02x} L:{:02x} SP:{:04x} PC:{:04x} PCMEM:{:02x},{:02x},{:02x},{:02x}",
                  m_Registers->A, m_Registers->F, m_Registers->B, m_Registers->C, m_Registers->D, m_Registers->E, m_Registers->H, m_Registers->L,
                  m_Registers->SP, m_Registers->PC, m_Bus.Read(m_Registers->PC), m_Bus.Read(m_Registers->PC + 1), m_Bus.Read(m_Registers->PC + 2),
                  m_Bus.Read(m_Registers->PC + 3));

    // Interrupt handler
    HandleInterrupts();

    // Fetch the next opcode
    u8 opcode = Fetch8();
    Instruction curInst = InstructionTable[opcode];
    if (opcode == 0xCB) {  // Prefix instructions, fetch the next instruction in the same step
        opcode = Fetch8();
        curInst = PrefixInstructionTable[opcode];
    }

    LOG_DEBUG("Executing instruction '{}'\tPC = 0x{:02X}", curInst.name, m_Registers->PC);

    u32 oldCycles = m_Cycles;       // Save the nb of cycles before the instruction
    curInst.Execute(*this, m_Bus);  // Run the instruction

    // For EI instruction, enable interrupt flag after the next instruction
    if (m_EnableIMECountdown > 0) {
        m_EnableIMECountdown--;
        if (m_EnableIMECountdown == 0) {
            m_Interrupt->SetIME(true);
        }
    }

    // Return T-Cycles AND NOT M-Cycles !!! (1 M-Cycle = 4 T-Cycles)
    return (m_Cycles - oldCycles) * 4;
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

u16 CPU::GetInterrupVector(u8 id) {
    switch (id) {
        case 0:
            return 0x0040;  // V-Blank
        case 1:
            return 0x0048;  // LCD STAT
        case 2:
            return 0x0050;  // Timer
        case 3:
            return 0x0058;  // Serial
        case 4:
            return 0x0060;  // Joypad
        default:
            LOG_ERROR("{} is an invalid interrupt ID", id);
            return 0x0000;  // Should never happen
    }
}

void CPU::Push8Stack(u8 value) { m_Bus.Write(--m_Registers->SP, value); }

void CPU::Push16Stack(u16 value) {
    u8 high = (value >> 8) & 0xFF;
    u8 low = value & 0xFF;

    m_Bus.Write(--m_Registers->SP, high);
    m_Bus.Write(--m_Registers->SP, low);
}

void CPU::HandleInterrupts() {
    if (m_Interrupt->GetIME() && m_Interrupt->HasPending()) {
        u8 id = m_Interrupt->GetNextPending();
        if (id != 0xFF) {
            Push16Stack(m_Registers->PC);
            m_Interrupt->SetIME(false);
            m_Registers->PC = GetInterrupVector(id);  // Jump to the address of the interrupt handler
            m_Cycles += 5;
        }
    }
}
