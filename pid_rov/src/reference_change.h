#ifndef _REFERENCE_CHANGE_H
#define _REFERENCE_CHANGE_H

/*
 * The instance of this class contains the variables needed to chnage the reference of the rov 
 * along an axis
 * - initial_position: is the initial position of the rov
 * - rov_max_speed: is the max spedd of the rov (m/s)
 * - joystick_sample_freq: is the frequency at which the joystick sends commands (Hz)
 * - max_ref: is the maximum position the rov can reach in a certain direction 
 * - min_ref: is the minimum reference the rov can reach
 * - tol: is an eventual tolerance for the rate variation of the reference, in case the speciifed one
 * is too high, a default one is used. It is also possible not to specify it and the default one is used
*/
class ReferenceChanger{
    public:
        ReferenceChanger(double initial_position, double rov_max_speed, double joystick_sample_freq, double max_ref, double min_ref, double tol);
        ReferenceChanger(double initial_position, double rov_max_speed, double joystick_sample_freq, double max_ref, double min_ref);
        void change_reference(double change);
        double get_current_reference(void);
    private:
        const double rov_max_speed;
        const double joystick_sample_freq;
        const double max_ref;
        const double min_ref;
        double current_reference;
        double tol;

};

#endif