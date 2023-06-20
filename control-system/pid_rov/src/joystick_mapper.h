#ifndef _JOYSTICK_MAPPER_H
#define _JOYSTICK_MAPPER_H

#define MAX_INPUT_JOYSTICK 32678.0
#define MIN_INPUT_JOYSTICK -32678.0

typedef enum {
    INCREASE = 1,
    DECREASE = -1
} direction;

/*
 * Returns the percentage of variation to change the reference.
 * Returned value is between zero and 1
 * The durection states wheter the reference in increasing or deacreasing
*/
double map_joystick(int joystick_reading, direction dir);

#endif