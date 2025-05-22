#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include <string>

#include "core/emu.h"
#include "gfx/tile.h"
#include "utils/common.h"

constexpr int UI_DEBUG_TILE_X = 24;
constexpr int UI_DEBUG_TILE_Y = 16;
constexpr int UI_DEBUG_TILE_SPACING = 1;

class UI {
   public:
    UI();
    ~UI();

    void Init(const std::string& title);
    void Update(Gameboy& gameboy);
    void Display();
    void Clear();
    void ProcessEvents();

    bool IsOpen() const { return m_DebugWindow->isOpen(); }

    /* Debug */
    void DisplayTile(u16 index, float offsetX, float offsetY, float scale = 1.0f);

   private:
    std::unique_ptr<sf::RenderWindow> m_DebugWindow;
    std::unique_ptr<sf::RenderWindow> m_MainWindow;
    std::array<sf::Texture*, 384> m_TileTextures;
};