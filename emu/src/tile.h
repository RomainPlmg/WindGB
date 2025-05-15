#pragma once

#include <array>

#include "common.h"

constexpr u8 TILE_SIZE = 16;

// For more info: https://gbdev.io/pandocs/Tile_Data.html
class Tile {
   public:
    Tile(u16 addr);
   private:
    std::array<u8, TILE_SIZE> m_Data;
};