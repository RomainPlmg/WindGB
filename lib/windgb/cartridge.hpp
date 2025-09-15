#pragma once

#include <memory>
#include <string>
#include <vector>

#include "component.hpp"
#include "mbc.hpp"

namespace WindGB {

struct CartridgeHeader {
    uint8_t entry[4];          // 0x0100-0x0103 -> Entry point
    uint8_t logo[48];          // 0x0104-0x0133 -> Nintendo logo
    uint8_t title[16];         // 0x0134-0x0143 -> Title
    uint16_t new_lic_code;     // 0x0144-0x0145 -> Code of the game publisher
    uint8_t sgb_flag;          // 0x0146 -> Is game supports SGB function ? (Yes if 0x03)
    uint8_t cart_type;         // 0x0147 -> Cartridge type
    uint8_t rom_size;          // 0x0148 -> ROM size on the cartridge
    uint8_t ram_size;          // 0x0149 -> RAM size on the cartridge
    uint8_t dest_code;         // 0x014A -> Sold in Japan or elsewhere
    uint8_t lic_code;          // 0x014B -> Old code of the game publisher
    uint8_t version;           // 0x014C -> Version of the game
    uint8_t checksum;          // 0x014D -> Compute the cartridge header bytes 0x0134-0x014C
    uint16_t global_checksum;  // 0x014E-0x014F -> Global checksum
};

class Cartridge : public Component {
   public:
    void load(const std::string& rom_path);
    [[nodiscard]] uint8_t read(uint16_t addr) const override;
    void write(uint16_t addr, uint8_t data) override;

    [[nodiscard]] CartridgeHeader* get_header() const { return header_; }

   private:
    CartridgeHeader* header_ = nullptr;
    std::vector<uint8_t> data_;
    std::unique_ptr<MBC> p_mbc_;

    [[nodiscard]] std::string get_title() const;
    [[nodiscard]] std::string get_cart_type() const;
    [[nodiscard]] std::string get_lic_name() const;
};

}  // namespace WindGB