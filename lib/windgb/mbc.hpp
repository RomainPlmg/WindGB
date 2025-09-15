#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

namespace WindGB {

constexpr std::array<uint8_t, 6> RAM_SIZE_KIB = {0, 2, 8, 32, 128, 64};

class MBC {
   public:
    virtual ~MBC() = default;

    [[nodiscard]] virtual uint8_t read(uint16_t addr) const = 0;
    virtual void write(uint16_t addr, uint8_t data) = 0;

    static std::unique_ptr<MBC> create(const std::vector<uint8_t>& rom, uint8_t cartridge_type, uint8_t ram_size);
};

}  // namespace WindGB