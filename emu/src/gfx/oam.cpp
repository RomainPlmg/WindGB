#include "oam.h"

#include "utils/log.h"

OAM::OAM() {}

u8 OAM::Read(u16 addr) const {
    u16 relativeAddr = addr - OAM_ADDR_START;
    if (relativeAddr >= OAM_ADDR_SIZE) {
        LOG_ERROR("Address addr 0x{:04X} is out of OAM range 0x{:02X}<->0x{:02X}", addr, OAM_ADDR_START, OAM_ADDR_START + OAM_ADDR_SIZE - 1);
        return 0;
    }
    return m_Data.at(relativeAddr);
}

const u8* OAM::GetPointerTo(u16 addr) const {
    u16 relativeAddr = addr - OAM_ADDR_START;
    if (relativeAddr >= OAM_ADDR_SIZE) {
        LOG_ERROR("Address addr 0x{:04X} is out of OAM range 0x{:02X}<->0x{:02X}", addr, OAM_ADDR_START, OAM_ADDR_START + OAM_ADDR_SIZE - 1);
        return 0;
    }
    return &m_Data.at(relativeAddr);
}

void OAM::Write(u16 addr, u8 data) {
    u16 relativeAddr = addr - OAM_ADDR_START;
    if (relativeAddr >= OAM_ADDR_SIZE) {
        LOG_ERROR("Address addr 0x{:04X} is out of OAM range 0x{:02X}<->0x{:02X}", addr, OAM_ADDR_START, OAM_ADDR_START + OAM_ADDR_SIZE - 1);
        return;
    }

    m_Data[relativeAddr] = data;
}
