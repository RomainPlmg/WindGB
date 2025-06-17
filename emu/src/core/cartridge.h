#pragma once

#include <memory>
#include <string>
#include <vector>

#include "mbc/mbc1.h"
#include "utils/common.h"

constexpr u16 CARTRIDGE_FIXED_ROM_BANK_START_ADDR = 0x0000;
constexpr u16 CARTRIDGE_FIXED_ROM_BANK_END_ADDR = 0x3FFF;
constexpr u16 CARTRIDGE_SWITCHABLE_ROM_BANK_START_ADDR = 0x4000;
constexpr u16 CARTRIDGE_EXTERNAL_RAM_BANK_START_ADDR = 0xA000;
constexpr u16 CARTRIDGE_SWITCHABLE_ROM_BANK_END_ADDR = 0x7FFF;
constexpr u16 CARTRIDGE_EXTERNAL_RAM_BANK_END_ADDR = 0xBFFF;
constexpr u16 CARTRIDGE_ROM_BANK_SIZE = 0x4000;
constexpr u16 CARTRIDGE_RAM_BANK_SIZE = 0x2000;

struct CartridgeHeader {
    u8 entry[4];          // 0x0100-0x0103 -> Entry point
    u8 logo[48];          // 0x0104-0x0133 -> Nintendo logo
    u8 title[16];         // 0x0134-0x0143 -> Title
    u16 new_lic_code;     // 0x0144-0x0145 -> Code of the game publisher
    u8 sgb_flag;          // 0x0146 -> Is game supports SGB function ? (Yes if 0x03)
    u8 cart_type;         // 0x0147 -> Cartridge type
    u8 rom_size;          // 0x0148 -> ROM size on the cartridge
    u8 ram_size;          // 0x0149 -> RAM size on the cartridge
    u8 dest_code;         // 0x014A -> Sold in Japan or elsewhere
    u8 lic_code;          // 0x014B -> Old code of the game publisher
    u8 version;           // 0x014C -> Version of the game
    u8 checksum;          // 0x014D -> Compute the cartridge header bytes 0x0134-0x014C
    u16 global_checksum;  // 0x014E-0x014F -> Global checksum

    std::string_view GetLicenseName() const;
    std::string_view GetCartridgeType() const;
    std::string_view GetTitle() const;
};

class Cartridge {
   public:
    Cartridge();
    ~Cartridge();
    void Load(const std::string& path);

    u8 Read(u16 addr) const;
    const u8* GetPointerTo(u16 address) const;
    void Write(u16 addr, u8 data);

    /* Getters */
    const CartridgeHeader* GetHeader() const { return m_Header; }
    const std::string& GetFilename() const { return m_Filename; }
    u32 GetROMSize() const { return m_ROMSize; }
    const std::vector<u8>& GetROMData() const { return m_ROMData; }

   private:
    std::unique_ptr<MBC1> m_MBC;
    CartridgeHeader* m_Header;
    std::string m_Filename;
    u32 m_ROMSize = 0;
    std::vector<u8> m_ROMData;
};