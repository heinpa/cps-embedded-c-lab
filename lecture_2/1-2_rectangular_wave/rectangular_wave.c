#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"

const uint8_t PIN = 8;
const uint32_t FREQUENCY = 4200;
const float DUTY_CYCLE = 0.1;

void led_init(void) {
    gpio_init(PIN);
    gpio_set_dir(PIN, GPIO_OUT);
}

int main(void) {
//    stdio_init_all();
///    sleep_ms(1000);
    led_init();
    uint64_t period_us =  1000000 / FREQUENCY ;
    uint64_t delay_on_us = period_us * DUTY_CYCLE;
    uint64_t delay_off_us = period_us * (1 - DUTY_CYCLE);
//    printf("%llu\n", base_delay);
//    printf("%llu\n", del_on);
//    printf("%llu\n", del_off);
    while (true) {
        gpio_put(PIN, 1);
        sleep_us(delay_on_us);
        gpio_put(PIN, 0);
        sleep_us(delay_off_us);
    }
}
