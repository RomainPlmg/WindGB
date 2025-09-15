#include "bus.hpp"

#include <algorithm>
#include <cstdint>
#include <fstream>

#include "common.hpp"
#include "logger.hpp"
#include "utils.hpp"

namespace WindGB {

Bus::Bus() {
    std::string boot_rom_path = PROJECT_SRC + std::string("/boot_rom.bin");
    std::ifstream file(boot_rom_path, std::ios::binary | std::ios::in);
    if (!file) {
        throw std::runtime_error("Unable to open the ROM \'" + boot_rom_path + "\'");
    }

    // Read file into the memory
    char byte;
    int i = 0;
    while (file.read(&byte, 1)) {
        boot_rom_[i] = static_cast<uint8_t>(byte);
        i++;
    }

    if (!file.eof()) {
        throw std::runtime_error("Boot ROM read failed");
    }
}

void Bus::link(Component* component, uint16_t start_addr, uint16_t end_addr, const std::string& name, uint16_t offset) {
    regions_.push_back({start_addr, end_addr, offset, component, name});

    // Try to recover IO class (for joypad udpate)
    io_ = dynamic_cast<IO*>(component);

    LOG_INFO("Linked {} at 0x{:04X}-0x{:04X}", regions_.back().name, start_addr, end_addr);
    std::ranges::sort(regions_, [](const auto& a, const auto& b) { return a.start < b.start; });
}

uint8_t Bus::direct_read(uint16_t addr) const {
    if (addr >= 0xFEA0 && addr <= 0xFEFF) return 0xFF;  // Prohibited
    if (addr == REG_IE_ADDR) return ie_reg_;

    for (const auto& region : regions_) {
        if (region.contains(addr)) {
            return region.component->read(addr - region.offset);
        }
    }

    LOG_WARN("Unmapped read at 0x{:04X}", addr);
    return 0xFF;  // Open bus
}

void Bus::direct_write(uint16_t addr, uint8_t data) {
    if (addr >= 0xFEA0 && addr <= 0xFEFF) {  // Prohibited
        return;
    }
    if (addr == REG_IE_ADDR) {
        ie_reg_ = data;
        return;
    }
    if (addr == REG_DIV_ADDR) {
        assert(p_timer_);
        p_timer_->reset_counter();
        return;
    }

    for (const auto& region : regions_) {
        if (region.contains(addr)) {
            region.component->write(addr - region.offset, data);
            return;
        }
    }

    LOG_WARN("Unmapped write at 0x{:04X} = 0x{:02X}", addr, data);
}

uint8_t Bus::read(const uint16_t addr) {
    cycles(1);
    if (is_dma_restricted_area(addr) && dma_active_) {
        return 0xFF;
    }
    if (boot_rom_enabled_ && addr < 0x0100) {
        return boot_rom_[addr];
    }
    const uint8_t data = direct_read(addr);
    return data;
}

void Bus::write(const uint16_t addr, const uint8_t data) {
    cycles(1);
    if (is_dma_restricted_area(addr) && dma_active_) {
        return;
    }
    if (addr == 0xFF50) {
        boot_rom_enabled_ = false;
        return;
    }
    if (addr == 0xFF46) {
        start_dma_transfer(data);
    }

    direct_write(addr, data);
}

void Bus::cycles(const uint8_t count) {
    assert(p_ppu_);
    assert(p_timer_);
    assert(io_);
    for (size_t i = 0; i < count; i++) {
        tick_++;
        if (dma_active_ && dma_cycles_remaining_ > 0) {
            const uint8_t byte = direct_read(dma_src_addr_ + 160 - dma_cycles_remaining_);
            direct_write(0xFE00 + 160 - dma_cycles_remaining_, byte);
            dma_cycles_remaining_--;
            if (dma_cycles_remaining_ <= 0) {
                dma_active_ = false;
                dma_src_addr_ = 0;
            }
        }
        for (size_t tcycle = 0; tcycle < 4; tcycle++) {  // 4 T-cycles per M-cycles
            if (io_->get_joypad()->is_button_released()) {
                uint8_t if_reg = io_->read(REG_IF_ADDR);
                if_reg |= (1 << 4);
                io_->write(REG_IF_ADDR, if_reg);
            }
            p_timer_->tick();
            p_ppu_->tick();
        }
    }
}

std::string Bus::memap_to_string() const {
    std::ostringstream oss;
    oss << "Memory Map:\n";
    for (const auto& region : regions_) {
        oss << "\t" << to_hex4(region.start) << "-" << to_hex4(region.end) << ": " << region.name << "\n";
    }

    return oss.str();
}

void Bus::start_dma_transfer(const uint8_t data) {
    dma_active_ = true;
    dma_cycles_remaining_ = 160;
    dma_src_addr_ = data * 0x100;
}

bool Bus::is_dma_restricted_area(const uint16_t addr) const { return (addr >= 0x8000 && addr <= 0xFDFF) && !(addr >= 0xFF80 && addr <= 0xFFFE); }

}  // namespace WindGB