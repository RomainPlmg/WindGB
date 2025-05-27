#pragma once

#include <array>
#include <memory>

#include "core/bus.h"
#include "tile.h"
#include "utils/common.h"

constexpr int TILE_NB = 384;

class TileSet {
   public:
    TileSet(Bus& memBus);
    void Update();

    /* Getters */
    const Tile* GetTile(u16 addr);

   private:
    Bus& m_Bus;
    std::array<std::unique_ptr<Tile>, TILE_NB> m_Tiles;
};