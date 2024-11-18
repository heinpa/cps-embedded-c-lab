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

void blink(int a, int b) {
    gpio_put(PINS[a], 1);
    gpio_put(PINS[b], 1);

    sleep_ms(LED_DELAY_MS);

    gpio_put(PINS[a], 0);
    gpio_put(PINS[b], 0);
}

int main() {
    led_init(); // initialise LED pins

    while(1) {
        blink(0,4);
        blink(1,3);
        
        gpio_put(PINS[2], 1);
        sleep_ms(LED_DELAY_MS);
        gpio_put(PINS[2], 0);
        
        blink(1,3);
    }
}
