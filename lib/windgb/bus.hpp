#pragma once

#include <string>
#include <vector>

#include "component.hpp"
#include "io.hpp"
#include "ppu.hpp"
#include "timer.hpp"

namespace WindGB {

class Bus {
   public:
    Bus();
    void link(Component* component, uint16_t start_addr, uint16_t end_addr, const std::string& name = "", uint16_t offset = 0);

    [[nodiscard]] uint8_t direct_read(uint16_t addr) const;
    void direct_write(uint16_t addr, uint8_t data);
    [[nodiscard]] uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);
    void cycles(uint8_t count);

    void link_ppu(PPU* ppu) { p_ppu_ = ppu; }
    void link_timer(Timer* timer) { p_timer_ = timer; }

    uint64_t get_tick() const { return tick_; }

    [[nodiscard]] std::string memap_to_string() const;

   private:
    struct MemoryRegion {
        uint16_t start;
        uint16_t end;
        uint16_t offset;
        Component* component;
        std::string name;

        [[nodiscard]] bool contains(uint16_t address) const { return address >= start && address <= end; }
    };

    std::vector<MemoryRegion> regions_;
    uint8_t ie_reg_ = 0;
    uint64_t tick_ = 0;
    std::array<uint8_t, 256> boot_rom_;
    bool boot_rom_enabled_ = true;
    PPU* p_ppu_ = nullptr;
    Timer* p_timer_ = nullptr;
    bool dma_active_ = false;
    uint8_t dma_cycles_remaining_ = 0;
    uint16_t dma_src_addr_ = 0;
    IO* io_ = nullptr;

    void start_dma_transfer(uint8_t data);
    [[nodiscard]] bool is_dma_restricted_area(uint16_t addr) const;
};

}  // namespace WindGB