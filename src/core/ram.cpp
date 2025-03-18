#include "ram.h"

RAM::RAM() : m_Memory({0}) {}

uint8_t RAM::Read(uint16_t addr) const {
    size_t it = static_cast<size_t>(addr);
    return this->m_Memory[static_cast<size_t>(it)];
}

void RAM::Write(uint16_t addr, uint8_t data) {
    size_t it = static_cast<size_t>(addr);
    this->m_Memory[it] = data;
}
