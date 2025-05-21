#include "ui.h"

#include <array>

#include "gfx/tile.h"

UI::UI() { m_DebugWindow = std::make_unique<sf::RenderWindow>(); }

void UI::Init(const std::string& title) {
    std::string windowTitle;
    if (title.empty()) {
        windowTitle = "WindGB";
    } else {
        windowTitle = "WindGB: " + title;
    }

    m_DebugWindow->create(sf::VideoMode({800, 600}), windowTitle);
    m_DebugWindow->setVerticalSyncEnabled(false);
}

void UI::Update(Gameboy& gameboy) {
    // Update debug window
    for (size_t y = 0; y < 24; y++) {
        for (size_t x = 0; x < 16; x++) {  // Displqy 384 tiles
            u16 index = y * 16 + x;
            DisplayTile(gameboy, 0x8000 + (index * 16), x * (16 + 1), y * (16 + 1));
        }
    }
}

void UI::Display() { m_DebugWindow->display(); }

void UI::Clear() { m_DebugWindow->clear(); }

void UI::ProcessEvents() {
    while (const std::optional event = m_DebugWindow->pollEvent()) {
        // Close window: exit
        if (event->is<sf::Event::Closed>()) m_DebugWindow->close();
    }
}

void UI::DisplayTile(Gameboy& gameboy, u16 addr, float offsetX, float offsetY) {
    Tile tile(*gameboy.GetBus(), addr);
    const u8* tilePixels = tile.GetPixels();
    sf::Texture tileTex(sf::Vector2u(TILE_SIZE, TILE_SIZE));
    tileTex.update(tilePixels);

    sf::Sprite tileSprite(tileTex);
    tileSprite.move(sf::Vector2f(offsetX, offsetY));

    m_DebugWindow->draw(tileSprite);
}
