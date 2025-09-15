#pragma once

#include <cstdint>

namespace WindGB {

constexpr uint16_t CARTRIDGE_HEADER_ENTRY_POINT = 0x0100;
constexpr uint16_t CARTRIDGE_HEADER_NINTENDO_LOGO = 0x0104;
constexpr uint16_t CARTRIDGE_HEADER_TITLE = 0x0134;
constexpr uint16_t CARTRIDGE_HEADER_MANUFACTURER_CODE = 0x013F;
constexpr uint16_t CARTRIDGE_HEADER_CGB_FLAG = 0x0143;
constexpr uint16_t CARTRIDGE_HEADER_NEW_LIC_CODE = 0x0144;
constexpr uint16_t CARTRIDGE_HEADER_SGB_FLAG = 0x0146;
constexpr uint16_t CARTRIDGE_HEADER_CARTRIDGE_TYPE = 0x0147;
constexpr uint16_t CARTRIDGE_HEADER_ROM_SIZE = 0x0148;
constexpr uint16_t CARTRIDGE_HEADER_RAM_SIZE = 0x0149;
constexpr uint16_t CARTRIDGE_HEADER_DEST_CODE = 0x014A;
constexpr uint16_t CARTRIDGE_HEADER_OLD_LIC_CODE = 0x014B;
constexpr uint16_t CARTRIDGE_HEADER_MASK_ROM_VERSION = 0x014C;
constexpr uint16_t CARTRIDGE_HEADER_CHECKSUM = 0x014D;
constexpr uint16_t CARTRIDGE_HEADER_GLOBAL_CHECKSUM = 0x014E;
constexpr uint16_t WRAM_ADDR_START = 0xC000;
constexpr uint16_t WRAM_ADDR_END = WRAM_ADDR_START + 0x2000 - 1;
constexpr uint16_t WRAM_ECHO_ADDR_START = 0xE000;
constexpr uint16_t WRAM_ECHO_ADDR_END = WRAM_ECHO_ADDR_START + 0x1E00 - 1;
constexpr uint16_t HRAM_ADDR_START = 0xFF80;
constexpr uint16_t HRAM_ADDR_END = HRAM_ADDR_START + 0x007F - 1;
constexpr uint16_t VRAM_ADDR_START = 0x8000;
constexpr uint16_t VRAM_ADDR_END = VRAM_ADDR_START + 0x2000 - 1;
constexpr uint16_t OAM_ADDR_START = 0xFE00;
constexpr uint16_t OAM_ADDR_END = OAM_ADDR_START + 0x00A0 - 1;
constexpr uint16_t IO_ADDR_START = 0xFF00;
constexpr uint16_t IO_ADDR_END = IO_ADDR_START + 0x0080 - 1;

// Joypad reg
constexpr uint16_t REG_JOYP_ADDR = 0xFF00;
// Serial transfer reg
constexpr uint16_t REG_SB_ADDR = 0xFF01;
constexpr uint16_t REG_SC_ADDR = 0xFF02;
// Timer reg
constexpr uint16_t REG_DIV_ADDR = 0xFF04;
constexpr uint16_t REG_TIMA_ADDR = 0xFF05;
constexpr uint16_t REG_TMA_ADDR = 0xFF06;
constexpr uint16_t REG_TAC_ADDR = 0xFF07;
// Interrupts reg
constexpr uint16_t REG_IF_ADDR = 0xFF0F;
constexpr uint16_t REG_IE_ADDR = 0xFFFF;
// Audio reg
constexpr uint16_t REG_NR10_ADDR = 0xFF10;
constexpr uint16_t REG_NR11_ADDR = 0xFF11;
constexpr uint16_t REG_NR12_ADDR = 0xFF12;
constexpr uint16_t REG_NR13_ADDR = 0xFF13;
constexpr uint16_t REG_NR14_ADDR = 0xFF14;
constexpr uint16_t REG_NR21_ADDR = 0xFF16;
constexpr uint16_t REG_NR22_ADDR = 0xFF17;
constexpr uint16_t REG_NR23_ADDR = 0xFF18;
constexpr uint16_t REG_NR24_ADDR = 0xFF19;
constexpr uint16_t REG_NR30_ADDR = 0xFF1A;
constexpr uint16_t REG_NR31_ADDR = 0xFF1B;
constexpr uint16_t REG_NR32_ADDR = 0xFF1C;
constexpr uint16_t REG_NR33_ADDR = 0xFF1D;
constexpr uint16_t REG_NR34_ADDR = 0xFF1E;
constexpr uint16_t REG_NR41_ADDR = 0xFF20;
constexpr uint16_t REG_NR42_ADDR = 0xFF21;
constexpr uint16_t REG_NR43_ADDR = 0xFF22;
constexpr uint16_t REG_NR44_ADDR = 0xFF23;
constexpr uint16_t REG_NR50_ADDR = 0xFF24;
constexpr uint16_t REG_NR51_ADDR = 0xFF25;
constexpr uint16_t REG_NR52_ADDR = 0xFF26;
constexpr uint16_t REG_WAVE_RAM_START_ADDR = 0xFF30;
constexpr uint16_t REG_WAVE_RAM_END_ADDR = 0xFF3F;
// LCD reg
constexpr uint16_t REG_LCDC_ADDR = 0xFF40;
constexpr uint16_t REG_STAT_ADDR = 0xFF41;
constexpr uint16_t REG_SCY_ADDR = 0xFF42;
constexpr uint16_t REG_SCX_ADDR = 0xFF43;
constexpr uint16_t REG_LY_ADDR = 0xFF44;
constexpr uint16_t REG_LYC_ADDR = 0xFF45;
constexpr uint16_t REG_DMA_ADDR = 0xFF46;
constexpr uint16_t REG_BGP_ADDR = 0xFF47;
constexpr uint16_t REG_OBP0_ADDR = 0xFF48;
constexpr uint16_t REG_OBP1_ADDR = 0xFF49;
constexpr uint16_t REG_WY_ADDR = 0xFF4A;
constexpr uint16_t REG_WX_ADDR = 0xFF4B;

// Misc info
constexpr uint16_t TILE_DATA_0 = 0x8000;
constexpr uint16_t TILE_DATA_1 = 0x8800;
constexpr uint16_t TILE_MAP_0 = 0x9800;
constexpr uint16_t TILE_MAP_1 = 0x9C00;
constexpr uint16_t SCREEN_WIDTH = 160;
constexpr uint16_t SCREEN_HEIGHT = 144;

constexpr bool GET_BIT(uint32_t a, uint8_t n) { return ((a & (1 << n)) != 0); }

}  // namespace WindGB