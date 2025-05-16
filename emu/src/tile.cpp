#include "tile.h"

static constexpr std::array<std::array<u8, 4>, 4> GB_COLORS = {{
    {8, 24, 32, 255},      // colorID = 0
    {52, 104, 86, 255},    // colorID = 1
    {136, 192, 112, 255},  // colorID = 2
    {224, 248, 208, 255}   // colorID = 3
}};

Tile::Tile(const u8* baseAddr) : m_Data(baseAddr) {}

void Tile::Update() {
    for (u8 row = 0; row < TILE_WIDTH; row++) {
        u8 firstByte = *(m_Data + row * 2);
        u8 secondByte = *(m_Data + row * 2 + 1);
        for (u8 column = 0; column < TILE_WIDTH; column++) {
            size_t pixelIndex = (row * TILE_WIDTH + column) * 4;
            u8 offset = 1 << (7 - column);
            u8 lo = (firstByte & offset) ? 1 : 0;
            u8 hi = (secondByte & offset) ? 1 : 0;
            u8 colorID = (hi << 1) | lo;

            const auto& color = GB_COLORS[colorID];
            m_Pixels[pixelIndex + 0] = color[0];
            m_Pixels[pixelIndex + 1] = color[1];
            m_Pixels[pixelIndex + 2] = color[2];
            m_Pixels[pixelIndex + 3] = color[3];
        }
    }
}
