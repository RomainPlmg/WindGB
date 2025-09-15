#include "ppu.hpp"

#include <cstdint>

#include "bus.hpp"
#include "common.hpp"
#include "io.hpp"
#include "logger.hpp"

namespace WindGB {

PPU::PPU(Bus& bus, IO& io)
    : bus_(bus),
      lcdc_(io.get_data()[REG_LCDC_ADDR - IO_ADDR_START]),
      stat_(io.get_data()[REG_STAT_ADDR - IO_ADDR_START]),
      scy_(io.get_data()[REG_SCY_ADDR - IO_ADDR_START]),
      scx_(io.get_data()[REG_SCX_ADDR - IO_ADDR_START]),
      ly_(io.get_data()[REG_LY_ADDR - IO_ADDR_START]),
      lyc_(io.get_data()[REG_LYC_ADDR - IO_ADDR_START]),
      dma_(io.get_data()[REG_DMA_ADDR - IO_ADDR_START]),
      bgp_(io.get_data()[REG_BGP_ADDR - IO_ADDR_START]),
      obp0_(io.get_data()[REG_OBP0_ADDR - IO_ADDR_START]),
      obp1_(io.get_data()[REG_OBP1_ADDR - IO_ADDR_START]),
      wy_(io.get_data()[REG_WY_ADDR - IO_ADDR_START]),
      wx_(io.get_data()[REG_WX_ADDR - IO_ADDR_START]),
      if_(io.get_data()[REG_IF_ADDR - IO_ADDR_START]),
      display_buffer_(&buffer_a_),
      render_buffer_(&buffer_b_) {}

void PPU::init() {
    mode_ = Mode::OAMSCAN;
    gfx_counter_ = 0;
    window_line_counter_ = 0;
    frame_ready_ = false;

    buffer_a_ = {0};
    buffer_b_ = {0};

    LOG_INFO("PPU initialized");
}

void PPU::tick() {
    if (!GET_BIT(lcdc_, 7)) {  // PPU/LCD enabled ?
        gfx_counter_ = 0;
        ly_ = 0;
        window_line_counter_ = 0;
        mode_ = Mode::HBLANK;

        if (!frame_blank_filled_) {
            std::ranges::fill(*render_buffer_, default_palette_[0]);
            present_frame();
            frame_ready_ = true;
            frame_blank_filled_ = true;
        }
        return;
    }

    gfx_counter_++;
    frame_blank_filled_ = false;

    // PPU state machine
    if (mode_ == Mode::HBLANK) {
        if (gfx_counter_ >= 204) {
            gfx_counter_ = 0;
            inc_ly();
            if (ly_ == 144) {  // All 144 scanlines have been drawn, switch to 10 VBLANK scanlines
                window_line_counter_ = 0;
                mode_ = Mode::VBLANK;
                present_frame();
                frame_ready_ = true;
                if_ |= (1 << 0);
            } else {  // Start to draw the next scanline
                mode_ = Mode::OAMSCAN;
                inc_window_line_counter();
            }
        }
    } else if (mode_ == Mode::VBLANK) {
        if (gfx_counter_ >= 456) {
            gfx_counter_ = 0;
            inc_ly();
            if (ly_ >= 154 - 1) {  // Last scanline
                ly_ = 0;
                mode_ = Mode::OAMSCAN;
            }
        }
    } else if (mode_ == Mode::OAMSCAN) {
        if (gfx_counter_ >= 80) {
            gfx_counter_ = 0;
            mode_ = Mode::DRAWING;
            evaluate_sprites();
        }
    } else {  // DRAWING
        if (gfx_counter_ >= 172) {
            gfx_counter_ = 0;
            mode_ = Mode::HBLANK;
            render_scanline();
        }
    }
}

void PPU::inc_ly() {
    ly_ = (ly_ + 1) % 154;
    if (ly_ == lyc_) {
        stat_ |= (1 << 2);
        if (GET_BIT(stat_, 6)) {
            if_ |= (1 << 1);
        }
    } else {
        stat_ &= ~(1 << 2);
    }
}
void PPU::inc_window_line_counter() {
    if (GET_BIT(lcdc_, 5) && ly_ > wy_ && wx_ <= 166) {
        window_line_counter_++;
    }
}

void PPU::set_pixel(const uint8_t x, const uint8_t y, const uint32_t color) { (*render_buffer_)[y * SCREEN_WIDTH + x] = color; }

uint8_t PPU::get_tile_pixel(const uint16_t tile_data_addr, const uint8_t pixel_x, const uint8_t pixel_y) const {
    const uint16_t line_addr = tile_data_addr + (pixel_y * 2);

    const uint8_t low_byte = bus_.direct_read(line_addr);
    const uint8_t high_byte = bus_.direct_read(line_addr + 1);

    const uint8_t bit_pos = 7 - pixel_x;

    const uint8_t low_bit = (low_byte >> bit_pos) & 1;
    const uint8_t high_bit = (high_byte >> bit_pos) & 1;

    return (high_bit << 1) | low_bit;
}

void PPU::evaluate_sprites() {
    scanline_sprites_.clear();  // Remove all sprites for the new scanline

    const uint16_t obj_size = GET_BIT(lcdc_, 2) ? 16 : 8;
    uint32_t sprite_count = 0;

    for (uint16_t i = 0; i < 40; i++) {                    // OAM store up to 40 sprites
        const uint16_t oam_addr = OAM_ADDR_START + i * 4;  // OAM sprite takes 4 bytes in memory

        // Recover sprite data
        const uint8_t y = bus_.direct_read(oam_addr);
        const uint8_t x = bus_.direct_read(oam_addr + 1);
        const uint8_t tile = bus_.direct_read(oam_addr + 2);
        const uint8_t attr = bus_.direct_read(oam_addr + 3);

        // Check if the scanline intercept the sprite position
        if (ly_ >= y - 16 && ly_ < y - 16 + obj_size) {
            Sprite sprite(x, y, tile);
            sprite.bg_priority = GET_BIT(attr, 7);
            sprite.y_flip = GET_BIT(attr, 6);
            sprite.x_flip = GET_BIT(attr, 5);
            sprite.palette = GET_BIT(attr, 4);
            sprite.oam_addr = oam_addr;

            scanline_sprites_.push_back(sprite);
            sprite_count++;

            if (sprite_count == 10) break;  // Max 10 sprites per scanline
        }
    }

    // Sort sprites by X growing
    std::sort(scanline_sprites_.begin(), scanline_sprites_.end(), [](const Sprite& a, const Sprite& b) { return a.x >= b.x; });
}

void PPU::fill_line(const uint32_t color) {
    if (ly_ < SCREEN_HEIGHT) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            set_pixel(x, ly_, color);
        }
    }
}

