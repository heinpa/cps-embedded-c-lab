#include <stdint.h>
#include "pico/stdlib.h"

#define NUM_LEDS 5
const uint8_t LED_PINS[NUM_LEDS] = {0, 1, 2, 3, 4};
const uint8_t BUTTON_PIN = 5;
const uint8_t BUTTON_DELAY_MS = 10;

typedef enum {UP, DOWN, PRESS, RELEASE} button_state_t;
button_state_t previous_button_state = UP;


void leds_initialize(void) {
    for (uint8_t led_idx = 0; led_idx < NUM_LEDS; led_idx++) {
        gpio_init(LED_PINS[led_idx]);
        gpio_set_dir(LED_PINS[led_idx], GPIO_OUT);
        gpio_put(LED_PINS[led_idx], 0);
    }
}

void leds_set_index(uint8_t index) {
    for (uint8_t led_idx = 0; led_idx < NUM_LEDS; led_idx++) {
        gpio_put(LED_PINS[led_idx], 0);
    }
    gpio_put(LED_PINS[index], 1);
}

void button_initialize(void) {
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_set_pulls(BUTTON_PIN, 1, 0);
}

button_state_t button_read_up_down(void) {
    return gpio_get(BUTTON_PIN) ? UP : DOWN;
}

button_state_t button_get_state(void) {
    button_state_t current_state = button_read_up_down();
    button_state_t new_state;
    
    if (current_state == DOWN) {
        if (previous_button_state == DOWN || previous_button_state == PRESS) {
            new_state = DOWN;
        } else {
            sleep_ms(BUTTON_DELAY_MS);
            if (button_read_up_down() == DOWN) {
                new_state = PRESS;
            } else {
                current_state = new_state;
            }
        }
    } else {
        if (previous_button_state == PRESS || previous_button_state == RELEASE) {
            new_state = UP;
        } else {
            sleep_ms(BUTTON_DELAY_MS);
            if (button_read_up_down() == UP) {
                new_state = RELEASE;
            } else {
                current_state = new_state;
            }
        }
    }
    previous_button_state = new_state;
    return new_state;

}

int main(void) {
    leds_initialize();
    button_initialize();

    uint8_t pressed_counter = 0;
    leds_set_index(pressed_counter);

    while (1) {
        if (button_get_state() == PRESS) {
            pressed_counter = (pressed_counter + 1) % NUM_LEDS;
            leds_set_index(pressed_counter);
        }
    }

    return 0;
}
