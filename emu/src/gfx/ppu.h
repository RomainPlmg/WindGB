#pragma once

#include <array>
#include <memory>

#include "core/bus.h"
#include "tilemap.h"
#include "tileset.h"
#include "utils/common.h"

constexpr u32 PPU_SCANLINE_CYCLES = 456;
constexpr u32 PPU_OAMSCAN_CYCLES = 80;
constexpr u32 PPU_DRAWING_CYCLES = 172;
constexpr u32 PPU_HBLANK_CYCLES = PPU_SCANLINE_CYCLES - PPU_OAMSCAN_CYCLES - PPU_DRAWING_CYCLES;
constexpr u32 PPU_NB_SCANLINES = 154;
constexpr u32 PPU_NB_LCD_SCANLINES = 144;

struct Sprite {
    u8 x;
    u8 y;
    u8 tile_index;

    bool bg_priority = false;  // false=OBJ on top of BG, true=BG on top of OBJ
    bool y_flip = false;
    bool x_flip = false;
    bool palette = false;  // false=OBP0, true=OBP1

    u16 oam_addr;

    Sprite(u8 x, u8 y, u8 tile_index) : x(x), y(y), tile_index(tile_index) {}
};

class PPU {
   public:
    PPU(Bus& memBus);
    enum class Mode { HBLANK = 0, VBLANK, OAMSCAN, DRAWING };

    void Reset();
    void Step();

    u8 Read(u16 addr) const;
    void Write(u16 addr, u8 data);

    /* Getters */
    TileSet* GetTileSet() const { return m_TileSet.get(); }
    TileMap* GetTileMap1() const { return m_TileMap1.get(); }
    TileMap* GetTileMap2() const { return m_TileMap2.get(); }
    const u8* GetFramebuffer() const { return m_FrameBuffer.data(); }
    bool ConsumeFrameBufferFlag();

   private:
    Bus& m_Bus;
    Mode m_CurrentMode = Mode::OAMSCAN;
    u32 m_ModeClock = 0;

    // Registers
    u8 m_LCDC = 0;
    u8 m_STAT = 0;
    u8 m_SCY = 0;
    u8 m_SCX = 0;
    u8 m_LY = 0;
    u8 m_LYC = 0;
    u8 m_DMA = 0;
    u8 m_BGP = 0;
    u8 m_OBP0 = 0;
    u8 m_OBP1 = 0;
    u8 m_WY = 0;
    u8 m_WX = 0;

    bool m_FramebufferReady = false;

    std::unique_ptr<TileSet> m_TileSet;
    std::unique_ptr<TileMap> m_TileMap1;
    std::unique_ptr<TileMap> m_TileMap2;
    std::vector<Sprite> m_ScanlineSprites;
    std::array<u8, 160 * 144 * 4> m_TempFrameBuffer = {0};
    std::array<u8, 160 * 144 * 4> m_FrameBuffer = {0};

    void RenderScanline();
    void EvaluateSprites();
};