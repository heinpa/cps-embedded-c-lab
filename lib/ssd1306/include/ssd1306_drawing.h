/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SSD1306_DRAWING_H
#define SSD1306_DRAWING_H

#include <stdint.h>
#include <stdbool.h>

void ssd1306_set_pixel(uint8_t* buf, int x, int y, bool on);
void ssd1306_draw_line(uint8_t* buf, int x0, int y0, int x1, int y1, bool on);
void ssd1306_write_char(uint8_t* buf, int16_t x, int16_t y, uint8_t ch);
void ssd1306_write_string(uint8_t* buf, int16_t x, int16_t y, char* str);

#endif