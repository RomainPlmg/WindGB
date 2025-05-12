#include "interrupt.h"
#include "log.h"

InterruptHandler::InterruptHandler(Bus& memBus) : m_Bus(memBus) {}

bool InterruptHandler::HasPending() const { 
    u8 IE = m_Bus.Read(INTERRUPT_ENABLE_ADDR);
    u8 IF = m_Bus.Read(IO_REG_INTERRUPT_FLAGS);
    return (IE & IF & 0x1F) != 0; }

u8 InterruptHandler::GetNextPending() { return u8(); }

void InterruptHandler::ClearFlag(u8 id) {
    if (id > 4) {
        LOG_ERROR("{} is an invalid interrupt ID", id);
    }
    u8 IF = m_Bus.Read(IO_REG_INTERRUPT_FLAGS);
    m_Bus.Write(IO_REG_INTERRUPT_FLAGS, IF & ~(1 << id));
}
