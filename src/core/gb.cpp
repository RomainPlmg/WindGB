#include "gb.h"

#include "cpu.h"
#include "ram.h"
#include "registers.h"

GB::GB() {
    m_RAM = std::make_unique<RAM>();
    m_CPU = std::make_unique<CPU>(*m_RAM);
}

GB::~GB() {}

void GB::Run() {
    // Write some data into the memory
    m_RAM->Write(0x100, 0x01);  // Write immediate value into BC
    m_RAM->Write(0x101, 0x34);  // The value MSB
    m_RAM->Write(0x102, 0x12);  // The value LSB

    m_CPU->GetRegisters()->PC = 0x100;  // Place the program counter on 0x100 addr

    // Run instruction
    m_CPU->RunNextInstruction();
    int test = 0;  // Just a debug stop point
}
