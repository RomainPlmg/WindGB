#pragma once

#include <array>
#include <atomic>
#include <cstdint>
#include <vector>

namespace WindGB {

class Bus;
class IO;

struct Sprite {
    uint8_t x;
    uint8_t y;
    uint8_t tile_index;

    bool bg_priority = false;  // false=OBJ on top of BG, true=BG on top of OBJ
    bool y_flip = false;
    bool x_flip = false;
    bool palette = false;  // false=OBP0, true=OBP1

    uint16_t oam_index = 0x0000;
    uint16_t oam_addr = 0x0000;

    Sprite(const uint8_t x, const uint8_t y, const uint8_t tile_index) : x(x), y(y), tile_index(tile_index) {}
};

class PPU {
   public:
    explicit PPU(Bus& bus, IO& io);

    void init();
    void tick();

    [[nodiscard]] const uint32_t* get_framebuffer() const { return display_buffer_.load()->data(); }
    [[nodiscard]] bool is_frame_ready() const { return frame_ready_; }
    void mark_frame_consumed() { frame_ready_ = false; }

    enum class Mode {
        HBLANK = 0,
        VBLANK,
        OAMSCAN,
        DRAWING,
    };

   private:
    Bus& bus_;

    uint8_t& lcdc_;
    uint8_t& stat_;
    uint8_t& scy_;
    uint8_t& scx_;
    uint8_t& ly_;
    uint8_t& lyc_;
    uint8_t& dma_;
    uint8_t& bgp_;
    uint8_t& obp0_;
    uint8_t& obp1_;
    uint8_t& wy_;
    uint8_t& wx_;
    uint8_t& if_;

    Mode mode_ = Mode::OAMSCAN;
    uint32_t gfx_counter_ = 0;
    uint8_t window_line_counter_ = 0;
    bool frame_ready_ = false;
    bool frame_blank_filled_ = false;
    uint32_t default_palette_[4] = {
        0xFFD0F8E0,
        0xFF70C088,
        0xFF566834,
        0xFF201808,
    };
    std::vector<Sprite> scanline_sprites_;

    // Buffers
    std::array<uint32_t, 160 * 144> buffer_a_{0};
    std::array<uint32_t, 160 * 144> buffer_b_{0};
    std::atomic<std::array<uint32_t, 160 * 144>*> display_buffer_;
    std::array<uint32_t, 160 * 144>* render_buffer_;
    std::array<uint8_t, 160 * 144> pixel_ids_;

    // Utility functions
    void inc_ly();
    void inc_window_line_counter();
    void set_pixel(uint8_t x, uint8_t y, uint32_t color);
    uint8_t get_tile_pixel(uint16_t tile_data_addr, uint8_t pixel_x, uint8_t pixel_y) const;
    void evaluate_sprites();
    void fill_line(uint32_t color);
    void render_bg_line();
    void render_obj_line();
    void render_window_line();
    void render_scanline();
    void present_frame();
};

}  // namespace WindGB