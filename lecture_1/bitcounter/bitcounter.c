#include "pico/stdlib.h"

const uint32_t LED_DELAY_MS = 250;
const uint8_t PINS[] = {0, 1, 2, 3, 4};
const uint8_t PIN_COUNT = sizeof(PINS)/sizeof(uint8_t);

void led_init(void) {
    for (int k = 0; k < PIN_COUNT; k++) {
        gpio_init(PINS[k]);
        gpio_set_dir(PINS[k], GPIO_OUT);
    }
}

int main() {
    led_init();

    while (1) {
        for (int k = 0; k < 32; k++) {
            for (int i = 0; i < PIN_COUNT; i++) {
                gpio_put(PINS[i], (k >> i) & 1);
            }
            sleep_ms(LED_DELAY_MS);
        }
    }
}
