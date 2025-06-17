#pragma once

#include <array>

#include "utils/common.h"

constexpr u16 OAM_ADDR_START = 0xFE00;
constexpr u16 OAM_ADDR_SIZE = 0x00A0;
constexpr u16 OAM_ADDR_END = OAM_ADDR_START + OAM_ADDR_SIZE - 1;

class OAM {
   public:
    OAM();

    u8 Read(u16 addr) const;
    const u8* GetPointerTo(u16 address) const;
    void Write(u16 addr, u8 data);

   private:
    std::array<u8, OAM_ADDR_SIZE> m_Data = {0};
};