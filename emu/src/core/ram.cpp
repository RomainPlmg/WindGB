#include "ram.h"

#include "utils/log.h"

u8 WRAM::Read(u16 addr) const {
    u16 relativeAddr = addr - WRAM_ADDR_START;
    if (relativeAddr >= WRAM_ADDR_SIZE) {
        LOG_ERROR("Address addr 0x{:04X} is out of WRAM range 0x{:02X}<->0x{:02X}", addr, WRAM_ADDR_START, WRAM_ADDR_START + WRAM_ADDR_SIZE - 1);
        return 0;
    }
    return m_Data.at(relativeAddr);
}

const u8* WRAM::GetPointerTo(u16 addr) const {
    u16 relativeAddr = addr - WRAM_ADDR_START;
    if (relativeAddr >= WRAM_ADDR_SIZE) {
        LOG_ERROR("Address addr 0x{:04X} is out of WRAM range 0x{:02X}<->0x{:02X}", addr, WRAM_ADDR_START, WRAM_ADDR_START + WRAM_ADDR_SIZE - 1);
        return 0;
    }
    return &m_Data.at(relativeAddr);
}

void WRAM::Write(u16 addr, u8 data) {
    u16 relativeAddr = addr - WRAM_ADDR_START;
    if (relativeAddr >= WRAM_ADDR_SIZE) {
        LOG_ERROR("Address addr 0x{:04X} is out of WRAM range 0x{:02X}<->0x{:02X}", addr, WRAM_ADDR_START, WRAM_ADDR_START + WRAM_ADDR_SIZE - 1);
        return;
    }

    m_Data[relativeAddr] = data;
}

u8 HRAM::Read(u16 addr) const {
    u16 relativeAddr = addr - HRAM_ADDR_START;
    if (relativeAddr >= HRAM_ADDR_SIZE) {
        LOG_ERROR("Address addr 0x{:04X} is out of HRAM range 0x{:02X}<->0x{:02X}", addr, HRAM_ADDR_START, HRAM_ADDR_START + HRAM_ADDR_SIZE - 1);
        return 0;
    }
    return m_Data.at(relativeAddr);
}

const u8* HRAM::GetPointerTo(u16 addr) const {
    u16 relativeAddr = addr - HRAM_ADDR_START;
    if (relativeAddr >= HRAM_ADDR_SIZE) {
        LOG_ERROR("Address addr 0x{:04X} is out of HRAM range 0x{:02X}<->0x{:02X}", addr, HRAM_ADDR_START, HRAM_ADDR_START + HRAM_ADDR_SIZE - 1);
        return 0;
    }
    return &m_Data.at(relativeAddr);
}

void HRAM::Write(u16 addr, u8 data) {
    u16 relativeAddr = addr - HRAM_ADDR_START;
    if (relativeAddr >= HRAM_ADDR_SIZE) {
        LOG_ERROR("Address addr 0x{:04X} is out of HRAM range 0x{:02X}<->0x{:02X}", addr, HRAM_ADDR_START, HRAM_ADDR_START + HRAM_ADDR_SIZE - 1);
        return;
    }

    m_Data[relativeAddr] = data;
}

u8 VRAM::Read(u16 addr) const {
    u16 relativeAddr = addr - VRAM_ADDR_START;
    if (relativeAddr >= VRAM_ADDR_SIZE) {
        LOG_ERROR("Address addr 0x{:04X} is out of VRAM range 0x{:02X}<->0x{:02X}", addr, VRAM_ADDR_START, VRAM_ADDR_START + VRAM_ADDR_SIZE - 1);
        return 0;
    }
    return m_Data.at(relativeAddr);
}

const u8* VRAM::GetPointerTo(u16 addr) const {
    u16 relativeAddr = addr - VRAM_ADDR_START;
    if (relativeAddr >= VRAM_ADDR_SIZE) {
        LOG_ERROR("Address addr 0x{:04X} is out of VRAM range 0x{:02X}<->0x{:02X}", addr, VRAM_ADDR_START, VRAM_ADDR_START + VRAM_ADDR_SIZE - 1);
        return 0;
    }
    return &m_Data.at(relativeAddr);
}

void VRAM::Write(u16 addr, u8 data) {
    u16 relativeAddr = addr - VRAM_ADDR_START;
    if (relativeAddr >= VRAM_ADDR_SIZE) {
        LOG_ERROR("Address addr 0x{:04X} is out of VRAM range 0x{:02X}<->0x{:02X}", addr, VRAM_ADDR_START, VRAM_ADDR_START + VRAM_ADDR_SIZE - 1);
        return;
    }

    m_Data[relativeAddr] = data;
}
