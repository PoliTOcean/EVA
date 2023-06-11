#include "reference_change.h"

#define MAX_CHANGE 1.0
#define MIN_CHANGE -1.0

ReferenceChanger::ReferenceChanger(double initial_position, double rov_max_speed, double joystick_sample_freq, double max_ref, double min_ref, double tol):
    rov_max_speed(rov_max_speed),
    joystick_sample_freq(joystick_sample_freq),
    current_reference(initial_position),
    min_ref(min_ref),
    max_ref(max_ref)
{

    const double default_tol = 0.005*rov_max_speed;
    if (tol>default_tol){
        this->tol = default_tol;
    }
    else {
        this->tol = tol;
    }


}

ReferenceChanger::ReferenceChanger(double initial_position, double rov_max_speed, double joystick_sample_freq, double max_ref, double min_ref):
    rov_max_speed(rov_max_speed),
    joystick_sample_freq(joystick_sample_freq),
    current_reference(initial_position),
    min_ref(min_ref),
    max_ref(max_ref)
{

    const double default_tol = 0.005*rov_max_speed;
    this->tol = default_tol;

}

void ReferenceChanger::change_reference(double change){

    if(change>MAX_CHANGE){
        change = MAX_CHANGE;
    } else if(change<MIN_CHANGE) {
        change = MIN_CHANGE;
    }

    double variation = (this->rov_max_speed)/(this->joystick_sample_freq)*change;
    if(variation>0){
        variation-=this->tol;
    } else {
        variation+=this->tol;
    }

    double new_reference = variation+this->current_reference;
    if(new_reference>(this->max_ref)){
        this->current_reference = this->max_ref;
    } else if(new_reference<(this->min_ref)){
        this->current_reference = this->min_ref;
    } else {
        this->current_reference = new_reference;
    }

}

double ReferenceChanger::get_current_reference(void){

    return this->current_reference;

}