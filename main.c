#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "scroll.h"
#include <linux/input.h>

#define MAX_SPEED 10
#define MIN_SPEED 1
#define INITIAL_DELAY_US 1000000 // Initial delay for scrolling (1 second)

char initials[] = {'T', 'O'}; // Define initials here
int num_initials = sizeof(initials) / sizeof(initials[0]);
int current_index = 0;
int xOffset = 0;
int yOffset = 0;
int xVelocity = 0;
int yVelocity = 0;
bool button_pressed = false;
bool scrolling_started = false; // Flag to track if scrolling has started

void handler(unsigned int code) {
    if (code == KEY_ENTER) {
        button_pressed = true;
    } else if (code == KEY_UP) {
        yVelocity = (yVelocity > -MAX_SPEED) ? yVelocity - 1 : -MAX_SPEED; // Increase upward velocity
    } else if (code == KEY_DOWN) {
        yVelocity = (yVelocity < MAX_SPEED) ? yVelocity + 1 : MAX_SPEED; // Increase downward velocity
    } else if (code == KEY_RIGHT) {
        xVelocity = (xVelocity < MAX_SPEED) ? xVelocity + 1 : MAX_SPEED; // Increase rightward velocity
    } else if (code == KEY_LEFT) {
        xVelocity = (xVelocity > -MAX_SPEED) ? xVelocity - 1 : -MAX_SPEED; // Increase leftward velocity
    }
}

int main(void) {
    open_display();
    open_input();

    // Initial display of the first initial
    char current_initial = initials[current_index];
    clear_display();
    display_letter(current_initial, xOffset, yOffset);

    while (1) {
        if (button_pressed) {
            // Change initial when button is pressed
            button_pressed = false;
            current_index++;
            if (current_index >= num_initials) {
                clear_display();
                close_display();
                close_input();
                exit(0);
            }
            // Update current initial
            current_initial = initials[current_index];
            clear_display();
            display_letter(current_initial, xOffset, yOffset);
        }

        // Update velocities based on joystick input
        check_input(handler, 0);

        // Apply scrolling velocities
        xOffset += xVelocity;
        yOffset += yVelocity;

        // Wrap around to the start/end of the text
        if (xOffset >= 8) {
            xOffset = 0;
        } else if (xOffset < 0) {
            xOffset = 7;
        }
        if (yOffset >= 8) {
            yOffset = 0;
        } else if (yOffset < 0) {
            yOffset = 7;
        }

        // Clear display and show current initial at new position
        clear_display();
        display_letter(current_initial, xOffset, yOffset);

        // Adjust scrolling speed to ensure it's approximately 1 pixel per second
        usleep(1000000 / MAX_SPEED);
    }

    return 0;
}
