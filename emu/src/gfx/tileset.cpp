#include "tileset.h"

#include "utils/log.h"

TileSet::TileSet(Bus& memBus) : m_Bus(memBus) {
    for (int i = 0; i < TILE_NB; i++) {
        u16 tileAddr = 0x8000 + i * TILE_SIZE;
        m_Tiles[i] = std::make_unique<Tile>(m_Bus, tileAddr);
    }
}

const Tile* TileSet::GetTile(u16 addr) {
    if (addr < 0x8000 || addr > 0x97FF) {
        LOG_ERROR("Invalid address {} for tile, need to be in range 0x8000 - 0x97FF", addr);
        return nullptr;
    }

    u16 tileIndex = (addr - 0x8000) / TILE_SIZE;
    return m_Tiles[tileIndex].get();
}

void TileSet::Update() {
    for (auto& tile : m_Tiles) {
        tile->Update();
    }
}
