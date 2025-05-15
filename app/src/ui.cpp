#include "ui.h"

UI::UI() { m_DebugWindow = std::make_unique<sf::RenderWindow>(); }

void UI::Init(const std::string& title) {
    std::string windowTitle;
    if (title.empty()) {
        windowTitle = "WindGB";
    } else {
        windowTitle = "WindGB: " + title;
    }
    m_DebugWindow->create(sf::VideoMode({800, 600}), windowTitle);
}

void UI::Update() {}

void UI::Display() { m_DebugWindow->display(); }

void UI::Clear() { m_DebugWindow->clear(); }

void UI::ProcessEvents() {
    while (const std::optional event = m_DebugWindow->pollEvent()) {
        // Close window: exit
        if (event->is<sf::Event::Closed>()) m_DebugWindow->close();
    }
}
