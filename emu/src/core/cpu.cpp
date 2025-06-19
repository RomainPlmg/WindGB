#include "cpu.h"

#include <iostream>

#include "bus.h"
#include "events/EventApp.h"
#include "instructions.h"
#include "io.h"
#include "registers.h"
#include "utils/log.h"

CPU::CPU(Bus& memBus, IO& io, EventBus& eventBus) : m_Bus(memBus), m_IO(io), m_EventBus(eventBus) {
    m_Registers = std::make_unique<Registers>();
    m_Interrupt = std::make_unique<InterruptHandler>(memBus);

    m_EventBus.Subscribe(BIND_EVENT_FN(OnEvent), EventCategory::EventCategoryApp);
}

void CPU::Reset() {  // Init registers
    // LOG_INFO("Reset CPU");
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

    m_Ticks = 0;
    m_Interrupt->SetIME(false);
    m_RequestIMEEnable = false;
    m_Halted = false;
}

void CPU::Step() {
    u32 oldCycles = m_Ticks;  // Save the nb of cycles before the instruction

    if (m_Halted) {
        if (m_Interrupt->HasPending()) {
            m_Halted = false;  // Wakes up the CPU
            if (!m_Interrupt->GetIME()) {
                // Trigger HALT bug
                m_HaltBug = true;
                Tick(1);
                return;
            }
        } else {
            Tick(1);
            return;
        }
    }

    if (m_DMATransfert) {
        for (int i = 0; i < 160; i++) {
            u8 data = m_Bus.Read(m_DMASourceAddr + i);
            m_Bus.Write(OAM_ADDR_START + i, data);
            // Tick(1);
        }
        m_DMATransfert = false;
        return;
    }

    // Interrupt handler
    if (!HandleInterrupts()) {  // Fetch the next opcode
        u8 opcode = Fetch8();
        Instruction curInst = InstructionTable[opcode];
        if (m_HaltBug) {
            m_Registers->PC--;
            m_HaltBug = false;
        }
        if (opcode == 0xCB) {  // Prefix instructions, fetch the next instruction in the same step
            opcode = Fetch8();
            curInst = PrefixInstructionTable[opcode];
        }

        LOG_DEBUG("Executing instruction '{}'\tPC = 0x{:02X}", curInst.name, m_Registers->PC);

        // For EI instruction, enable interrupt flag after the next instruction
        if (m_RequestIMEEnable == true) {
            curInst.Execute(*this, m_Bus);  // Run the instruction
            m_Interrupt->SetIME(true);
            m_RequestIMEEnable = false;
        } else {
            curInst.Execute(*this, m_Bus);  // Run the instruction
        }
    }
}

void CPU::Tick(u32 ticks) {
    for (int cycle = 0; cycle < ticks; cycle++) {
        for (int tcycle = 0; tcycle < 4; tcycle++) {
            m_Ticks++;
            m_IO.GetTimer()->Step();
            m_IO.GetPPU()->Step();
        }
    }
}

u8 CPU::Fetch8() {
    u8 value = m_Bus.Read(m_Registers->PC);
    m_Registers->PC++;
    return value;
}

u16 CPU::Fetch16() {
    u16 low = Fetch8();
    u16 high = Fetch8();
    return (high << 8) | low;
}

u8 CPU::Pop8Stack() { return m_Bus.Read(m_Registers->SP++); }

u16 CPU::Pop16Stack() {
    u8 low = m_Bus.Read(m_Registers->SP++);
    u8 high = m_Bus.Read(m_Registers->SP++);

    return (high << 8) | low;
}

u16 CPU::GetInterrupVector(u8 id) {
    switch (id) {
        case 0:
            return 0x0040;  // V-Blank
        case 1:
            return 0x0048;  // LCD STAT
        case 2:
            return 0x0050;  // Timer
        case 3:
            return 0x0058;  // Serial
        case 4:
            return 0x0060;  // Joypad
        default:
            LOG_ERROR("{} is an invalid interrupt ID", id);
            return 0x0000;  // Should never happen
    }
}

void CPU::Push8Stack(u8 value) { m_Bus.Write(--m_Registers->SP, value); }

void CPU::Push16Stack(u16 value) {
    u8 high = (value >> 8) & 0xFF;
    u8 low = value & 0xFF;

    m_Bus.Write(--m_Registers->SP, high);
    m_Bus.Write(--m_Registers->SP, low);
}

bool CPU::HandleInterrupts() {
    if (m_Interrupt->GetIME() && m_Interrupt->HasPending()) {
        u8 id = m_Interrupt->GetNextPending();
        m_Interrupt->ClearFlag(id);
        if (id != 0xFF) {
            Push16Stack(m_Registers->PC);
            m_Interrupt->SetIME(false);
            m_Registers->PC = GetInterrupVector(id);  // Jump to the address of the interrupt handler
            Tick(5);
        }
        return true;
    }
    return false;
}

void CPU::OnEvent(const Event& event) {
    if (event.GetType() == EventType::DMATransfert) {
        const auto* e = dynamic_cast<const DMATransfertEvent*>(&event);
        m_DMATransfert = true;
        m_DMASourceAddr = e->m_SourceAddr;
    }
}