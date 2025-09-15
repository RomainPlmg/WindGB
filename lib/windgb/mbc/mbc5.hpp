#pragma once

#include "../mbc.hpp"

namespace WindGB {

class MBC5 final : public MBC {
   public:
    explicit MBC5(const std::vector<uint8_t>& rom, uint8_t ram_size_index = 0, bool battery = false);

    [[nodiscard]] uint8_t read(uint16_t addr) const override;
    void write(uint16_t addr, uint8_t data) override;

   private:
    const std::vector<uint8_t>& rom_;
    std::vector<uint8_t> ram_;
    uint16_t rom_bank_low_ = 1;
    uint16_t rom_bank_high_ = 0;
    uint8_t ram_bank_ = 0;
    bool ram_enable_ = false;
    bool battery_ = false;

    [[nodiscard]] uint16_t rom_bank() const { return (rom_bank_high_ << 8) | rom_bank_low_; }
};

}  // namespace WindGB