void PPU::render_bg_line() {
    const uint8_t bg_y = (ly_ + scy_) & 0xFF;
    const uint8_t tile_row = bg_y / 8;
    const uint8_t pixel_row = bg_y % 8;

    const uint16_t tile_map_base = (GET_BIT(lcdc_, 3)) ? TILE_MAP_1 : TILE_MAP_0;

    const bool signed_addressing = !GET_BIT(lcdc_, 4);

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        const uint8_t bg_x = (x + scx_) & 0xFF;
        const uint8_t tile_col = bg_x / 8;
        const uint8_t pixel_col = bg_x % 8;
        const uint16_t tile_map_addr = tile_map_base + (tile_row * 32) + tile_col;
        const uint8_t tile_id = bus_.direct_read(tile_map_addr);

        uint16_t tile_data_addr;
        if (signed_addressing) {
            const auto signed_id = static_cast<int8_t>(tile_id);
            tile_data_addr = 0x9000 + (signed_id * 16);
        } else {
            tile_data_addr = TILE_DATA_0 + (tile_id * 16);
        }

        const uint8_t color_id = get_tile_pixel(tile_data_addr, pixel_col, pixel_row);
        pixel_ids_[ly_ * SCREEN_WIDTH + x] = color_id;

        const uint8_t palette_color = (bgp_ >> (color_id * 2)) & 0x03;
        const uint32_t final_color = default_palette_[palette_color];

        set_pixel(x, ly_, final_color);
    }
}

