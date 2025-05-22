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
    m_SignedMode = (LCDC & (1 << LCDC_BG_AND_WINDOW_TILES)) == 0;
}

const u8* TileMap::GetPixels() {
    for (size_t i = 0; i < TILEMAP_SIZE; i++) {
        u16 tileAddr;
        u8 tileIndex = *(m_Data + i);
        if (m_SignedMode) {
            tileAddr = 0x9000 + static_cast<int>(tileIndex) * TILE_SIZE;
        } else {
            tileAddr = 0x8000 + tileIndex * TILE_SIZE;
        }

        Tile tile(m_Bus, tileAddr);
        const u8* tilePixels = tile.GetPixels();

        u32 tilePosX = i % (TILEMAP_WIDTH / TILE_WIDTH);
        u32 tilePosY = i / (TILEMAP_WIDTH / TILE_WIDTH);

        for (size_t y = 0; y < TILE_WIDTH; y++) {
            for (size_t x = 0; x < TILE_WIDTH; x++) {
                u16 tilePixelIndex = (y * TILE_WIDTH + x) * 4;

                u32 pixelGlobalPosX = tilePosX * TILE_WIDTH + x;
                u32 pixelGlobalPosY = tilePosY * TILE_WIDTH + y;

                size_t pixelIndex = (pixelGlobalPosY * TILEMAP_WIDTH + pixelGlobalPosX) * 4;
                m_Pixels[pixelIndex + 0] = *(tilePixels + tilePixelIndex + 0);
                m_Pixels[pixelIndex + 1] = *(tilePixels + tilePixelIndex + 1);
                m_Pixels[pixelIndex + 2] = *(tilePixels + tilePixelIndex + 2);
                m_Pixels[pixelIndex + 3] = *(tilePixels + tilePixelIndex + 3);
            }
        }
    }

    return m_Pixels.data();
}