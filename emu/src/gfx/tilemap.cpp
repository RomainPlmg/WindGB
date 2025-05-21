#include "tilemap.h"

#include "core/io_reg.h"
#include "tile.h"
#include "utils/exit_codes.h"
#include "utils/log.h"

TileMap::TileMap(Bus& memBus, u16 baseAddr) : m_Bus(memBus), m_BaseAddr(baseAddr) {
    if (m_BaseAddr != TILEMAP1_ADDR && m_BaseAddr != TILEMAP2_ADDR) {
        LOG_CRITICAL("Invalid address {} for tilemap creation. Abort.", m_BaseAddr);
        exit(EXIT_INTERNAL_ERROR);
    }
    m_Data = m_Bus.GetPointerTo(m_BaseAddr);
    u8 LCDC = m_Bus.Read(IO_REG_LCD_START);
    m_SignedMode = LCDC & (1 << LCDC_BG_AND_WINDOW_TILES) == 0;
}

const u8* TileMap::GetPixels() const {
    u16 targetAddr = 0x0000;
    std::array<u8, TILEMAP_WIDTH * TILEMAP_WIDTH * 4> pixels;

    if (m_SignedMode) {
        targetAddr = 0x8800;
    } else {
        targetAddr = 0x8000;
    }

    for (size_t i = 0; i < TILEMAP_SIZE; i++) {
        Tile* tile;
        u8 tileIndex = *(m_Data + i);
        if (m_SignedMode) {
            tile = new Tile(m_Bus, m_BaseAddr + static_cast<int>(tileIndex));
        } else {
            tile = new Tile(m_Bus, m_BaseAddr + tileIndex);
        }

        const u8* tilePixels = tile->GetPixels();
        for (size_t byte = 0; byte < TILE_PIXEL_SIZE; byte++) {
            u32 index = i * TILE_PIXEL_SIZE + byte;
            pixels[index] = *(tilePixels + byte);
        }
    }

    return pixels.data();
}