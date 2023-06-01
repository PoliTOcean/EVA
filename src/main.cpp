#include <iostream>

#include "control_allocation.h"
#include "joystick_mapper.h"
#include "lookuptable.h"
#include "pid.h"
#include "reference_change.h"

#define kp 89.0
#define ki 0.25
#define kd 0.2

#define MAX_FORCE 80.0
#define MIN_FORCE 1.0
#define MIN_DISTANCE 0.001

#define MAX_SPEED 1.0
#define dt 0.03

#define map(X) X==1500?0.0:((X/(1900.0+1100.0))*dt*MAX_SPEED*(X>=1500?1.0:-1.0))

int main() {

    PID pid = PID(0.03,MAX_FORCE,MIN_DISTANCE,kp,kd,ki);
    double reference = 0.0;
    double new_ref = 3.0;
    double t = 0.0;

    std::cout<<"Position, PWM, Force, Time"<<std::endl;

    while(t<10.0){
        double force = pid.calculate(new_ref,reference);
        //std::cout<<"force: "<<force<<std::endl;
        double kgf = map_to_kgf(force,MIN_FORCE);
        //std::cout<<"kgf: "<<kgf<<std::endl;
        int pwm = lookup_pwm(kgf);
        //std::cout<<"pwm: "<<pwm<<std::endl;
        double var = map(pwm);
        reference+=var;
        //std::cout<<"var: "<<var<<std::endl<<std::endl;
        std::cout<<reference<<", ";
        std::cout<<pwm<<", ";
        std::cout<<kgf<<", ";
        std::cout<<t<<std::endl;
        t+=0.03;
    }

    return 0;
}