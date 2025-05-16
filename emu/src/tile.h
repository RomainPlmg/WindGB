#pragma once

#include <array>

#include "common.h"

constexpr u8 TILE_SIZE = 16;  // Nb bytes for a tile
constexpr u8 TILE_WIDTH = 8;  // Width of the tile in term of pixels

// For more info: https://gbdev.io/pandocs/Tile_Data.html
class Tile {
   public:
    Tile(const u8* baseAddr);
    void Update();
    const u8* GetPixels() const { return m_Pixels.data(); }

   private:
    const u8* m_Data;
    std::array<u8, TILE_WIDTH * TILE_WIDTH * 4> m_Pixels;
};