#include "bus.h"

#include "io.h"
#include "utils/log.h"

Bus::Bus() {
    m_VRAM = std::make_unique<VRAM>();
    m_WRAM = std::make_unique<WRAM>();
    m_HRAM = std::make_unique<HRAM>();
    m_OAM = std::make_unique<OAM>();
}

u8 Bus::Read(u16 addr) const {
    if (BETWEEN(addr, CARTRIDGE_FIXED_ROM_BANK_START_ADDR, CARTRIDGE_SWITCHABLE_ROM_BANK_END_ADDR)) {  // ROM data
        return m_Cartridge->Read(addr);
    }
    if (BETWEEN(addr, VRAM_ADDR_START, VRAM_ADDR_END)) {  // VRAM data
        return m_VRAM->Read(addr);
    }
    if (BETWEEN(addr, CARTRIDGE_EXTERNAL_RAM_BANK_START_ADDR, CARTRIDGE_EXTERNAL_RAM_BANK_END_ADDR)) {  // RAM data
        return m_Cartridge->Read(addr);
    }
    if (BETWEEN(addr, WRAM_ADDR_START, WRAM_ADDR_END)) {  // WRAM data
        return m_WRAM->Read(addr);
    }
    if (BETWEEN(addr, WRAM_ECHO_ADDR_START, WRAM_ECHO_ADDR_END)) {  // WRAM echo data
        return m_WRAM->Read(addr - WRAM_ADDR_SIZE);
    }
    if (BETWEEN(addr, OAM_ADDR_START, OAM_ADDR_END)) {  // OAM data
        return m_OAM->Read(addr);
    }
    if (BETWEEN(addr, 0xFEA0, 0xFEFF)) {  // Prohibited data
        return 0xFF;
    }
    if (BETWEEN(addr, REG_JOYP_ADDR, 0xFF7F)) {  // IOREG data
        return m_IO->Read(addr);
    }
    if (BETWEEN(addr, HRAM_ADDR_START, HRAM_ADDR_END)) {  // HRAM data
        return m_HRAM->Read(addr);
    }
    if (addr == REG_IE_ADDR) {  // IE data
        return m_IE;
    }

    LOG_ERROR("Invalid addr on bus for read operation. Addr = 0x{:04X}", addr);
    return 0;
}

const u8* Bus::GetPointerTo(u16 addr) {
    if (BETWEEN(addr, CARTRIDGE_FIXED_ROM_BANK_START_ADDR, CARTRIDGE_SWITCHABLE_ROM_BANK_END_ADDR)) {  // ROM data
        return m_Cartridge->GetPointerTo(addr);
    }
    if (BETWEEN(addr, VRAM_ADDR_START, VRAM_ADDR_END)) {  // VRAM data
        return m_VRAM->GetPointerTo(addr);
    }
    if (BETWEEN(addr, CARTRIDGE_EXTERNAL_RAM_BANK_START_ADDR, CARTRIDGE_EXTERNAL_RAM_BANK_END_ADDR)) {  // RAM data
        return m_Cartridge->GetPointerTo(addr);
    }
    if (BETWEEN(addr, WRAM_ADDR_START, WRAM_ADDR_END)) {  // WRAM data
        return m_WRAM->GetPointerTo(addr);
    }
    if (BETWEEN(addr, WRAM_ECHO_ADDR_START, WRAM_ECHO_ADDR_END)) {  // WRAM echo data
        return m_WRAM->GetPointerTo(addr - WRAM_ADDR_SIZE);
    }
    if (BETWEEN(addr, OAM_ADDR_START, OAM_ADDR_END)) {  // OAM data
        return m_OAM->GetPointerTo(addr);
    }
    if (BETWEEN(addr, 0xFEA0, 0xFEFF)) {  // Prohibited data
        return nullptr;
    }
    if (BETWEEN(addr, REG_JOYP_ADDR, 0xFF7F)) {  // IOREG data
        return m_IO->GetPointerTo(addr);
    }
    if (BETWEEN(addr, HRAM_ADDR_START, HRAM_ADDR_END)) {  // HRAM data
        return m_HRAM->GetPointerTo(addr);
    }
    if (addr == REG_IE_ADDR) {  // IE data
        return &m_IE;
    }

    LOG_ERROR("Invalid addr on bus for get pointer operation. Addr = 0x{:04X}", addr);
    return nullptr;
}

void Bus::Write(u16 addr, u8 data) {
    if (BETWEEN(addr, CARTRIDGE_FIXED_ROM_BANK_START_ADDR, CARTRIDGE_SWITCHABLE_ROM_BANK_END_ADDR)) {  // ROM data
        return m_Cartridge->Write(addr, data);
    }
    if (BETWEEN(addr, VRAM_ADDR_START, VRAM_ADDR_END)) {  // VRAM data
        return m_VRAM->Write(addr, data);
    }
    if (BETWEEN(addr, CARTRIDGE_EXTERNAL_RAM_BANK_START_ADDR, CARTRIDGE_EXTERNAL_RAM_BANK_END_ADDR)) {  // RAM data
        return m_Cartridge->Write(addr, data);
    }
    if (BETWEEN(addr, WRAM_ADDR_START, WRAM_ADDR_END)) {  // WRAM data
        return m_WRAM->Write(addr, data);
    }
    if (BETWEEN(addr, WRAM_ECHO_ADDR_START, WRAM_ECHO_ADDR_END)) {  // WRAM echo data
        return m_WRAM->Write(addr - WRAM_ADDR_SIZE, data);
    }
    if (BETWEEN(addr, OAM_ADDR_START, OAM_ADDR_END)) {  // OAM data
        return m_OAM->Write(addr, data);
    }
    if (BETWEEN(addr, 0xFEA0, 0xFEFF)) {  // Prohibited data
        return;
    }
    if (BETWEEN(addr, REG_JOYP_ADDR, 0xFF7F)) {  // IOREG data
        return m_IO->Write(addr, data);
    }
    if (BETWEEN(addr, HRAM_ADDR_START, HRAM_ADDR_END)) {  // HRAM data
        return m_HRAM->Write(addr, data);
    }
    if (addr == REG_IE_ADDR) {  // IE data
        m_IE = data;
        return;
    }

    LOG_ERROR("Invalid addr on bus for write operation. Addr = 0x{:04X} | Data = 0x{:01X}", addr, data);
    return;
}
