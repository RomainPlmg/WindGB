#pragma once

#include <array>

#include "core/bus.h"
#include "utils/common.h"

constexpr u16 TILEMAP1_ADDR = 0x9800;
constexpr u16 TILEMAP2_ADDR = 0x9C00;
constexpr u16 TILEMAP_SIZE = 0x400;
constexpr u16 TILEMAP_WIDTH = 256;

// For more info: https://gbdev.io/pandocs/Tile_Maps.html
class TileMap {
   public:
    TileMap(Bus& memBus, u16 baseAddr);

    /* Getters */
    const u8* GetData() const { return m_Data; }
    u16 GetAddr() const { return m_BaseAddr; }
    const u8* GetPixels();

   private:
    Bus& m_Bus;
    const u16 m_BaseAddr;
    const u8* m_Data;
    bool m_SignedMode;

    std::array<u8, TILEMAP_WIDTH * TILEMAP_WIDTH * 4> m_Pixels;
};