#include "ram.hpp"

#include "common.hpp"
#include "logger.hpp"

namespace WindGB {

uint8_t WRAM::read(const uint16_t addr) const {
    const uint16_t index = addr - WRAM_ADDR_START;
    return data_.at(index);
}

void WRAM::write(const uint16_t addr, const uint8_t data) {
    const uint16_t index = addr - WRAM_ADDR_START;
    data_[index] = data;
}

uint8_t HRAM::read(const uint16_t addr) const {
    const uint16_t index = addr - HRAM_ADDR_START;
    return data_.at(index);
}

void HRAM::write(const uint16_t addr, const uint8_t data) {
    const uint16_t index = addr - HRAM_ADDR_START;
    data_[index] = data;
}

uint8_t VRAM::read(const uint16_t addr) const {
    const uint16_t index = addr - VRAM_ADDR_START;
    return data_.at(index);
}

void VRAM::write(const uint16_t addr, uint8_t data) {
    const uint16_t index = addr - VRAM_ADDR_START;
    data_[index] = data;
}

uint8_t OAM::read(const uint16_t addr) const {
    const uint16_t index = addr - OAM_ADDR_START;
    return data_.at(index);
}

void OAM::write(const uint16_t addr, const uint8_t data) {
    const uint16_t index = addr - OAM_ADDR_START;
    data_[index] = data;
}

}  // namespace WindGB