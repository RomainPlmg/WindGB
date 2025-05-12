#include "interrupt.h"

#include "log.h"

InterruptHandler::InterruptHandler(Bus& memBus) : m_Bus(memBus) {}

bool InterruptHandler::HasPending() const {
    u8 IE = m_Bus.Read(INTERRUPT_ENABLE_ADDR);
    u8 IF = m_Bus.Read(IO_REG_INTERRUPT_FLAGS);
    return (IE & IF & 0x1F) != 0;
}

u8 InterruptHandler::GetNextPending() {
    u8 IE = m_Bus.Read(INTERRUPT_ENABLE_ADDR);
    u8 IF = m_Bus.Read(IO_REG_INTERRUPT_FLAGS);

    u8 pending = IF & IE;  // Mask for enabled pending instructions
    for (u8 id = 0; id <= 4; id++) {
        if (((1 << id) & pending) != 0) {
            return id;
        }
    }
    return 0xFF;
}

void InterruptHandler::ClearFlag(u8 id) {
    if (id > 4) {
        LOG_ERROR("{} is an invalid interrupt ID", id);
    }
    u8 IF = m_Bus.Read(IO_REG_INTERRUPT_FLAGS);
    m_Bus.Write(IO_REG_INTERRUPT_FLAGS, IF & ~(1 << id));
}
