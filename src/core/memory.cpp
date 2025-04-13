#include "memory.h"

#include "pch.h"

Memory::Memory() : m_Memory({0}) {}

uint8_t Memory::Read(uint16_t addr) const {
    size_t it = static_cast<size_t>(addr);
    return this->m_Memory[static_cast<size_t>(it)];
}

void Memory::Write(uint16_t addr, uint8_t data) {
    size_t it = static_cast<size_t>(addr);
    this->m_Memory[it] = data;
}

void Memory::LoadROM(const std::vector<uint8_t>& rom) {
    uint16_t startAddr = 0x0000;
    for (const auto& byte : rom) {
        m_Memory[startAddr] = byte;
        startAddr++;
    }
}
