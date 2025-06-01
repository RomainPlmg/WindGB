#pragma once

#include <vector>

#include "../mbc.h"
#include "utils/common.h"

class MBC1 : public MBC {
   public:
    MBC1(const std::vector<u8>& romData, std::vector<u8> ramData);

    virtual u8 ReadROM(u16 addr) const override;
    virtual void WriteROM(u8 data, u16 addr) override;
    virtual u8 ReadRAM(u16 addr) const override;
    virtual void WriteRAM(u8 data, u16 addr) override;

   private:
    const std::vector<u8>& m_ROM;
    std::vector<u8> m_RAM;

    u8 m_ROMBank;
    bool m_RAMEnable;
};