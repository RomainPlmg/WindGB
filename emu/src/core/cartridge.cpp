#include "cartridge.h"

#include <array>
#include <fstream>
#include <unordered_map>

#include "utils/exit_codes.h"
#include "utils/log.h"

static const std::unordered_map<u8, std::string_view> CARTRIDGE_TYPES = {{0x00, "ROM ONLY"},
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
                                                                         {0x22, "MBC7+SENSOR+RUMBLE+RAM+BATTERY"}};

static const std::unordered_map<u8, std::string_view> LICENSE_CODES = {
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
    {0x96, "Yonezawa/s’pal"},
    {0x97, "Kaneko"},
    {0x99, "Pack-In-Video"},
    {0xA4, "Konami (Yu-Gi-Oh!)"},
};

Cartridge::Cartridge() {}

void Cartridge::Load(const std::string& path) {
    std::ifstream file(path, std::ios::binary | std::ios::in);
    if (!file) {
        LOG_CRITICAL("Unable to open the ROM '{}'", path);
        exit(EXIT_FILE_NOT_FOUND);
    }

    // Read file into the memory
    char byte;
    while (file.read(&byte, 1)) {
        m_Context.rom_data.push_back(static_cast<u8>(byte));
    }

    m_Context.rom_size = m_Context.rom_data.size();

    if (!file.eof()) {
        LOG_CRITICAL("ROM read failed");
        m_Context.rom_data = {0};
        exit(EXIT_INVALID_FORMAT);
    }

    // Create the MBC
    m_MBC = std::make_unique<MBC1>(m_Context.rom_data, m_Context.ram_data);

    m_Context.header = reinterpret_cast<CartridgeHeader*>(m_Context.rom_data.data() + 0x100);
    m_Context.header->title[15] = 0;  // Remove the \0 character

    // Checksum
    u8 x = 0;
    for (uint16_t address = 0x0134; address <= 0x014C; address++) {
        x = x - m_Context.rom_data[address] - 1;
    }

    LOG_INFO("Cartridge loaded:");
    LOG_INFO("\tTitle: {}", m_Context.header->GetTitle());
    LOG_INFO("\tType: 0x{:02X} ({})", m_Context.header->cart_type, m_Context.header->GetCartridgeType());
    LOG_INFO("\tROM Size: {} KB", 32 << m_Context.header->rom_size);
    LOG_INFO("\tRAM Size: 0x{:02X}", m_Context.header->ram_size);
    LOG_INFO("\tLicense Code: 0x{:02X} ({})", m_Context.header->lic_code, m_Context.header->GetLicenseName());
    LOG_INFO("\tROM Version: 0x{:02X}", m_Context.header->version);
    LOG_INFO("\tChecksum: 0x{:02X} ({})", m_Context.header->checksum, (x & 0xFF) ? "PASSED" : "FAILED");
}

u8 Cartridge::Read(u16 addr) const { return m_MBC->ReadROM(addr); }

const u8* Cartridge::GetPointerTo(u16 addr) const {
    if (BETWEEN(addr, CARTRIDGE_FIXED_ROM_BANK_START_ADDR, CARTRIDGE_SWITCHABLE_ROM_BANK_START_ADDR - 1)) {
        // TODO: Get pointer in fixed ROM bank
        return &m_Context.rom_data.at(addr);
    } else if (BETWEEN(addr, CARTRIDGE_SWITCHABLE_ROM_BANK_START_ADDR, CARTRIDGE_SWITCHABLE_ROM_BANK_START_ADDR + CARTRIDGE_ROM_BANK_SIZE - 1)) {
        // TODO: Get pointer in switchable ROM bank
    } else if (BETWEEN(addr, CARTRIDGE_EXTERNAL_RAM_BANK_START_ADDR, CARTRIDGE_EXTERNAL_RAM_BANK_START_ADDR + CARTRIDGE_RAM_BANK_SIZE - 1)) {
        // TODO: Get pointer in external RAM bank
    }

    return nullptr;
}

void Cartridge::Write(u16 addr, u8 data) { m_MBC->WriteROM(data, addr); }

std::string_view CartridgeHeader::GetLicenseName() const {
    auto it = LICENSE_CODES.find(new_lic_code);
    if (it != LICENSE_CODES.end()) {
        return it->second;
    }
    return "UNKNOWN";
}

std::string_view CartridgeHeader::GetCartridgeType() const {
    auto it = CARTRIDGE_TYPES.find(cart_type);
    if (it != CARTRIDGE_TYPES.end()) {
        return it->second;
    }
    return "UNKNOWN";
}

std::string_view CartridgeHeader::GetTitle() const {
    std::string_view view(reinterpret_cast<const char*>(title), 16);
    size_t len = view.find('\0');
    return view.substr(0, len == std::string_view::npos ? 16 : len);
}
