#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

const uint8_t PIN = 8;
const uint8_t PWM_LEVEL = 20;
const uint8_t WRAP = 99;

int main(void) {
    uint channel = pwm_gpio_to_channel(PIN);
    uint slice = pwm_gpio_to_slice_num(PIN);

    gpio_set_function(PIN, GPIO_FUNC_PWM);
    
    pwm_set_wrap(slice, WRAP); // TODO: wrap +1 ?
    pwm_set_chan_level(slice, channel, PWM_LEVEL);

    pwm_set_enabled(slice, true);
}
