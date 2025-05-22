#include "ui.h"

#include <array>

#include "gfx/tile.h"
#include "gfx/tilemap.h"

UI::UI() {
    m_DebugWindow = std::make_unique<sf::RenderWindow>();
    m_MainWindow = std::make_unique<sf::RenderWindow>();
}

UI::~UI() {
    for (size_t i = 0; i < 384; i++) {
        delete m_TileTextures[i];
    }
}

void UI::Init(const std::string& title) {
    std::string windowTitle;
    if (title.empty()) {
        windowTitle = "WindGB";
    } else {
        windowTitle = "WindGB: " + title;
    }

    m_DebugWindow->create(sf::VideoMode({800, 600}), std::string(windowTitle + " (Debug)"));
    m_MainWindow->create(sf::VideoMode({800, 600}), windowTitle);

    for (size_t i = 0; i < 384; i++) {
        m_TileTextures[i] = new sf::Texture(sf::Vector2u(TILE_WIDTH, TILE_WIDTH));
    }
}

void UI::Update(Gameboy& gameboy) {
    // Update debug window
    for (size_t y = 0; y < UI_DEBUG_TILE_Y; y++) {
        for (size_t x = 0; x < UI_DEBUG_TILE_X; x++) {  // Display 384 tiles
            u16 index = y * UI_DEBUG_TILE_X + x;
            Tile tile(*gameboy.GetBus(), 0x8000 + index * 16);
            m_TileTextures[index]->update(tile.GetPixels());
            DisplayTile(index, x * (TILE_WIDTH + UI_DEBUG_TILE_SPACING), y * (TILE_WIDTH + UI_DEBUG_TILE_SPACING), 2.5f);
        }
    }

    // Update main window
    TileMap tilemap(*gameboy.GetBus(), TILEMAP1_ADDR);
    sf::Texture tileMapTex(sf::Vector2u(TILEMAP_WIDTH, TILEMAP_WIDTH));
    tileMapTex.update(tilemap.GetPixels());

    sf::Sprite tileMapSprite(tileMapTex);
    tileMapSprite.move(sf::Vector2f(25.0f, 25.0f));
    tileMapSprite.scale(sf::Vector2f(2.0f, 2.0f));
    m_MainWindow->draw(tileMapSprite);
}

void UI::Display() {
    m_DebugWindow->display();
    m_MainWindow->display();
}

void UI::Clear() {
    m_DebugWindow->clear();
    m_MainWindow->clear();
}

void UI::ProcessEvents() {
    while (const std::optional event = m_DebugWindow->pollEvent()) {
        // Close window: exit
        if (event->is<sf::Event::Closed>()) m_DebugWindow->close();
    }

    while (const std::optional event = m_MainWindow->pollEvent()) {
        // Close window: exit
        if (event->is<sf::Event::Closed>()) m_MainWindow->close();
    }
}

void UI::DisplayTile(u16 index, float offsetX, float offsetY, float scale) {
    sf::Sprite tileSprite(*m_TileTextures[index]);
    tileSprite.scale(sf::Vector2f(scale, scale));
    tileSprite.move(sf::Vector2f(offsetX * scale, offsetY * scale));

    m_DebugWindow->draw(tileSprite);
}
