#pragma once

#include <array>

#include "common.h"

constexpr u16 WRAM_ADDR_START = 0xC000;
constexpr u16 WRAM_ADDR_SIZE = 0x2000;

constexpr u16 WRAM_ECHO_ADDR_START = 0xE000;
constexpr u16 WRAM_ECHO_ADDR_SIZE = 0x2000;

constexpr u16 HRAM_ADDR_START = 0xFF80;
constexpr u16 HRAM_ADDR_SIZE = 0x007F;

constexpr u16 VRAM_ADDR_START = 0x8000;
constexpr u16 VRAM_ADDR_SIZE = 0x2000;

class WRAM {
   public:
    u8 Read(u16 addr) const;
    void Write(u16 addr, u8 data);

   private:
    std::array<u8, WRAM_ADDR_SIZE> m_Data;
};

class HRAM {
   public:
    u8 Read(u16 addr) const;
    void Write(u16 addr, u8 data);

   private:
    std::array<u8, HRAM_ADDR_SIZE> m_Data;
};

class VRAM {
   public:
    u8 Read(u16 addr) const;
    void Write(u16 addr, u8 data);

   private:
    std::array<u8, VRAM_ADDR_SIZE> m_Data;
};