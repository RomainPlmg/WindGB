#include "mbc5.hpp"

#include "logger.hpp"

namespace WindGB {

MBC5::MBC5(const std::vector<uint8_t>& rom, const uint8_t ram_size_index, const bool battery) : rom_(rom), battery_(battery) {
    ram_.resize(RAM_SIZE_KIB[ram_size_index] * 1024);
}
uint8_t MBC5::read(uint16_t addr) const {
    if (addr < 0x4000) {
        return rom_.at(addr);
    }

    if (addr < 0x8000) {
        if (const uint32_t rom_addr = (rom_bank() * 0x4000) + (addr - 0x4000); rom_addr < rom_.size()) {
            return rom_.at(rom_addr);
        }
    }

    if (addr >= 0xA000 && addr < 0xC000 && ram_enable_ && !ram_.empty()) {
        if (const uint32_t ram_addr = (ram_bank_ * 0x2000) + (addr - 0xA000); ram_addr < ram_.size()) {
            return ram_.at(ram_addr);
        }
    }

    LOG_ERROR("Invalid read address 0x{:04X} in MBC", addr);
    return 0xFF;
}

void MBC5::write(uint16_t addr, const uint8_t data) {
    if (addr < 0X2000) {
        ram_enable_ = (data & 0x0F) == 0X0A;
    } else if (addr < 0x3000) {
        rom_bank_low_ = data;
    } else if (addr < 0x4000) {
        rom_bank_high_ = data & 0x01;
    } else if (addr < 0x6000) {
        ram_bank_ = data & 0x0F;
    } else if (addr >= 0xA000 && addr < 0xC000 && ram_enable_ && !ram_.empty()) {  // External RAM Write
        if (const uint32_t ram_addr = (ram_bank_ * 0x2000) + (addr - 0xA000); ram_addr < ram_.size()) {
            ram_[ram_addr] = data;
            if (battery_) {
                // TODO: Save
            }
        }
    } else {
        LOG_ERROR("Invalid write address 0x{:04X} in MBC", addr);
    }
}

}  // namespace WindGB