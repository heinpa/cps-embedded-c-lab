#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "ssd1306.h"
#include "hardware/i2c.h"
#include "ball.h"


i2c_config_t display_dev = {
    .sda_pin = 20,
    .scl_pin = 21,
    .address = 0x3c,
    .clk_freq = 400000,
    .i2c_inst = &i2c0_inst
};

render_area_t frame_area = {
    .start_col = 0,
    .end_col = SSD1306_WIDTH - 1,
    .start_page = 0,
    .end_page = SSD1306_NUM_PAGES - 1
};

void display_init(void) {
    i2c_init(display_dev.i2c_inst, display_dev.clk_freq);
    gpio_set_function(display_dev.sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(display_dev.scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(display_dev.sda_pin);
    gpio_pull_up(display_dev.scl_pin);
    
    sleep_ms(500);

    ssd1306_init(&display_dev);
}

void display_render_grid(
        uint8_t* buffer,
        render_area_t* area,
        const bool * const grid,
        const uint8_t grid_width,
        const uint8_t grid_height,
        const uint8_t x,
        const uint8_t y) {
    if (x + grid_width >= SSD1306_WIDTH || y + grid_height >= SSD1306_HEIGHT) {
        return;
    }

    for (uint8_t gx = 0; gx < grid_width; gx++) {
        for (uint8_t gy = 0; gy < grid_height; gy++) {
            ssd1306_set_pixel(buffer, x + gx, y + gy, grid[gx * grid_width + gy]);
        }
    }

    ssd1306_render(&display_dev, buffer, area);
}

void display_render_ball(uint8_t x, uint8_t y) {
    const uint16_t buflen = ssd1306_calculate_render_arena_buflen(&frame_area);
    uint8_t buffer[buflen];
    memset(buffer, 0, buflen);

    display_render_grid(
        buffer, &frame_area, BALL_GRID, BALL_WIDTH, BALL_HEIGHT, x, y
    );
}

int main(void) {
    stdio_init_all();
    sleep_ms(1000);
    display_init();

    uint8_t pos_x = 59;
    uint8_t pos_y = 11;
    display_render_ball(pos_x, pos_y);
    
    while(1) { }

    return 0;
}
