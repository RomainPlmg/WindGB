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

class PPU {
   public:
    PPU(Bus& memBus);
    enum class Mode { HBLANK = 0, VBLANK, OAMSCAN, DRAWING };

    void Init();
    void Step(u8 cycles);

    /* Getters */
    TileSet* GetTileSet() const { return m_TileSet.get(); }
    TileMap* GetTileMap1() const { return m_TileMap1.get(); }
    TileMap* GetTileMap2() const { return m_TileMap2.get(); }
    const u8* GetFramebuffer() const { return m_FrameBuffer.data(); }
    bool IsFramebufferReady() const { return m_FramebufferReady; }

   private:
    Mode m_CurrentMode;
    u32 m_ModeClock;
    u32 m_LY;
    Bus& m_Bus;
    bool m_FramebufferReady;

    std::unique_ptr<TileSet> m_TileSet;
    std::unique_ptr<TileMap> m_TileMap1;
    std::unique_ptr<TileMap> m_TileMap2;
    std::array<u8, 160 * 144 * 4> m_TempFrameBuffer = {0};
    std::array<u8, 160 * 144 * 4> m_FrameBuffer = {0};

    void RenderScanline();
};