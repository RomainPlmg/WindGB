#pragma once

#include <array>

#include "utils/common.h"

constexpr u16 IO_REG_START = 0xFF00;
constexpr u16 IO_REG_SIZE = 0x0080;

constexpr u16 IO_REG_JOYPAD_INPUT = 0xFF00;
constexpr u16 IO_REG_SERIAL_TRANSFER_START = 0xFF01;
constexpr u16 IO_REG_SERIAL_TRANSFER_END = 0xFF02;
constexpr u16 IO_REG_TIMER_AND_DIV_START = 0xFF04;
constexpr u16 IO_REG_TIMER_AND_DIV_END = 0xFF07;
constexpr u16 IO_REG_INTERRUPT_FLAGS = 0xFF0F;
constexpr u16 IO_REG_AUDIO_START = 0xFF10;
constexpr u16 IO_REG_AUDIO_END = 0xFF26;
constexpr u16 IO_REG_WAVE_PATTERN_START = 0xFF30;
constexpr u16 IO_REG_WAVE_PATTERN_END = 0xFF3F;
constexpr u16 IO_REG_LCD_START = 0xFF40;
constexpr u16 IO_REG_LCD_END = 0xFF4B;
constexpr u16 IO_REG_DISABLE_BOOT_ROM = 0xFF50;

// LCD Control Register globals (0xFF40)
constexpr u8 LCDC_BG_WINDOW_EN_PRIORITY = 0;
constexpr u8 LCDC_OBJ_EN = 1;
constexpr u8 LCDC_OBJ_SIZE = 2;
constexpr u8 LCDC_BG_TILE_MAP = 3;
constexpr u8 LCDC_BG_AND_WINDOW_TILES = 4;
constexpr u8 LCDC_WINDOW_EN = 5;
constexpr u8 LCDC_WINDOW_TILEMAP = 6;
constexpr u8 LCDC_AND_PPU_EN = 7;

// LCD Status Registers
constexpr u16 LCDS_STAT_ADDR = 0xFF41;
constexpr u16 LCDS_LY_ADDR = 0xFF44;
constexpr u16 LCDS_LYC_ADDR = 0xFF45;

// Scrolling
constexpr u16 LCD_SCY_ADDR = 0xFF42;
constexpr u16 LCD_SCX_ADDR = 0xFF43;
constexpr u16 LCD_WY_ADDR = 0xFF4A;
constexpr u16 LCD_WX_ADDR = 0xFF4B;

// Palettes
constexpr u16 LCD_BGP_ADDR = 0xFF47;
constexpr u16 LCD_OBP0_ADDR = 0xFF48;
constexpr u16 LCD_OBP1_ADDR = 0xFF49;

class IO {
   public:
    u8 Read(u16 addr) const;
    const u8* GetPointerTo(u16 address) const;
    void Write(u16 addr, u8 data);

   private:
    std::array<u8, IO_REG_SIZE> m_Data;
};