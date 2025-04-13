#include "cpu.h"

#include "memory.h"
#include "opcodes.h"
#include "registers.h"
#include "utils/Logger.h"  // FOR DEBUG

CPU::CPU(Memory& memory) : m_Memory(memory), m_Cycles(0) { m_Registers = std::make_unique<Registers>(); }

CPU::~CPU() {}

uint8_t CPU::Fetch8() {
    uint16_t value = m_Memory.Read(m_Registers->PC);
    m_Registers->PC++;
    return value;
}

uint16_t CPU::Fetch16() {
    uint16_t low = Fetch8();
    uint16_t high = Fetch8();
    return (high << 8) | low;
}

uint8_t CPU::Pop8Stack() { return m_Memory.Read(m_Registers->SP++); }

uint16_t CPU::Pop16Stack() {
    uint8_t low = m_Memory.Read(m_Registers->SP++);
    uint8_t high = m_Memory.Read(m_Registers->SP++);

    return (high << 8) | low;
}

void CPU::Push8Stack(uint8_t value) { m_Memory.Write(--m_Registers->SP, value); }

void CPU::Push16Stack(uint16_t value) {
    uint8_t high = (value >> 8) & 0xFF;
    uint8_t low = value & 0xFF;

    m_Memory.Write(--m_Registers->SP, high);
    m_Memory.Write(--m_Registers->SP, low);
}

void CPU::RunNextInstruction() {
    sf::Time time = m_Clock.getElapsedTime();
    if (time.asMicroseconds() >= CPU_PERIOD_US) {
        uint8_t opcode = Fetch8();
        DecodeInstruction(opcode);
        m_Clock.restart();

        // Print the instruction
        LOG_TRACE("Run \'{0}\' at address {1}", opcodeTable[opcode].name, m_Registers->PC);
    }
}

void CPU::AddCycles(uint64_t cycles) { m_Cycles += cycles; }

void CPU::Reset() {
    // Init registers
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

    m_Halted = false;
    m_IME = false;
}

Registers* CPU::GetRegisters() { return m_Registers.get(); }

Memory& CPU::GetMemory() { return m_Memory; }

void CPU::DecodeInstruction(uint8_t opcode) { opcodeTable[opcode].Execute(*this); }