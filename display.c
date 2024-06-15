// display.c

#include <stdio.h>
#include <unistd.h>
#include "scroll.h"

#define WHITE 0xFFFF
#define BLACK 0x0000

pi_framebuffer_t *fb = NULL;

void open_display(void) {
    if (fb == NULL) {
        fb = getFrameBuffer();
    }
}

void close_display(void) {
    if (fb) {
        clearFrameBuffer(fb, BLACK);
        sleep(1);
        freeFrameBuffer(fb);
        fb = NULL;
    }
}

void display_letter(char letter, int xOffset, int yOffset) {
    if (fb == NULL) {
        fprintf(stderr, "Tried to draw to a non-existent frame buffer!\n");
        return;
    }
    sense_fb_bitmap_t *bm = fb->bitmap;
    if (bm == NULL) {
        fprintf(stderr, "Failed to get bitmap\n");
        return;
    }

    // Clear the framebuffer
    clearFrameBuffer(fb, BLACK);

    // Draw the letter based on the input and offset
    switch (letter) {
        case 'T':
            // Draw letter T
            for (int i = 0; i < 8; i++) {
                bm->pixel[i + xOffset][0 + yOffset] = WHITE;
                bm->pixel[3 + xOffset][i + yOffset] = WHITE; // Middle line of T
            }
            break;
        case 'O':
            // Draw letter O
            for (int i = 1; i < 7; i++) {
                bm->pixel[i + xOffset][0 + yOffset] = WHITE;
                bm->pixel[i + xOffset][7 + yOffset] = WHITE;
            }
            for (int i = 1; i < 7; i++) {
                bm->pixel[0 + xOffset][i + yOffset] = WHITE;
                bm->pixel[7 + xOffset][i + yOffset] = WHITE;
            }
            break;
        case 'X':
            // Draw letter X
            for (int i = 0; i < 8; i++) {
                bm->pixel[i + xOffset][i + yOffset] = WHITE;
                bm->pixel[i + xOffset][7 - i + yOffset] = WHITE;
            }
            break;
        case 'H':
            // Draw letter H
            for (int i = 0; i < 8; i++) {
                bm->pixel[i + xOffset][4 + yOffset] = WHITE;
                bm->pixel[i + xOffset][3 + yOffset] = WHITE;
                bm->pixel[0 + xOffset][i + yOffset] = WHITE; // Middle line of H
                bm->pixel[7 + xOffset][i + yOffset] = WHITE;
            }
            break;
        case 'A':
            // Draw letter A
            for (int i = 0; i < 8; i++) {
                bm->pixel[i + xOffset][0 + yOffset] = WHITE;
                bm->pixel[i + xOffset][7 + yOffset] = WHITE;
            }
            for (int i = 1; i < 7; i++) {
                bm->pixel[0 + xOffset][i + yOffset] = WHITE;
                bm->pixel[3 + xOffset][i + yOffset] = WHITE; // Middle line of A
            }
            break;
        case 'C':
            // Draw letter C
            for (int i = 1; i < 7; i++) {
                bm->pixel[i + xOffset][0 + yOffset] = WHITE;
                bm->pixel[i + xOffset][7 + yOffset] = WHITE;
            }
            for (int i = 1; i < 7; i++) {
                bm->pixel[0 + xOffset][i + yOffset] = WHITE;
            }
            break;
        default:
            fprintf(stderr, "Unknown letter: %c\n", letter);
            break;
    }
}

void clear_display(void) {
    if (fb) {
        clearFrameBuffer(fb, BLACK);
    }
}
