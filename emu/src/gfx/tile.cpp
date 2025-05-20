#include "tile.h"

#include "utils/log.h"

static constexpr std::array<std::array<u8, 4>, 4> GB_COLORS = {{
    {8, 24, 32, 255},      // colorID = 0
    {52, 104, 86, 255},    // colorID = 1
    {136, 192, 112, 255},  // colorID = 2
    {224, 248, 208, 255}   // colorID = 3
}};

Tile::Tile(Bus& memBus, u16 baseAddr) : m_Bus(memBus), m_BaseAddr(baseAddr) {}

const u8* Tile::GetData() const {
    if (m_Data == nullptr) {
        LOG_ERROR("Tile data is nullptr...");
    }
    return m_Data;
}

const u8* Tile::GetPixels() const {
    std::array<u8, TILE_PIXEL_SIZE> pixels;
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
            pixels[pixelIndex + 0] = color[0];
            pixels[pixelIndex + 1] = color[1];
            pixels[pixelIndex + 2] = color[2];
            pixels[pixelIndex + 3] = color[3];
        }
    }

    return pixels.data();
}
