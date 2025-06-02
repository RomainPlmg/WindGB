#include "bus.h"

#include "utils/log.h"

Bus::Bus(Cartridge* cartridge) : m_Cartridge(cartridge) {
    m_VRAM = std::make_unique<VRAM>();
    m_WRAM = std::make_unique<WRAM>();
    m_HRAM = std::make_unique<HRAM>();
    m_OAM = std::make_unique<OAM>();
    m_IOREG = std::make_unique<IO>();
}

u8 Bus::Read(u16 addr) const {
    if (addr < VRAM_ADDR_START) {  // ROM data
        return m_Cartridge->Read(addr);
    } else if (addr < 0xA000) {  // VRAM data
        return m_VRAM->Read(addr);
    } else if (addr < WRAM_ADDR_START) {  // RAM data
        m_Cartridge->Read(addr);
    } else if (addr < WRAM_ECHO_ADDR_START) {  // WRAM data
        return m_WRAM->Read(addr);
    } else if (addr < OAM_ADDR_START) {  // WRAM echo data
        return m_WRAM->Read(addr - WRAM_ADDR_SIZE);
    } else if (addr < 0xFEA0) {  // WRAM echo data
        return m_OAM->Read(addr);
    } else if (addr >= IO_REG_START && addr < HRAM_ADDR_START) {  // IOREG data
        return m_IOREG->Read(addr);
    } else if (addr < INTERRUPT_ENABLE_ADDR) {  // HRAM data
        return m_HRAM->Read(addr);
    } else if (addr == INTERRUPT_ENABLE_ADDR) {  // IE data
        return m_IE;
    }

    LOG_ERROR("Invalid addr on bus for read operation. Addr = 0x{:04X}", addr);
    return 0;
}

const u8* Bus::GetPointerTo(u16 addr) {
    if (addr < VRAM_ADDR_START) {  // ROM data
        return m_Cartridge->GetPointerTo(addr);
    } else if (addr < 0xA000) {  // VRAM data
        return m_VRAM->GetPointerTo(addr);
    } else if (addr < WRAM_ADDR_START) {  // RAM data
        m_Cartridge->GetPointerTo(addr);
    } else if (addr < WRAM_ECHO_ADDR_START) {  // WRAM data
        return m_WRAM->GetPointerTo(addr);
    } else if (addr < OAM_ADDR_START) {  // WRAM echo data
        return m_WRAM->GetPointerTo(addr - WRAM_ADDR_SIZE);
    } else if (addr < 0xFEA0) {  // WRAM echo data
        return m_OAM->GetPointerTo(addr);
    } else if (addr >= IO_REG_START && addr < HRAM_ADDR_START) {  // IOREG data
        return m_IOREG->GetPointerTo(addr);
    } else if (addr < INTERRUPT_ENABLE_ADDR) {  // HRAM data
        return m_HRAM->GetPointerTo(addr);
    } else if (addr == INTERRUPT_ENABLE_ADDR) {  // IE data
        return &m_IE;
    }

    LOG_ERROR("Invalid addr on bus for read operation. Addr = 0x{:04X}", addr);
    return nullptr;
}

void Bus::Write(u16 addr, u8 data) {
    if (addr < VRAM_ADDR_START) {  // ROM data
        return m_Cartridge->Write(addr, data);
    } else if (addr < 0xA000) {  // VRAM data
        return m_VRAM->Write(addr, data);
    } else if (addr < WRAM_ADDR_START) {  // RAM data
        return m_Cartridge->Write(addr, data);
    } else if (addr < WRAM_ECHO_ADDR_START) {  // WRAM data
        return m_WRAM->Write(addr, data);
    } else if (addr < OAM_ADDR_START) {  // WRAM echo data
        return m_WRAM->Write(addr - WRAM_ADDR_SIZE, data);
    } else if (addr < 0xFEA0) {  // WRAM echo data
        return m_OAM->Write(addr, data);
    } else if (addr >= IO_REG_START && addr < HRAM_ADDR_START) {  // IOREG data
        return m_IOREG->Write(addr, data);
    } else if (addr < INTERRUPT_ENABLE_ADDR) {  // HRAM data
        return m_HRAM->Write(addr, data);
    } else if (addr == INTERRUPT_ENABLE_ADDR) {  // IE data
        m_IE = data;
        return;
    }

    LOG_ERROR("Invalid addr on bus for write operation. Addr = 0x{:04X} | Data = 0x{:01X}", addr, data);
    return;
}
