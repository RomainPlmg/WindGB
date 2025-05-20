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

class IO {
   public:
    u8 Read(u16 addr) const;
    const u8* GetPointerTo(u16 address) const;
    void Write(u16 addr, u8 data);

   private:
    std::array<u8, IO_REG_SIZE> m_Data;
};