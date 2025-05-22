#include "tile.h"

#include "utils/log.h"

static constexpr std::array<std::array<u8, 4>, 4> GB_COLORS = {{
    {37, 37, 37, 255},     // colorID = 0
    {70, 70, 70, 255},     // colorID = 1
    {130, 130, 130, 255},  // colorID = 2
    {180, 180, 180, 255}   // colorID = 3
}};

Tile::Tile(Bus& memBus, u16 baseAddr) : m_Bus(memBus), m_BaseAddr(baseAddr) { m_Data = m_Bus.GetPointerTo(baseAddr); }

const u8* Tile::GetData() const {
    if (m_Data == nullptr) {
        LOG_ERROR("Tile data is nullptr...");
    }
    return m_Data;
}

const u8* Tile::GetPixels() {
    for (u8 row = 0; row < TILE_WIDTH; row++) {
        u8 firstByte = *(m_Data + row * 2);
        u8 secondByte = *(m_Data + row * 2 + 1);
        for (u8 column = 0; column < TILE_WIDTH; column++) {
            size_t pixelIndex = (row * TILE_WIDTH + column) * 4;
            u8 offset = 1 << (7 - column);
            u8 lo = (firstByte & offset) ? 1 : 0;
            u8 hi = (secondByte & offset) ? 1 : 0;
            u8 colorID = (hi << 1) | lo;

            if (colorID >= 4) {
                LOG_ERROR("Invalid color ID {}", colorID);
                m_Pixels[pixelIndex + 0] = 255;
                m_Pixels[pixelIndex + 1] = 0;
                m_Pixels[pixelIndex + 2] = 0;
                m_Pixels[pixelIndex + 3] = 255;
            } else {
                const auto& color = GB_COLORS[colorID];
                m_Pixels[pixelIndex + 0] = color[0];
                m_Pixels[pixelIndex + 1] = color[1];
                m_Pixels[pixelIndex + 2] = color[2];
                m_Pixels[pixelIndex + 3] = color[3];
            }
        }
    }

    return m_Pixels.data();
}
