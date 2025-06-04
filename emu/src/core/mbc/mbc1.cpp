#include "mbc1.h"

#include "utils/log.h"

MBC1::MBC1(const std::vector<u8>& romData, std::vector<u8> ramData) : m_ROM(romData), m_RAM(std::move(ramData)) {
}

u8 MBC1::ReadROM(u16 addr) const {
    if (addr < 0x4000) {
        // Bank 0 -> Fixe
        return m_ROM.at(addr);
    } else if (addr < 0x8000) {
        // Switchable banks -> 1 to N
        u32 offset = (m_ROMBank * 0x4000) + (addr - 0x4000);  // Offset from 0x0000 to 0x4000 in the selected ROM bank
        return m_ROM.at(offset);
    } else {
        LOG_ERROR("Invalid address 0x{:02X} in MBC", addr);
        return 0xFF;
    }
}

void MBC1::WriteROM(u8 data, u16 addr) {
    if (addr < 0X2000) {  // RAM enable
        m_RAMEnable = (data & 0x0F) == 0X0A;
        LOG_INFO("{} cartridge RAM", (m_RAMEnable ? "Enable" : "Disable"));
    } else if (addr < 0x4000) {
        m_ROMBank = data & 0x1F;
        if (m_ROMBank == 0) {
            LOG_WARN("ROM bank cannot be 0");
            m_ROMBank = 1;
        }
    }
    // TODO: Manage bits high and banking modes for + than 32 banks
}

u8 MBC1::ReadRAM(u16 addr) const { return 0xFF; }

void MBC1::WriteRAM(u8 data, u16 addr) {}
