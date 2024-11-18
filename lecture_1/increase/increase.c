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
    led_init(); // initialise LED pins
    int sequence[] = {0, 1, 2, 3, 4};
    int sequence_length = sizeof(sequence)/sizeof(int);

    while(1) {
        // incrementally turn on the LEDs 
        for (int i = 0; i < sequence_length; i++) {
            gpio_put(PINS[sequence[i]], 1);
            sleep_ms(LED_DELAY_MS);
        }
        // turn off all LEDs at the end of the sequence
        for (int i = 0; i < sequence_length; i++) {
            gpio_put(PINS[sequence[i]], 0);
        }
        sleep_ms(LED_DELAY_MS);
    }
}
