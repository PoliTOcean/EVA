#include "joystick_mapper.h"

double map_joystick(int joystick_reading, direction dir){

    double bias = joystick_reading + MAX_INPUT_JOYSTICK;
    double percentage = bias/(MAX_INPUT_JOYSTICK-MIN_INPUT_JOYSTICK);

    return percentage*((double) dir);

}