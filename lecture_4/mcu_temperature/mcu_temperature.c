#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "ssd1306.h"

i2c_config_t display_dev = {
    .sda_pin = 20,
    .scl_pin = 21,
    .address = 0x3c,
    .clk_freq = 400000,
    .i2c_inst = &i2c0_inst
};

void temp_init(void) {
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
}

float temp_read_temperature(void) {
    const float conversion_factor = 3.3f / (1 << 12);
    const float adc_voltage = (float) adc_read() * conversion_factor;
    const float temperature = 27 - (adc_voltage - 0.706) / 0.001721;
    return temperature;
}

void display_init(void) {
    i2c_init(display_dev.i2c_inst, display_dev.clk_freq);
    gpio_set_function(display_dev.sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(display_dev.scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(display_dev.sda_pin);
    gpio_pull_up(display_dev.scl_pin);
    
    sleep_ms(500);

    ssd1306_init(&display_dev);
}

void display_render_header(void) {
    render_area_t area = {
        .start_col = 0,
        .end_col = SSD1306_WIDTH - 1,
        .start_page = 0,
        .end_page = SSD1306_NUM_PAGES - 1
    };
    const uint16_t buflen = ssd1306_calculate_render_arena_buflen(&area);

    uint8_t buffer[buflen];
    memset(buffer, 0, buflen);
    
    char* text = "temperature";
    ssd1306_write_string(buffer, 20, 8, text);
    ssd1306_render(&display_dev, buffer, &area);
} 

void display_render_temperature(float temperature) {
    render_area_t area = {
        .start_col = 0,
        .end_col = SSD1306_WIDTH -1,
        .start_page = 2,
        .end_page = 2
    };
    const uint16_t buflen = ssd1306_calculate_render_arena_buflen(&area);

    uint8_t buffer[buflen];
    memset(buffer, 0, buflen);

    uint32_t temp_int = abs((int)roundf(temperature));
    char text_buf[4];
    sprintf(text_buf, "%uC", temp_int);

    ssd1306_write_string(buffer, 52, 0, text_buf);
    ssd1306_render(&display_dev, buffer, &area);
}

int main(void) {
    stdio_init_all();
    sleep_ms(1000);
    temp_init();
    display_init();

    display_render_header();
    
    while (1) { 
        float temperature = temp_read_temperature();
        display_render_temperature(temperature);
        sleep_ms(100);
    }

    return 0;
}
