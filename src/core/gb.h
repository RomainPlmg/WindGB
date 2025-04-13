#ifndef __GB_H__
#define __GB_H__

#include <memory>

class CPU;
class Memory;
class Cartridge;

namespace sf {
class RenderWindow;
}  // namespace sf

class GB {
   public:
    GB();
    ~GB();

    void LoadCartridge(std::shared_ptr<Cartridge> cartridge);
    void Run();

   private:
    std::unique_ptr<CPU> m_CPU;
    std::unique_ptr<Memory> m_Memory;
    std::shared_ptr<Cartridge> m_Cartridge;
    std::unique_ptr<sf::RenderWindow> m_Window;
};

#endif  // __GB_H__