#include "tile.h"

#include "utils/log.h"

Tile::Tile(Bus& memBus, u16 baseAddr) : m_Bus(memBus), m_BaseAddr(baseAddr) { m_Data = m_Bus.GetPointerTo(baseAddr); }

const u8* Tile::GetData() const {
    if (m_Data == nullptr) {
        LOG_ERROR("Tile data is nullptr...");
    }
    return m_Data;
}

u8* Tile::GetFramebuffer() {
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
                LOG_ERROR("Invalid color ID {0} for pixel {1}/{2}", colorID, row, column);
            } else {
                m_Framebuffer[pixelIndex] = colorID;
            }
        }
    }

    return m_Framebuffer.data();
}
