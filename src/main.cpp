#include <SFML/Graphics.hpp>
#include <argparse/argparse.hpp>
#include <cstdint>
#include <thread>

#include "common.hpp"
#include "windgb.hpp"

std::atomic running{true};
constexpr float GAMEBOY_ASPECT = static_cast<float>(WindGB::SCREEN_WIDTH) / WindGB::SCREEN_HEIGHT;

void update_viewport(sf::RenderWindow& window, sf::View& fixed_view) {
    const sf::Vector2u size = window.getSize();
    const float window_ratio = static_cast<float>(size.x) / static_cast<float>(size.y);

    sf::FloatRect viewport;
    if (window_ratio > GAMEBOY_ASPECT) {
        const float width = GAMEBOY_ASPECT / window_ratio;
        viewport = sf::FloatRect(sf::Vector2f((1.0f - width) / 2.0f, 0.0f), sf::Vector2f(width, 1.0f));
    } else {
        const float height = window_ratio / GAMEBOY_ASPECT;
        viewport = sf::FloatRect(sf::Vector2f(0.0f, (1.0f - height) / 2.0f), sf::Vector2f(1.0f, height));
    }

    fixed_view.setViewport(viewport);
    window.setView(fixed_view);
}

int main(int argc, char** argv) {
    std::string rom_path;

    argparse::ArgumentParser parser("windgb", "0.1.0");
    parser.add_argument("rom_path").help("Path to the ROM to load into the emulator.").store_into(rom_path);

    try {
        parser.parse_args(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        exit(EXIT_FAILURE);
    }

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "WindGB");
    window.setFramerateLimit(60);
    sf::Texture screen_texture(sf::Vector2u(160, 144));
    sf::Sprite screen_sprite(screen_texture);

    sf::View fixed_view(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(160, 144)));
    window.setView(fixed_view);

    WindGB::Logger::init();

    WindGB::Cartridge cart;
    WindGB::GameBoy gameboy;

    cart.load(rom_path);
    gameboy.insert(&cart);
    gameboy.init();

    std::thread emu_thread([&]() {
        uint64_t cycles_acc = 0;
        const auto start_time = std::chrono::high_resolution_clock::now();
        constexpr auto mcycle_duration = std::chrono::nanoseconds(952);

        while (running) {
            cycles_acc += gameboy.step();

            auto target_duration = cycles_acc * mcycle_duration;

            if (auto elapsed = std::chrono::high_resolution_clock::now() - start_time; elapsed < target_duration) {
                std::this_thread::sleep_for(target_duration - elapsed);
            }
        }
    });

    update_viewport(window, fixed_view);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                running = false;
                window.close();
            }
            if (event->is<sf::Event::Resized>()) {
                update_viewport(window, fixed_view);
            }
            if (event->is<sf::Event::KeyPressed>()) {
                auto joypad = gameboy.get_io().get_joypad();
                switch (event->getIf<sf::Event::KeyPressed>()->code) {
                    case sf::Keyboard::Key::Right:
                        joypad->set_button(WindGB::JoypadButton::RIGHT, true);
                        break;
                    case sf::Keyboard::Key::Left:
                        joypad->set_button(WindGB::JoypadButton::LEFT, true);
                        break;
                    case sf::Keyboard::Key::Up:
                        joypad->set_button(WindGB::JoypadButton::UP, true);
                        break;
                    case sf::Keyboard::Key::Down:
                        joypad->set_button(WindGB::JoypadButton::DOWN, true);
                        break;
                    case sf::Keyboard::Key::Z:
                        joypad->set_button(WindGB::JoypadButton::A, true);
                        break;
                    case sf::Keyboard::Key::X:
                        joypad->set_button(WindGB::JoypadButton::B, true);
                        break;
                    case sf::Keyboard::Key::Enter:
                        joypad->set_button(WindGB::JoypadButton::START, true);
                        break;
                    case sf::Keyboard::Key::Backspace:
                        joypad->set_button(WindGB::JoypadButton::SELECT, true);
                        break;
                    default:
                        break;
                }
            }

            if (event->is<sf::Event::KeyReleased>()) {
                auto joypad = gameboy.get_io().get_joypad();
                switch (event->getIf<sf::Event::KeyReleased>()->code) {
                    case sf::Keyboard::Key::Right:
                        joypad->set_button(WindGB::JoypadButton::RIGHT, false);
                        break;
                    case sf::Keyboard::Key::Left:
                        joypad->set_button(WindGB::JoypadButton::LEFT, false);
                        break;
                    case sf::Keyboard::Key::Up:
                        joypad->set_button(WindGB::JoypadButton::UP, false);
                        break;
                    case sf::Keyboard::Key::Down:
                        joypad->set_button(WindGB::JoypadButton::DOWN, false);
                        break;
                    case sf::Keyboard::Key::Z:
                        joypad->set_button(WindGB::JoypadButton::A, false);
                        break;
                    case sf::Keyboard::Key::X:
                        joypad->set_button(WindGB::JoypadButton::B, false);
                        break;
                    case sf::Keyboard::Key::Enter:
                        joypad->set_button(WindGB::JoypadButton::START, false);
                        break;
                    case sf::Keyboard::Key::Backspace:
                        joypad->set_button(WindGB::JoypadButton::SELECT, false);
                        break;
                    default:
                        break;
                }
            }
        }

        if (gameboy.get_ppu().is_frame_ready()) {
            screen_texture.update(reinterpret_cast<const uint8_t*>(gameboy.get_ppu().get_framebuffer()));
            gameboy.get_ppu().mark_frame_consumed();

            window.clear(sf::Color::Black);
            window.draw(screen_sprite);
            window.display();
        }
    }

    running = false;
    if (emu_thread.joinable()) emu_thread.join();
    return 0;
}