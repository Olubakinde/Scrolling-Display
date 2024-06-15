#ifndef SCROLL_H
#define SCROLL_H

#include "sense.h"
#include <stdint.h>

void open_display(void);
void close_display(void);
void display_letter(char letter, int xOffset, int yOffset);
void clear_display(void);
void setPixel(sense_fb_bitmap_t *bm, int x, int y, uint16_t color);
void drawChar8x8(sense_fb_bitmap_t *bm, int x, int y, uint16_t fgcolor, uint16_t bgcolor, char c);
void open_input(void);
void close_input(void);
void check_input(void (*callback)(unsigned int code), int delay);

#endif
