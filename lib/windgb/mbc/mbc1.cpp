#include "mbc1.hpp"

#include <cstdint>

#include "../logger.hpp"

namespace WindGB {

MBC1::MBC1(const std::vector<uint8_t>& rom, const uint8_t ram_size_index, const bool battery) : rom_(rom), battery_(battery) {
    ram_.resize(RAM_SIZE_KIB[ram_size_index] * 1024);
}

uint8_t MBC1::read(uint16_t addr) const {
    if (addr < 0x4000) {  // Bank 0 -> Fixed
        return rom_.at(addr);
    }

    if (addr < 0x8000) {  // Switchable banks -> 1 to N
        if (const uint32_t rom_addr = (rom_bank_ * 0x4000) + (addr - 0x4000); rom_addr < rom_.size()) {
            return rom_.at(rom_addr);
        }
    }

    if (addr >= 0xA000 && addr < 0xC000 && ram_enable_ && !ram_.empty()) {  // External RAM

        if (banking_mode_ == 0) {  // Simple banking mode (One RAM bank)
            return ram_[addr - 0xA000];
        }

        // Advanced banking mode (Several RAM banks)
        if (const uint32_t ram_addr = (ram_bank_ * 0x2000) + (addr - 0xA000); ram_addr < ram_.size()) {
            return ram_.at(ram_addr);
        }
    }

    LOG_ERROR("Invalid address 0x{:04X} in MBC", addr);
    return 0xFF;
}

void MBC1::write(const uint16_t addr, const uint8_t data) {
    if (addr < 0X2000) {  // RAM enable
        ram_enable_ = (data & 0x0F) == 0X0A;
    } else if (addr < 0x4000) {  // ROM Bank number
        rom_bank_ = data & 0x1F;
        if (rom_bank_ == 0) {
            LOG_WARN("ROM bank cannot be 0");
            rom_bank_ = 1;
        }
    } else if (addr < 0x6000) {  // RAM Bank number
        ram_bank_ = data & 0x03;
    } else if (addr < 0x8000) {
        banking_mode_ = data & 0x01;
    } else if (addr >= 0xA000 && addr < 0xC000 && ram_enable_ && !ram_.empty()) {  // External RAM write
        if (banking_mode_ == 0) {
            if (const uint32_t ram_addr = addr - 0xA000; ram_addr < ram_.size()) {
                ram_[ram_addr] = data;
            }
        } else {
            if (const uint32_t ram_addr = (ram_bank_ * 0x2000) + (addr - 0xA000); ram_addr < ram_.size()) {
                ram_[ram_addr] = data;
            }
        }
    } else {
        LOG_ERROR("Invalid address 0x{:04X} in MBC", addr);
    }
}

}  // namespace WindGB