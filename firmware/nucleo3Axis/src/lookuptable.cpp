#include "lookuptable.h"

#define SQUARE(X) X*X

#define THETA_1_1 0.0158*1000
#define THETA_1_2 0.1633*1000
#define THETA_1_3 1.4527*1000
#define THETA_2_1 -0.0105*1000
#define THETA_2_2 0.1304*1000
#define THETA_2_3 1.5477*1000
#define THETA_C_1 4.0000*1000
#define THETA_C_2 1.5000*1000

#define EPS  0.01

/*
    Maps the input force into the desired pwm
*/
int lookup_pwm(double kgf) {

    if (kgf < -EPS){
        return SQUARE(kgf)*THETA_1_1+kgf*THETA_1_2+THETA_1_3;
    } else if (kgf > EPS) {
        return SQUARE(kgf)*THETA_2_1+kgf*THETA_2_2+THETA_2_3;
    } else {
        return kgf*THETA_C_1+THETA_C_2;
    }

}