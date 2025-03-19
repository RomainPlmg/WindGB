#ifndef __CPU_H__
#define __CPU_H__

#include <memory>

class Registers;
class RAM;

class CPU {
   public:
    CPU(RAM& memory);
    ~CPU();

    uint8_t Fetch8();
    uint16_t Fetch16();
    void RunNextInstruction();

    /* Getters */
    Registers* GetRegisters();
    RAM& GetRAM();

   private:
    RAM& m_RAM;                              // RAM is not owned by the CPU, but it needs to know it to fetch data
    std::unique_ptr<Registers> m_Registers;  // Registers of the CPU

    // Private methods
    void DecodeInstruction(uint8_t opcode);
};

#endif  // __CPU_H__