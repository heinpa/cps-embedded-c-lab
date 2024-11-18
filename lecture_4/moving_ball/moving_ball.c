#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "ssd1306.h"
#include "hardware/i2c.h"
#include "ball.h"


enum DIRECTION {
    UP, DOWN, LEFT, RIGHT, INVALID
};

uint8_t pos_x = 0;
uint8_t pos_y = 0;
int traj[] = {+1, +1};

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

void display_render_ball() {
    const uint16_t buflen = ssd1306_calculate_render_arena_buflen(&frame_area);
    uint8_t buffer[buflen];
    memset(buffer, 0, buflen);

    display_render_grid(
        buffer, &frame_area, BALL_GRID, BALL_WIDTH, BALL_HEIGHT, pos_x, pos_y
    );
}



void display_render_char(char input) {
    render_area_t area = {
        .start_col = 0,
        .end_col = SSD1306_WIDTH -1,
        .start_page = 2,
        .end_page = 2
    };
    const uint16_t buflen = ssd1306_calculate_render_arena_buflen(&area);

    uint8_t buffer[buflen];
    memset(buffer, 0, buflen);


    ssd1306_write_char(buffer, 52, 0, input);
    ssd1306_render(&display_dev, buffer, &area);
}



enum DIRECTION get_direction(char input) {
    if (input == 'w') {
        return UP;
    } else if (input == 'a') {
        return LEFT;
    } else if (input == 's') {
        return DOWN;
    } else if (input == 'd') {
        return RIGHT;
    }
    else {
        return INVALID;
    }
}

bool upper_edge_not_reached() {
    return pos_y > 0;
}

bool lower_edge_not_reached() {
    return pos_y < (SSD1306_NUM_PAGES * 8) - 1 - BALL_HEIGHT;
}

bool left_edge_not_reached() {
    return pos_x > 0;
}

bool right_edge_not_reached() {
    return pos_x < SSD1306_WIDTH - 1 - BALL_WIDTH;
}

void update_position_x_y(enum DIRECTION direction) {
    if (direction == UP) {
        if (upper_edge_not_reached()) {
            pos_y --;
        }
    }
    if (direction == DOWN) {
        if (lower_edge_not_reached()) {
            pos_y ++;
        }
    }
    if (direction == RIGHT) {
        if (right_edge_not_reached()) {
            pos_x ++;
        }
    }
    if (direction == LEFT) {
        if (left_edge_not_reached()) {
            pos_x --;
        }
    }
}

void update_traj() {
    if (!upper_edge_not_reached() && traj[1] < 0) {
        traj[1] = +1;
    }
    if (!lower_edge_not_reached() && traj[1] > 0) {
        traj[1] = -1;
    }
    if (!left_edge_not_reached() && traj[0] < 0) {
        traj[0] = +1;
    }
    if (!right_edge_not_reached() && traj[0] > 0) {
        traj[0] = -1;
    }
}

void update_position_x_y_with_traj() {
    pos_x += traj[0];
    pos_y += traj[1];
}

int main(void) {
    stdio_init_all();
    sleep_ms(1000);
    display_init();

    pos_x = 59;
    pos_y = 11;
    display_render_ball();
    uint8_t traj[] = {+1,+1};

    while(1) { 
//        update_traj();
//        update_position_x_y_with_traj();
//        display_render_ball();
//        sleep_ms(10);
        char input = getchar();
        enum DIRECTION direction = get_direction(input);
        if (direction != INVALID) {
            update_position_x_y(direction);
            display_render_ball();
        }
    }
    return 0;
}