void PPU::render_window_line() {
    if (wy_ > ly_) return;
    if (wx_ >= 167) return;

    const uint8_t tile_row = window_line_counter_ / 8;
    const uint8_t pixel_row = window_line_counter_ % 8;

    const uint16_t tile_map_base = GET_BIT(lcdc_, 6) ? TILE_MAP_1 : TILE_MAP_0;

    const bool signed_addressing = !GET_BIT(lcdc_, 4);

    const int window_start_x = wx_ - 7;

    for (int screen_x = std::max(0, window_start_x); screen_x < SCREEN_WIDTH; screen_x++) {
        const uint8_t window_x = screen_x - window_start_x;
        const uint8_t tile_col = window_x / 8;
        const uint8_t pixel_col = window_x % 8;

        const uint16_t tile_map_addr = tile_map_base + (tile_row * 32) + tile_col;
        const uint8_t tile_id = bus_.direct_read(tile_map_addr);

        uint16_t tile_data_addr;
        if (signed_addressing) {
            const auto signed_id = static_cast<int8_t>(tile_id);
            tile_data_addr = 0x9000 + (signed_id * 16);
        } else {
            tile_data_addr = TILE_DATA_0 + (tile_id * 16);
        }

        const uint8_t color_id = get_tile_pixel(tile_data_addr, pixel_col, pixel_row);
        pixel_ids_[ly_ * SCREEN_WIDTH + screen_x] = color_id;

        const uint8_t palette_color = (bgp_ >> (color_id * 2)) & 0x03;
        const uint32_t final_color = default_palette_[palette_color];

        set_pixel(screen_x, ly_, final_color);
    }
}

void PPU::render_obj_line() {
    const uint16_t obj_size = GET_BIT(lcdc_, 2) ? 16 : 8;

    for (const auto& sprite : scanline_sprites_) {
        uint8_t sprite_y = ly_ - (sprite.y - 16);  // The relative position of the scanline in the sprite
        if (sprite.y_flip) sprite_y = obj_size - 1 - sprite_y;

        if (sprite_y >= obj_size) continue;

        uint16_t tile_addr = (0x8000 + sprite.tile_index * 16);
        if (obj_size == 16) {  // 8*16 mode
            uint8_t tile_index = sprite.tile_index & 0xFE;
            tile_addr = 0x8000 + tile_index * 16;
        }
        for (int x = 0; x < 8; x++) {
            uint8_t sprite_x = x;  // sprite_x is the relative pixel position in the sprite
            if (sprite.x_flip) sprite_x = 7 - sprite_x;
            const uint8_t pixel = get_tile_pixel(tile_addr, sprite_x, sprite_y);

            if (pixel == 0) continue;

            const uint8_t lcd_x = (sprite.x - 8) + x;
            if (lcd_x >= 160 || lcd_x < 0) continue;

            // Check the pixel color of the background if bg_priority
            uint8_t bg_pixel_id = pixel_ids_.at(ly_ * SCREEN_WIDTH + lcd_x);
            if (sprite.bg_priority && bg_pixel_id != 0) continue;

            // Populate the framebuffer
            const uint8_t palette = sprite.palette ? obp1_ : obp0_;
            const uint8_t color_id = (palette >> (pixel * 2)) & 0x03;

            const auto& color = default_palette_[color_id];

            set_pixel(lcd_x, ly_, color);
        }
    }
}

void PPU::render_scanline() {
    if (GET_BIT(lcdc_, 0)) {  // BG & Window enable
        render_bg_line();
        if (GET_BIT(lcdc_, 5)) {  // Window enable
            render_window_line();
        }
    } else {
        fill_line(default_palette_[0]);
    }

    if (GET_BIT(lcdc_, 1)) {  // OBJ enable
        render_obj_line();
    }
}

void PPU::present_frame() {
    auto* old_display = display_buffer_.exchange(render_buffer_);
    render_buffer_ = old_display;
}

}  // namespace WindGB