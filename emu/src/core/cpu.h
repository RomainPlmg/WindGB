#pragma once

#include <memory>

#include "bus.h"
#include "utils/common.h"
#include "interrupt.h"
#include "registers.h"

class CPU {
   public:
    CPU(Bus& memBus);
    void Reset();
    u8 Step();
    void AddCycles(u32 cycles) { m_Cycles += cycles; }
    uint8_t Fetch8();
    uint16_t Fetch16();
    uint8_t Pop8Stack();
    uint16_t Pop16Stack();
    void Push8Stack(uint8_t value);
    void Push16Stack(uint16_t value);

    /* Getters */
    Registers* GetRegisters() { return m_Registers.get(); }
    InterruptHandler* GetInterrupHandler() { return m_Interrupt.get(); }
    u32 GetCycles() const { return m_Cycles; }
    u16 GetInterrupVector(u8 id);  // Return the address of the interrupt handler corresponding to the ID

    /* Setters */
    void SetCycles(u32 cycles) { m_Cycles = cycles; }
    void RequestIMEEnable() { m_EnableIMECountdown = 2; }
    void Halt() { m_Halted = true; }

   private:
    int m_EnableIMECountdown;
    bool m_Halted;
    u32 m_Cycles;
    std::unique_ptr<Registers> m_Registers;
    Bus& m_Bus;
    std::unique_ptr<InterruptHandler> m_Interrupt;

    void HandleInterrupts();
};