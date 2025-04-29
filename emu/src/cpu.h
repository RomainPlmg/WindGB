#pragma once

#include <memory>

#include "bus.h"
#include "common.h"
#include "registers.h"

class CPU {
   public:
    CPU(Bus& memBus);
    void Reset();
    void Step();
    void AddCycles(u32 cycles) { m_Cycles += cycles; }
    uint8_t Fetch8();
    uint16_t Fetch16();
    uint8_t Pop8Stack();
    uint16_t Pop16Stack();
    void Push8Stack(uint8_t value);
    void Push16Stack(uint16_t value);

    /* Getters */
    Registers* GetRegisters() { return m_Registers.get(); }
    bool GetIME() const { return m_IME; }
    u32 GetCycles() const { return m_Cycles; }

    /* Setters */
    void SetIME(bool ime) { m_IME = ime; }
    void SetCycles(u32 cycles) { m_Cycles = cycles; }
    void RequestIMEEnable() { m_EnableIMEAfterInstruction = true; }

   private:
    bool m_IME;
    bool m_EnableIMEAfterInstruction;
    bool m_Halted;
    u32 m_Cycles;
    std::unique_ptr<Registers> m_Registers;
    Bus& m_Bus;

    void HandleInterrupts();
};