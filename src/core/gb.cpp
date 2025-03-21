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
    m_RAM->Write(0x000D, 0x18);  // Jump relative with signed e8 value
    m_RAM->Write(0x000E, 0x02);  // e8 value

    m_CPU->GetRegisters()->PC = 0x00D;  // Place the program counter on 0x00D addr

    // Run instruction
    m_CPU->RunNextInstruction();
}
