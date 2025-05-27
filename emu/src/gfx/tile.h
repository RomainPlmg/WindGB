#pragma once

#include <array>

#include "core/bus.h"
#include "utils/common.h"

constexpr int TILE_SIZE = 16;  // Nb bytes for a tile
constexpr int TILE_WIDTH = 8;  // Width of the tile in term of pixels

// For more info: https://gbdev.io/pandocs/Tile_Data.html
class Tile {
   public:
    Tile(Bus& memBus, u16 baseAddr);
    void Update();

    /* Getters */
    u16 GetAddr() const { return m_BaseAddr; }
    const u8* GetData() const { return m_Data.data(); }
    const u8* GetFramebuffer() const { return m_Framebuffer.data(); }

   private:
    Bus& m_Bus;
    u16 m_BaseAddr;
    std::array<u8, TILE_WIDTH * TILE_WIDTH> m_Data;
    std::array<u8, TILE_WIDTH * TILE_WIDTH * 4> m_Framebuffer;
};