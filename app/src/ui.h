#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "core/emu.h"
#include "utils/common.h"

class UI {
   public:
    UI();

    void Init(const std::string& title);
    void Update(Gameboy& gameboy);
    void Display();
    void Clear();
    void ProcessEvents();

    bool IsOpen() const { return m_DebugWindow->isOpen(); }

    /* Debug */
    void DisplayTile(Gameboy& gameboy, u16 addr, float offsetX, float offsetY);

   private:
    std::unique_ptr<sf::RenderWindow> m_DebugWindow;
};