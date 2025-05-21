#pragma once

#include <array>

#include "core/bus.h"
#include "utils/common.h"

constexpr u8 TILE_SIZE = 16;                                  // Nb bytes for a tile
constexpr u8 TILE_WIDTH = 8;                                  // Width of the tile in term of pixels
constexpr u16 TILE_PIXEL_SIZE = TILE_WIDTH * TILE_WIDTH * 4;  // Nb bytes for a tile pixel array

// For more info: https://gbdev.io/pandocs/Tile_Data.html
class Tile {
   public:
    Tile(Bus& memBus, u16 baseAddr);

    /* Getters */
    u16 GetAddr() const { return m_BaseAddr; }
    const u8* GetData() const;
    const u8* GetPixels();

   private:
    Bus& m_Bus;
    u16 m_BaseAddr;
    const u8* m_Data;
    std::array<u8, TILE_PIXEL_SIZE> m_Pixels;
};