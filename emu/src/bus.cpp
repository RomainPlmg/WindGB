#include "bus.h"

#include "log.h"

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

    if (address < 0x8000) {
        return m_Cartridge->Read(address);  // ROM data
    } else if (address < 0xA000) {
        return m_VRAM->Read(address);
    } else if (address >= 0xC000 && address < WRAM_ECHO_ADDR_START) {
        return m_WRAM->Read(address);
    } else if (address >= WRAM_ECHO_ADDR_START && address < 0xFE00) {
        return m_WRAM->Read(address - WRAM_ADDR_SIZE);
    } else if (address >= 0xFF00 && address < 0xFF80) {
        return m_IOREG->Read(address);
    } else if (address < INTERRUPT_ENABLE_ADDR) {
        return m_HRAM->Read(address);
    } else if (address == INTERRUPT_ENABLE_ADDR) {
        return m_IE;
    }

    LOG_ERROR("Invalid address on bus for read operation. Addr = 0x{:02X}", address);
    return 0;
}

void Bus::Write(u16 address, u8 data) {
    if (address < 0x8000) {
        // LOG_ERROR("The address 0x{:02X} belongs to the cartridge's ROM, you cannot write inside it.", address);
        // return (m_Cartridge->Write(address, data));
    } else if (address < 0xA000) {
        return m_VRAM->Write(address, data);
    } else if (address >= 0xC000 && address < 0xE000) {
        return m_WRAM->Write(address, data);
    } else if (address >= 0xFF00 && address < 0xFF80) {
        return m_IOREG->Write(address, data);
    } else if (address < 0xFFFF) {
        return m_HRAM->Write(address, data);
    } else if (address == INTERRUPT_ENABLE_ADDR) {
        m_IE = data;
        return;
    }

    LOG_ERROR("Invalid address on bus for write operation. Addr = 0x{:02X} | Data = 0x{:01X}", address, data);
    return;
}
