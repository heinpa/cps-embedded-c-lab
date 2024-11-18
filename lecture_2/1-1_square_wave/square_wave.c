#include <stdint.h>
#include "pico/stdlib.h"

const uint8_t PIN = 8;
const uint64_t DELAY = 50;

void led_init(void) {
    gpio_init(PIN);
    gpio_set_dir(PIN, GPIO_OUT);
}

int main(void) {
    led_init();
    while (true) {
        gpio_put(PIN, 1);
        sleep_us(DELAY);
        gpio_put(PIN, 0);
        sleep_us(DELAY);
    }
}
