#include "sense.h"
#include "scroll.h"
#include <linux/input.h>
#include <stdio.h>

pi_joystick_t *joystick = NULL;

void open_input(void) {
    if (joystick == NULL) {
        joystick = getJoystickDevice();
    }
}

void close_input(void) {
    if (joystick) {
        freeJoystick(joystick);
        joystick = NULL;
    }
}

void check_input(void (*callback)(unsigned int code), int delay) {
    if (joystick == NULL) {
        fprintf(stderr, "Tried to check input on a non-existent joystick!\n");
        return;
    }
    pollJoystick(joystick, callback, delay);
}
