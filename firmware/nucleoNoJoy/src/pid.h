#ifndef _PID_H
#define _PID_H

class PID {
    public:
        /* 
         * Kp -  proportional gain
         * Ki -  Integral gain
         * Kd -  derivative gain
         * dt -  loop interval time
         * max - maximum value of manipulated variable
        */
        PID(double dt, double max, double min, double Kp, double Kd, double Ki);

        /*
         * Returns the manipulated variable given a setpoint and current process value
        */
        double calculate(double setpoint, double pv);

    private:
        const double dt;
        const double max;
        const double min;
        const double Kp;
        const double Kd;
        const double Ki;
        double pre_error;
        double integral;
};

#endif