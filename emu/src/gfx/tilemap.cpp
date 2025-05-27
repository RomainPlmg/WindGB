#include "tilemap.h"

#include "core/io_reg.h"
#include "utils/exit_codes.h"
#include "utils/log.h"

TileMap::TileMap(Bus& memBus, u16 baseAddr) : m_Bus(memBus), m_BaseAddr(baseAddr) {
    if (m_BaseAddr != TILEMAP1_ADDR && m_BaseAddr != TILEMAP2_ADDR) {
        LOG_CRITICAL("Invalid address {} for tilemap creation. Abort.", m_BaseAddr);
        exit(EXIT_INTERNAL_ERROR);
    }
    m_Data = m_Bus.GetPointerTo(m_BaseAddr);
    u8 LCDC = m_Bus.Read(IO_REG_LCD_START);
    m_SignedMode = GET_BIT(LCDC, LCDC_BG_AND_WINDOW_TILES) == 0;
}

u16 TileMap::GetTileAddr(u8 posX, u8 posY) {
    u16 index = posX + posY * (TILEMAP_WIDTH / TILE_WIDTH);
    u8 tileIndex = *(m_Data + index);
    u16 tileAddr;
    u8 LCDC = m_Bus.Read(IO_REG_LCD_START);
    m_SignedMode = GET_BIT(LCDC, LCDC_BG_AND_WINDOW_TILES) == 0;
    if (m_SignedMode) {
        tileAddr = 0x9000 + static_cast<int8_t>(tileIndex) * TILE_SIZE;
    } else {
        tileAddr = 0x8000 + tileIndex * TILE_SIZE;
    }

    return tileAddr;
}