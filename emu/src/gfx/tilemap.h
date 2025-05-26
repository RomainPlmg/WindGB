#pragma once

#include <array>

#include "core/bus.h"
#include "tile.h"
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
    u8 GetTileIndex(u16 index) { return *(m_Data + index); }
    Tile GetTile(u8 tileIndex);
    Tile GetTile(u8 posX, u8 posY);
    u16 GetAddr() const { return m_BaseAddr; }

   private:
    Bus& m_Bus;
    const u16 m_BaseAddr;
    const u8* m_Data;
    bool m_SignedMode;
};