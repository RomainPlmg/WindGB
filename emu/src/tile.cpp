#include "tile.h"

Tile::Tile(u8* baseAddr) : m_Data(baseAddr) {}

std::array<u8, TILE_WIDTH * TILE_WIDTH * 4> Tile::GetPixels() const {
    std::array<u8, TILE_WIDTH * TILE_WIDTH * 4> pixels;

    for (u8 row = 0; row < TILE_WIDTH; row++) {
        u8 firstByte = *(m_Data + row * 2);
        u8 secondByte = *(m_Data + row * 2 + 1);

        for (u8 column = 0; column < TILE_WIDTH; column++) {
            u8 offset = 1 << (7 - column);
            u8 colorID = (firstByte & offset) << 1 | (secondByte & offset);

            switch (colorID) {
                case 0:

                    break;

                default:
                    break;
            }
        }
    }

    return pixels;
}
