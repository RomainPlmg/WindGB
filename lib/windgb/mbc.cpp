#include "mbc.hpp"

#include "mbc/mbc1.hpp"
#include "mbc/mbc5.hpp"

namespace WindGB {

std::unique_ptr<MBC> MBC::create(const std::vector<uint8_t>& rom, const uint8_t cartridge_type, uint8_t ram_size) {
    switch (cartridge_type) {
        case 0x00:  // ROM ONLY
            return nullptr;
        case 0x01:  // MBC1
            return std::make_unique<MBC1>(rom);
        case 0x02:  // MBC1+RAM
            return std::make_unique<MBC1>(rom, ram_size);
        case 0x03:  // MBC1+RAM+BATTERY
            return std::make_unique<MBC1>(rom, ram_size, true);
        case 0x19:  // MBC5
            return std::make_unique<MBC5>(rom);
        case 0x1A:  // MBC5+RAM
            return std::make_unique<MBC5>(rom, ram_size);
        case 0x1B:  // MBC5+RAM+BATTERY
            return std::make_unique<MBC5>(rom, ram_size, true);

        default:
            return nullptr;
    }
}

}  // namespace WindGB
