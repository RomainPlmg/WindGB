#include "cartridge.hpp"

#include <cstdint>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "common.hpp"
#include "logger.hpp"
#include "mbc/mbc1.hpp"

namespace WindGB {

// clang-format off
static const std::unordered_map<uint8_t, std::string> CARTRIDGE_TYPES = {
    {0x00, "ROM ONLY"},
    {0x01, "MBC1"},
    {0x02, "MBC1+RAM"},
    {0x03, "MBC1+RAM+BATTERY"},
    {0x05, "MBC2"},
    {0x06, "MBC2+BATTERY"},
    {0x08, "ROM+RAM 1"},
    {0x09, "ROM+RAM+BATTERY 1"},
    {0x0B, "MMM01"},
    {0x0C, "MMM01+RAM"},
    {0x0D, "MMM01+RAM+BATTERY"},
    {0x0F, "MBC3+TIMER+BATTERY"},
    {0x10, "MBC3+TIMER+RAM+BATTERY 2"},
    {0x11, "MBC3"},
    {0x12, "MBC3+RAM 2"},
    {0x13, "MBC3+RAM+BATTERY 2"},
    {0x19, "MBC5"},
    {0x1A, "MBC5+RAM"},
    {0x1B, "MBC5+RAM+BATTERY"},
    {0x1C, "MBC5+RUMBLE"},
    {0x1D, "MBC5+RUMBLE+RAM"},
    {0x1E, "MBC5+RUMBLE+RAM+BATTERY"},
    {0x20, "MBC6"},
    {0x22, "MBC7+SENSOR+RUMBLE+RAM+BATTERY"}
};

static const std::unordered_map<uint8_t, std::string> LICENSE_CODES = {
    {0x00, "None"},
    {0x01, "Nintendo R&D"},
    {0x08, "Capcom"},
    {0x13, "EA"},
    {0x18, "Hudson Soft"},
    {0x19, "B-AI"},
    {0x20, "KSS"},
    {0x22, "Planning Office WADA"},
    {0x24, "PCM Complete"},
    {0x25, "San-X"},
    {0x28, "Kemco"},
    {0x29, "Seta Corporation"},
    {0x30, "Viacom"},
    {0x31, "Nintendo"},
    {0x32, "Bandai"},
    {0x33, "Ocean Software/Acclaim Entertainment"},
    {0x34, "Konami"},
    {0x35, "HectorSoft"},
    {0x37, "Taito"},
    {0x38, "Hudson Soft"},
    {0x39, "Banpresto"},
    {0x41, "Ubisoft"},
    {0x42, "Atlus"},
    {0x44, "Malibu Interactive"},
    {0x46, "Angel"},
    {0x47, "Bullet-Proof Software"},
    {0x49, "Irem"},
    {0x50, "Absolute"},
    {0x51, "Acclaim Entertainment"},
    {0x52, "Activision"},
    {0x53, "Sammy USA Corporation"},
    {0x54, "Konami"},
    {0x55, "Hi tech Entertainment"},
    {0x56, "LJN"},
    {0x57, "Matchbox"},
    {0x58, "Mattel"},
    {0x59, "Milton Bradley Company"},
    {0x60, "Titus Interactive"},
    {0x61, "Virgin Game Ltd."},
    {0x64, "Lucasfilm Games"},
    {0x67, "Ocean Software"},
    {0x69, "EA"},
    {0x70, "Infogrames"},
    {0x71, "Interplay Entertainment"},
    {0x72, "Broderbund"},
    {0x73, "Sculptured Software"},
    {0x75, "The Sales Curve Limited"},
    {0x78, "THQ"},
    {0x79, "Accolade"},
    {0x80, "Misawa Entertainment"},
    {0x83, "lozc"},
    {0x86, "Tokuma Shoten"},
    {0x87, "Tsukuda Original"},
    {0x91, "Chunsoft Co."},
    {0x92, "Video System"},
    {0x93, "Ocean Software/Acclaim Entertainment"},
    {0x95, "Varie"},
    {0x96, "Yonezawa/s\'pal"},
    {0x97, "Kaneko"},
    {0x99, "Pack-In-Video"},
    {0xA4, "Konami (Yu-Gi-Oh!)"},
};
// clang-format on

void Cartridge::load(const std::string& rom_path) {
    std::ifstream file(rom_path, std::ios::binary | std::ios::in);
    if (!file) {
        throw std::runtime_error("Unable to open the ROM \'" + rom_path + "\'");
    }

    // Read file into the memory
    char byte;
    while (file.read(&byte, 1)) {
        data_.push_back(static_cast<uint8_t>(byte));
    }

    if (!file.eof()) {
        data_.clear();
        throw std::runtime_error("ROM read failed");
    }

    header_ = reinterpret_cast<CartridgeHeader*>(data_.data() + CARTRIDGE_HEADER_ENTRY_POINT);

    // MBC
    p_mbc_ = MBC::create(data_, header_->cart_type, header_->ram_size);

    // Checksum
    uint8_t checksum = 0;
    for (uint16_t address = CARTRIDGE_HEADER_TITLE; address <= CARTRIDGE_HEADER_MASK_ROM_VERSION; address++) {
        checksum = checksum - data_[address] - 1;
    }

    LOG_INFO("Cartridge loaded:");
    LOG_INFO("\tTitle: {}", get_title());
    LOG_INFO("\tType: 0x{:02X} ({})", header_->cart_type, get_cart_type());
    LOG_INFO("\tROM Size: {} KB", 32 << header_->rom_size);
    LOG_INFO("\tRAM Size: 0x{:02X}", header_->ram_size);
    LOG_INFO("\tLicense Code: 0x{:02X} ({})", header_->lic_code, get_lic_name());
    LOG_INFO("\tROM Version: 0x{:02X}", header_->version);
    LOG_INFO("\tChecksum: 0x{:02X} ({})", header_->checksum, (checksum == header_->checksum) ? "PASSED" : "FAILED");
}

uint8_t Cartridge::read(const uint16_t addr) const {
    if (p_mbc_) {
        return p_mbc_->read(addr);
    }
    return data_[addr];
}

void Cartridge::write(const uint16_t addr, const uint8_t data) {
    if (p_mbc_) {
        return p_mbc_->write(addr, data);
    }
}

std::string Cartridge::get_title() const {
    std::string str(reinterpret_cast<const char*>(header_->title), 16);
    const size_t len = str.find('\0');
    return str.substr(0, len == std::string_view::npos ? 16 : len);
}

std::string Cartridge::get_cart_type() const {
    if (const auto it = CARTRIDGE_TYPES.find(header_->cart_type); it != CARTRIDGE_TYPES.end()) {
        return it->second;
    }
    return "UNKNOWN";
}

std::string Cartridge::get_lic_name() const {
    if (const auto it = LICENSE_CODES.find(header_->new_lic_code); it != LICENSE_CODES.end()) {
        return it->second;
    }
    return "UNKNOWN";
}

}  // namespace WindGB