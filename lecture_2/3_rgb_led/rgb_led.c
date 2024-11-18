#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

const uint16_t WRAP = 999;

const uint8_t PIN_RED = 0;
const uint8_t PIN_GREEN = 1;
const uint8_t PIN_BLUE = 2;

const double LEVELS_FOR_COLOURS[7][3] = {
    // r    g    b
    {1.0, 0.0, 0.0},    // red
    {0.0, 1.0, 0.0},    // green
    {0.0, 0.0, 1.0},    // blue
    {1.0, 0.3, 0.0},    // yellow
    {0.0, 1.0, 1.0},    // cyan
    {1.0, 0.0, 0.3},    // magenta
    {1.0, 0.3, 0.3}};   // white

uint channel_num_red;
uint channel_num_green;
uint channel_num_blue;
uint slice_num_red;
uint slice_num_green;
uint slice_num_blue;

void set_levels(const double* levels) {
    pwm_set_chan_level(slice_num_red, channel_num_red, levels[0] * WRAP+1);
    pwm_set_chan_level(slice_num_green, channel_num_green, levels[1] * WRAP+1);
    pwm_set_chan_level(slice_num_blue, channel_num_blue, levels[2] * WRAP+1);
}

int main(void) {
    gpio_set_function(PIN_RED, GPIO_FUNC_PWM);
    gpio_set_function(PIN_GREEN, GPIO_FUNC_PWM);
    gpio_set_function(PIN_BLUE, GPIO_FUNC_PWM);

    channel_num_red = pwm_gpio_to_channel(PIN_RED);
    channel_num_green = pwm_gpio_to_channel(PIN_GREEN);
    channel_num_blue = pwm_gpio_to_channel(PIN_BLUE);
    
    slice_num_red = pwm_gpio_to_slice_num(PIN_RED);
    slice_num_green = pwm_gpio_to_slice_num(PIN_GREEN);
    slice_num_blue = pwm_gpio_to_slice_num(PIN_BLUE);
    
    pwm_set_wrap(slice_num_red, WRAP);
    pwm_set_wrap(slice_num_green, WRAP);
    pwm_set_wrap(slice_num_blue, WRAP);

    // levels have to be set at least once before we can start pwm
    double levels_no_colour[3]= {0.0, 0.0, 0.0};
    set_levels(levels_no_colour);

    pwm_set_enabled(slice_num_red, true);
    pwm_set_enabled(slice_num_green, true);
    pwm_set_enabled(slice_num_blue, true);

    while (true) {
        for (int k = 0; k < 7; k++){
            set_levels(LEVELS_FOR_COLOURS[k]);
            sleep_ms(2000);
        }
    }
}
