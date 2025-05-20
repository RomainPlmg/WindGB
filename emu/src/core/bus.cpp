#include "bus.h"

#include "utils/log.h"

Bus::Bus(Cartridge* cartridge) : m_Cartridge(cartridge) {
    m_VRAM = std::make_unique<VRAM>();
    m_WRAM = std::make_unique<WRAM>();
    m_HRAM = std::make_unique<HRAM>();
    m_IOREG = std::make_unique<IO>();
}

u8 Bus::Read(u16 address) const {
    if (address == 0xFF44) {  // For Gameboy-Doctor
        return 0x90;
    }

    if (address < VRAM_ADDR_START) {  // ROM data
        return m_Cartridge->Read(address);
    }

    if (address >= VRAM_ADDR_START && address < 0xA000) {  // VRAM data
        return m_VRAM->Read(address);
    }

    if (address >= WRAM_ADDR_START && address < WRAM_ECHO_ADDR_START) {  // WRAM data
        return m_WRAM->Read(address);
    }

    if (address >= WRAM_ECHO_ADDR_START && address < 0xFE00) {  // WRAM echo data
        return m_WRAM->Read(address - WRAM_ADDR_SIZE);
    }

    if (address >= IO_REG_START && address < HRAM_ADDR_START) {  // IOREG data
        return m_IOREG->Read(address);
    }

    if (address >= HRAM_ADDR_START && address < INTERRUPT_ENABLE_ADDR) {  // HRAM data
        return m_HRAM->Read(address);
    }

    if (address == INTERRUPT_ENABLE_ADDR) {  // IE data
        return m_IE;
    }

    LOG_ERROR("Invalid address on bus for read operation. Addr = 0x{:04X}", address);
    return 0;
}

const u8* Bus::GetPointerTo(u16 address) {
    if (address < VRAM_ADDR_START) {  // ROM data
        return m_Cartridge->GetPointerTo(address);
    }

    if (address >= VRAM_ADDR_START && address < 0xA000) {  // VRAM data
        return m_VRAM->GetPointerTo(address);
    }

    if (address >= WRAM_ADDR_START && address < WRAM_ECHO_ADDR_START) {  // WRAM data
        return m_WRAM->GetPointerTo(address);
    }

    if (address >= WRAM_ECHO_ADDR_START && address < 0xFE00) {  // WRAM echo data
        return m_WRAM->GetPointerTo(address - WRAM_ADDR_SIZE);
    }

    if (address >= IO_REG_START && address < HRAM_ADDR_START) {  // IOREG data
        return m_IOREG->GetPointerTo(address);
    }

    if (address >= HRAM_ADDR_START && address < INTERRUPT_ENABLE_ADDR) {  // HRAM data
        return m_HRAM->GetPointerTo(address);
    }

    if (address == INTERRUPT_ENABLE_ADDR) {  // IE data
        return &m_IE;
    }

    LOG_ERROR("Invalid address on bus for read operation. Addr = 0x{:04X}", address);
    return nullptr;
}

void Bus::Write(u16 address, u8 data) {
    if (address < VRAM_ADDR_START) {  // ROM data
        return m_Cartridge->Write(address, data);
    }

    if (address >= VRAM_ADDR_START && address < 0xA000) {  // VRAM data
        return m_VRAM->Write(address, data);
    }

    if (address >= WRAM_ADDR_START && address < WRAM_ECHO_ADDR_START) {  // WRAM data
        return m_WRAM->Write(address, data);
    }

    if (address >= WRAM_ECHO_ADDR_START && address < 0xFE00) {  // WRAM echo data
        return m_WRAM->Write(address - WRAM_ADDR_SIZE, data);
    }

    if (address >= IO_REG_START && address < HRAM_ADDR_START) {  // IOREG data
        return m_IOREG->Write(address, data);
    }

    if (address >= HRAM_ADDR_START && address < INTERRUPT_ENABLE_ADDR) {  // HRAM data
        return m_HRAM->Write(address, data);
    }

    if (address == INTERRUPT_ENABLE_ADDR) {  // IE data
        m_IE = data;
        return;
    }

    LOG_ERROR("Invalid address on bus for write operation. Addr = 0x{:04X} | Data = 0x{:01X}", address, data);
    return;
}
