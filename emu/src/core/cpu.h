#pragma once

#include <memory>
#include <chrono>

#include "bus.h"
#include "interrupt.h"
#include "registers.h"
#include "utils/common.h"
#include "events/EventBus.h"

class CPU {
   public:
    CPU(Bus& memBus, IO& io, EventBus& eventBus);
    void Reset();
    void Step();
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

    void OnEvent(const Event& event);

   private:
    bool m_RequestIMEEnable = false;
    bool m_Halted = false;
    bool m_HaltBug = false;
    bool m_DMATransfert = false;
    u16 m_DMASourceAddr = 0x0100;
    u32 m_Ticks = 0;
    std::unique_ptr<Registers> m_Registers;
    std::unique_ptr<InterruptHandler> m_Interrupt;

    Bus& m_Bus;
    IO& m_IO;
    EventBus& m_EventBus;

    // Clock
    using Clock = std::chrono::high_resolution_clock;

    bool HandleInterrupts();
};