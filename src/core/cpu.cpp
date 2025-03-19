#include "cpu.h"

#include "opcodes.h"
#include "ram.h"
#include "registers.h"

CPU::CPU(RAM& memory) : m_RAM(memory) { m_Registers = std::make_unique<Registers>(); }

CPU::~CPU() {}

uint8_t CPU::Fetch8() {
    uint16_t value = m_RAM.Read(m_Registers->PC);
    m_Registers->PC++;
    return value;
}

uint16_t CPU::Fetch16() {
    uint16_t low = Fetch8();
    uint16_t high = Fetch8();
    return (high << 8) | low;
}

void CPU::RunNextInstruction() {
    uint8_t opcode = Fetch8();
    DecodeInstruction(opcode);
}

Registers* CPU::GetRegisters() { return m_Registers.get(); }

RAM& CPU::GetRAM() { return m_RAM; }

void CPU::DecodeInstruction(uint8_t opcode) { opcodeTable[opcode].Execute(*this); }