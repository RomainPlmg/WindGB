#ifndef __CPU_H__
#define __CPU_H__

#include <SFML/System.hpp>
#include <memory>

constexpr double CPU_PERIOD_US = 1.0 / 4.194304;
constexpr double CPU_PERIOD_MS = 1.0 / 4194.304;

class Registers;
class Memory;

class CPU {
   public:
    CPU(Memory& memory);
    ~CPU();

    uint8_t Fetch8();
    uint16_t Fetch16();
    uint8_t Pop8Stack();
    uint16_t Pop16Stack();
    void Push8Stack(uint8_t value);
    void Push16Stack(uint16_t value);
    void RunNextInstruction();
    void AddCycles(uint64_t cycles);
    void Reset();

    /* Getters */
    Registers* GetRegisters();
    Memory& GetMemory();
    uint64_t GetCycles() const { return m_Cycles; }
    bool GetIME() const { return m_IME; }

    /* Setters */
    void SetIME(bool enable) { m_IME = enable; }

   private:
    Memory& m_Memory;                        // Memory is not owned by the CPU, but it needs to know it to fetch data
    std::unique_ptr<Registers> m_Registers;  // Registers of the CPU
    uint64_t m_Cycles;
    bool m_Halted;  // Halt mode, if true turn on low power mode and ignore interrupts
    bool m_IME;     // Interrupt Master Enable

    sf::Clock m_Clock;  // Clock of the CPU, at 4.194304 MHz

    // Private methods
    void DecodeInstruction(uint8_t opcode);
};

#endif  // __CPU_H__