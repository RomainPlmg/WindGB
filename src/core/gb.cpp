#include "gb.h"

#include <SFML/Graphics.hpp>

#include "Utils/Logger.h"
#include "cartridge.h"
#include "cpu.h"
#include "memory.h"
#include "registers.h"

GB::GB() {
    m_Memory = std::make_unique<Memory>();
    m_CPU = std::make_unique<CPU>(*m_Memory);
    m_Window = std::make_unique<sf::RenderWindow>();
}

GB::~GB() {}

void GB::LoadCartridge(std::shared_ptr<Cartridge> cartridge) {
    m_Cartridge = cartridge;
    if (!m_Cartridge->GetROM().empty()) {
        LOG_INFO("Loaded cartridge, ROM size: {} Bytes", m_Cartridge->GetROM().size());
    } else {
        LOG_WARNING("Loaded cartridge, ROM empty...");
    }

    m_Memory->LoadROM(m_Cartridge->GetROM());
    m_CPU->Reset();
}

double period = 0;

void GB::Run() {
    if (m_Cartridge == nullptr) {
        LOG_WARNING("No cartridge loaded in the GameBoy");
        return;
    }

    m_Window->create(sf::VideoMode({1200, 720}), "WindGB");

    while (m_Window->isOpen()) {
        // Handle events
        while (const std::optional event = m_Window->pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) m_Window->close();
        }

        // Run the next CPU instruction
        m_CPU->RunNextInstruction();
    }
}