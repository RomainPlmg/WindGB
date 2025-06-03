#include "io.h"

#include "utils/log.h"

IO::IO(Bus& memBus) : m_Bus(memBus) { m_Timer = std::make_unique<Timer>(m_Bus); }

void IO::Reset() { m_Timer->Reset(); }

u8 IO::Read(u16 addr) const {
    if (BETWEEN(addr, TIMER_START_ADDR, TIMER_END_ADDR)) {
        return m_Timer->Read(addr);
    }

    u16 relativeAddr = addr - 0xFF00;
    if (relativeAddr >= 0x80) {
        LOG_ERROR("Address addr 0x{:02X} is out of IO REG range 0x{:02X}<->0x{:02X}", addr, 0xFF00, 0xFF7F);
        return 0;
    }
    return m_Data.at(relativeAddr);
}

const u8* IO::GetPointerTo(u16 addr) const {
    u16 relativeAddr = addr - 0xFF00;
    if (relativeAddr >= 0x80) {
        LOG_ERROR("Address addr 0x{:02X} is out of IO REG range 0x{:02X}<->0x{:02X}", addr, 0xFF00, 0xFF7F);
        return 0;
    }
    return &m_Data.at(relativeAddr);
}

void IO::Write(u16 addr, u8 data) {
    if (BETWEEN(addr, TIMER_START_ADDR, TIMER_END_ADDR)) {
        return m_Timer->Write(addr, data);
    }

    u16 relativeAddr = addr - 0xFF00;
    if (relativeAddr >= 0x80) {
        LOG_ERROR("Address addr 0x{:02X} is out of IO REG range 0x{:02X}<->0x{:02X}", addr, 0xFF00, 0xFF7F);
        return;
    }

    m_Data[relativeAddr] = data;
}
