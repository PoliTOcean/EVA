#include "control_allocation.h"

double map_to_kgf(double force, double tol){

    if(force<tol && force> -tol){
        return 0.0;
    }
    force = Z_COEFFICIENT*force;
    if(force>UPPER_LIMIT){
        force = UPPER_LIMIT;
    } else if(force<LOWER_LIMIT){
        force = LOWER_LIMIT;
    }
    double kgf = force/9.81;

    return kgf;

}