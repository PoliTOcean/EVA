#include "pid.h"

#include <iostream>

PID::PID(double dt, double max, double min, double Kp, double Kd, double Ki):
    dt(dt),
    max(max),
    min(min),
    Kp(Kp),
    Kd(Kd),
    Ki(Ki)
{

    this->pre_error = 0.0;
    this->integral = 0.0; 

}

double PID::calculate(double setpoint, double pv){

    //Error
    double error = setpoint - pv;
    if(setpoint-pv<(this->min) && setpoint-pv> -(this->min)){
        return 0.0;
    }

    //Proporital Part
    double Pout = Kp*error;

    //Integral Part
    this->integral = error*dt;
    double Iout = Ki*integral;

    //Derivative Part
    double derivative = (error - pre_error)/dt;
    double Dout = Kd*derivative;

    //Computation of the Output
    double output = Pout + Iout + Dout;
    if(output>max && output>0){
        output = max;
    } else if(output< -max && output<0){
        output = -max;
    }
    //Save current error for further derivation parts
    this->pre_error = error;

    return output;

}