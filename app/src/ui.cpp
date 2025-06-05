#include "ui.h"

#include <array>

#include "gfx/tile.h"

UI::UI(Gameboy& gameboy) : m_Gameboy(gameboy) { m_MainWindow = std::make_unique<sf::RenderWindow>(); }

void UI::Init() {
    std::string windowTitle;
    std::string title = static_cast<std::string>(m_Gameboy.GetLoadedGame());
    if (title.empty()) {
        windowTitle = "WindGB";
    } else {
        windowTitle = "WindGB: " + title;
    }

    m_MainWindow->create(sf::VideoMode({800, 600}), windowTitle);
}

void UI::Update() {
    // Update main window
    sf::Texture lcdTex(sf::Vector2u(160, 144));
    lcdTex.update(m_Gameboy.GetPPU()->GetFramebuffer());
    sf::Sprite windowSprite(lcdTex);
    windowSprite.scale(sf::Vector2f(2.5f, 2.5f));
    m_MainWindow->draw(windowSprite);
}

void UI::Display() { m_MainWindow->display(); }

void UI::Clear() { m_MainWindow->clear(); }

void UI::ProcessEvents() {
    while (const std::optional event = m_MainWindow->pollEvent()) {
        // Close window: exit
        if (event->is<sf::Event::Closed>()) {
            m_MainWindow->close();
        }
    }
}
