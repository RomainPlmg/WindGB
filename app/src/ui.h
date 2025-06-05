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
    UI(Gameboy& gameboy);

    void Init();
    void Update();
    void Display();
    void Clear();
    void ProcessEvents();
    bool IsOpen() const { return m_MainWindow->isOpen(); }

   private:
    Gameboy& m_Gameboy;
    std::unique_ptr<sf::RenderWindow> m_MainWindow;
};