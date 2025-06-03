#pragma once

#include <memory>

#include "bus.h"
#include "gfx/ppu.h"
#include "interrupt.h"
#include "registers.h"
#include "utils/common.h"

class CPU {
   public:
    CPU(Bus& memBus, PPU& ppu, IO& io);
    void Reset();
    int Step();
    void Tick(u32 ticks);

    uint8_t Fetch8();
    uint16_t Fetch16();
    uint8_t Pop8Stack();
    uint16_t Pop16Stack();
    void Push8Stack(u8 value);
    void Push16Stack(u16 value);

    /* Getters */
    Registers* GetRegisters() { return m_Registers.get(); }
    InterruptHandler* GetInterrupHandler() { return m_Interrupt.get(); }
    u16 GetInterrupVector(u8 id);  // Return the address of the interrupt handler corresponding to the ID

    /* Setters */
    void RequestIMEEnable() { m_RequestIMEEnable = true; }
    void Halt() { m_Halted = true; }

   private:
    bool m_RequestIMEEnable = false;
    bool m_Halted = false;
    bool m_HaltBug = false;
    u32 m_Ticks = 0;
    std::unique_ptr<Registers> m_Registers;
    std::unique_ptr<InterruptHandler> m_Interrupt;

    Bus& m_Bus;
    PPU& m_PPU;
    IO& m_IO;

    bool HandleInterrupts();
};