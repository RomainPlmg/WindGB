#pragma once

#include <cstdint>
#include <iostream>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

/* IO registers */
// Joypad
constexpr u16 REG_JOYP_ADDR = 0xFF00;
// Serial transfer
constexpr u16 REG_SB_ADDR = 0xFF01;
constexpr u16 REG_SC_ADDR = 0xFF02;
// Timer
constexpr u16 REG_DIV_ADDR = 0xFF04;
constexpr u16 REG_TIMA_ADDR = 0xFF05;
constexpr u16 REG_TMA_ADDR = 0xFF06;
constexpr u16 REG_TAC_ADDR = 0xFF07;
// Interrupts
constexpr u16 REG_IF_ADDR = 0xFF0F;
constexpr u16 REG_IE_ADDR = 0xFFFF;
// Audio
constexpr u16 REG_NR10_ADDR = 0xFF10;
constexpr u16 REG_NR11_ADDR = 0xFF11;
constexpr u16 REG_NR12_ADDR = 0xFF12;
constexpr u16 REG_NR13_ADDR = 0xFF13;
constexpr u16 REG_NR14_ADDR = 0xFF14;
constexpr u16 REG_NR21_ADDR = 0xFF16;
constexpr u16 REG_NR22_ADDR = 0xFF17;
constexpr u16 REG_NR23_ADDR = 0xFF18;
constexpr u16 REG_NR24_ADDR = 0xFF19;
constexpr u16 REG_NR30_ADDR = 0xFF1A;
constexpr u16 REG_NR31_ADDR = 0xFF1B;
constexpr u16 REG_NR32_ADDR = 0xFF1C;
constexpr u16 REG_NR33_ADDR = 0xFF1D;
constexpr u16 REG_NR34_ADDR = 0xFF1E;
constexpr u16 REG_NR41_ADDR = 0xFF20;
constexpr u16 REG_NR42_ADDR = 0xFF21;
constexpr u16 REG_NR43_ADDR = 0xFF22;
constexpr u16 REG_NR44_ADDR = 0xFF23;
constexpr u16 REG_NR50_ADDR = 0xFF24;
constexpr u16 REG_NR51_ADDR = 0xFF25;
constexpr u16 REG_NR52_ADDR = 0xFF26;
constexpr u16 REG_WAVE_RAM_START_ADDR = 0xFF30;
constexpr u16 REG_WAVE_RAM_END_ADDR = 0xFF3F;
// LCD
constexpr u16 REG_LCDC_ADDR = 0xFF40;
constexpr u16 REG_STAT_ADDR = 0xFF41;
constexpr u16 REG_SCY_ADDR = 0xFF42;
constexpr u16 REG_SCX_ADDR = 0xFF43;
constexpr u16 REG_LY_ADDR = 0xFF44;
constexpr u16 REG_LYC_ADDR = 0xFF45;
constexpr u16 REG_DMA_ADDR = 0xFF46;
constexpr u16 REG_BGP_ADDR = 0xFF47;
constexpr u16 REG_OBP0_ADDR = 0xFF48;
constexpr u16 REG_OBP1_ADDR = 0xFF49;
constexpr u16 REG_WY_ADDR = 0xFF4A;
constexpr u16 REG_WX_ADDR = 0xFF4B;

// constexpr u16 DISABLE_BOOT_ROM_ADDR = 0xFF50;

constexpr double T_CYCLE_DURATION_US = 0.238418579;

constexpr bool GET_BIT(u32 a, u8 n) { return ((a & (1 << n)) != 0); }
constexpr bool BETWEEN(u16 addr, u16 a1, u16 a2) { return (addr >= a1) && (addr <= a2); }