#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class UI {
   public:
    UI();

    void Init(const std::string& title);
    void Update();
    void Display();
    void Clear();
    void ProcessEvents();

    bool IsOpen() const { return m_DebugWindow->isOpen(); }

   private:
    std::unique_ptr<sf::RenderWindow> m_DebugWindow;
};