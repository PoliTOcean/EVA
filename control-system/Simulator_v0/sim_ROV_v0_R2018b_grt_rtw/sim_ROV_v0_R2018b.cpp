

    

        /*
        * sim_ROV_v0_R2018b.cpp
        *
                * Academic License - for use in teaching, academic research, and meeting
* course requirements at degree granting institutions only.  Not for
* government, commercial, or other organizational use.
        *
    * Code generation for model "sim_ROV_v0_R2018b".
    *
    * Model version              : 10.0
    * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
        * C++ source code generated on : Wed May 10 11:42:16 2023
 * 
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objective: Execution efficiency
 * Validation result: Not run
        */




    
#include "sim_ROV_v0_R2018b.h"

#include "rtwtypes.h"

#include "sim_ROV_v0_R2018b_private.h"

#include "sim_ROV_v0_R2018b_types.h"

#include <cmath>

#include <cstring>

extern "C" {

#include "rt_nonfinite.h"
}

        #include "sim_ROV_v0_R2018b_dt.h"


    

    

    

    
    

/* Named constants for MATLAB Function: '<S16>/Normalization' */
const int32_T sim_ROV_v0_R2018b_CALL_EVENT{-1};



    

    

    

    

    

    

    
        /* Block signals (default storage) */
                                            B_sim_ROV_v0_R2018b_T sim_ROV_v0_R2018b_B;

            
        /* Continuous states */
                            X_sim_ROV_v0_R2018b_T sim_ROV_v0_R2018b_X;

    
            /* Block states (default storage) */
                                            DW_sim_ROV_v0_R2018b_T sim_ROV_v0_R2018b_DW;

            
    




            
        
        
        
        
        
        

        

        
        


                /* Real-time model */
                        
                                RT_MODEL_sim_ROV_v0_R2018b_T sim_ROV_v0_R2018b_M_{};

                            RT_MODEL_sim_ROV_v0_R2018b_T *const sim_ROV_v0_R2018b_M{ &sim_ROV_v0_R2018b_M_ };



    

    

    static void rate_scheduler(void);

    

        
                         
real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[], uint32_T maxIndex)
{
    real_T frac;
    real_T yL_0d0;
    uint32_T iLeft;
    /* Column-major Lookup 1-D
   Search method: 'binary'
   Use previous index: 'off'
   Interpolation method: 'Linear point-slope'
   Extrapolation method: 'Linear'
   Use last breakpoint for index at or above upper limit: 'off'
   Remove protection against out-of-range input in generated code: 'off'
 */
    /* Prelookup - Index and Fraction
   Index Search method: 'binary'
   Extrapolation method: 'Linear'
   Use previous index: 'off'
   Use last breakpoint for index at or above upper limit: 'off'
   Remove protection against out-of-range input in generated code: 'off'
 */
    if (u0 <= bp0[0U]) {
        iLeft = 0U;
        frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
    } else if (u0 < bp0[maxIndex]) {
        uint32_T bpIdx;
        uint32_T iRght;
        /* Binary Search */
        bpIdx = maxIndex >> 1U;
        iLeft = 0U;
        iRght = maxIndex;
        while (iRght - iLeft > 1U) {
            if (u0 < bp0[bpIdx]) {
                iRght = bpIdx;
            } else {
                iLeft = bpIdx;
            }
            bpIdx = (iRght + iLeft) >> 1U;
        }
        frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
    } else {
        iLeft = maxIndex - 1U;
        frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
    }
    /* Column-major Interpolation 1-D
   Interpolation method: 'Linear point-slope'
   Use last breakpoint for index at or above upper limit: 'off'
   Overflow mode: 'portable wrapping'
 */
    yL_0d0 = table[iLeft];
    return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}
        
    
        
        





            /* 
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */

                        static void rate_scheduler(void)
            {
                    
    /* Compute which subrates run during the next base time step.  Subrates
    * are an integer multiple of the base rate counter.  Therefore, the subtask
    * counter is reset when it reaches its limit (zero means run).
    */
    

            (sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[2])++;
            if ((sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[2]) > 9) { /* Sample time: [0.1s, 0.0s] */
            sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[2] = 0;
        }


            }
            










    /* 
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */

        static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
    {
        

            time_T    t    { rtsiGetT(si) };
            time_T    tnew { rtsiGetSolverStopTime(si) };
            time_T    h    { rtsiGetStepSize(si) };
            real_T    *x   { rtsiGetContStates(si) };
            ODE4_IntgData  *id  { static_cast<ODE4_IntgData *>(rtsiGetSolverData(si)) };
            real_T    *y   { id->y };
            real_T    *f0  { id->f[0] };
            real_T    *f1  { id->f[1] };
            real_T    *f2  { id->f[2] };
            real_T    *f3  { id->f[3] };
            real_T    temp;
            int_T     i;
            int_T     nXc  { 71 };

            rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
            

            /* Save the state values at time t in y, we'll use x as ynew. */
            (void) std::memcpy(y, x,
static_cast<uint_T>(nXc)*sizeof(real_T));

            /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
            /* f0 = f(t,y) */
            rtsiSetdX(si, f0);
                        sim_ROV_v0_R2018b_derivatives();

            /* f1 = f(t + (h/2), y + (h/2)*f0) */
            temp = 0.5 * h;
            for (i = 0; i < nXc; i++) {
                x[i] = y[i] + (temp*f0[i]);
            }
            rtsiSetT(si, t + temp);
            rtsiSetdX(si, f1);
            
            


            sim_ROV_v0_R2018b_step();


                        sim_ROV_v0_R2018b_derivatives();

            
            /* f2 = f(t + (h/2), y + (h/2)*f1) */
            for (i = 0; i < nXc; i++) {
                x[i] = y[i] + (temp*f1[i]);
            }
            rtsiSetdX(si, f2);
            
            


            sim_ROV_v0_R2018b_step();


                        sim_ROV_v0_R2018b_derivatives();

            
            /* f3 = f(t + h, y + h*f2) */
            for (i = 0; i < nXc; i++) {
                x[i] = y[i] + (h*f2[i]);
            }
            rtsiSetT(si, tnew);
            rtsiSetdX(si, f3);
            
            


            sim_ROV_v0_R2018b_step();


                        sim_ROV_v0_R2018b_derivatives();

            
            /* tnew = t + h
            ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
            temp = h / 6.0;
            for (i = 0; i < nXc; i++) {
                x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
            }





            rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
            

    }
    

    
    

                
        
        
        
        
        
                                
        
                            /* System initialize for atomic system: */
                

        


          void sim_ROV_v0_R_LowpassFilter_Init(DW_LowpassFilter_sim_ROV_v0_R_T *localDW)
    {
    
                
    
b_dspcodegen_FIRFilter_sim_RO_T *iobj_0;

    




                                    




                                                
                                    /* {S!d482}Start for MATLABSystem: '<S30>/Lowpass Filter' */
localDW->obj._pobj0.matlabCodegenIsDeleted = true;
localDW->obj.NumChannels = -1;
localDW->obj.matlabCodegenIsDeleted = false;
localDW->objisempty = true;
localDW->obj.isInitialized = 1;
if (localDW->obj.NumChannels == -1) {
    localDW->obj.NumChannels = 1;
}
localDW->obj._pobj0.isInitialized = 0;
localDW->obj._pobj0.isInitialized = 0;
/* System object Constructor function: dsp.FIRFilter */
localDW->obj._pobj0.cSFunObject.P0_InitialStates = 0.0;
localDW->obj._pobj0.cSFunObject.P1_Coefficients[0] = 0.1281357124396979;
localDW->obj._pobj0.cSFunObject.P1_Coefficients[1] = 0.37186432519028217;
localDW->obj._pobj0.cSFunObject.P1_Coefficients[2] = 0.37186432519028217;
localDW->obj._pobj0.cSFunObject.P1_Coefficients[3] = 0.1281357124396979;
localDW->obj._pobj0.matlabCodegenIsDeleted = false;
localDW->obj.FilterObj = &localDW->obj._pobj0;
localDW->obj.isSetupComplete = true;
/* {E!d482}End of Start for MATLABSystem: '<S30>/Lowpass Filter' */

/* {S!d484}InitializeConditions for MATLABSystem: '<S30>/Lowpass Filter' */
iobj_0 = localDW->obj.FilterObj;
if (iobj_0->isInitialized == 1) {
    /* System object Initialization function: dsp.FIRFilter */
    iobj_0->cSFunObject.W0_states[0] = iobj_0->cSFunObject.P0_InitialStates;
    iobj_0->cSFunObject.W0_states[1] = iobj_0->cSFunObject.P0_InitialStates;
    iobj_0->cSFunObject.W0_states[2] = iobj_0->cSFunObject.P0_InitialStates;
}
/* {E!d484}End of InitializeConditions for MATLABSystem: '<S30>/Lowpass Filter' */





    




                            }
        


            
        


                    /* Output and update for atomic system: */
            
                        

        


          void sim_ROV_v0_R2018b_LowpassFilter(real_T rtu_0, B_LowpassFilter_sim_ROV_v0_R2_T *localB, DW_LowpassFilter_sim_ROV_v0_R_T *localDW)
    {
    
                                            
            
b_dsp_FIRFilter_0_sim_ROV_v0__T *obj_0;
b_dspcodegen_FIRFilter_sim_RO_T *obj;
real_T zNext;

            
        




                                                            
        




                                                    
                                    



/* {S!d486}MATLABSystem: '<S30>/Lowpass Filter' */
obj = localDW->obj.FilterObj;
if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->isSetupComplete = true;
    /* System object Initialization function: dsp.FIRFilter */
    obj->cSFunObject.W0_states[0] = obj->cSFunObject.P0_InitialStates;
    obj->cSFunObject.W0_states[1] = obj->cSFunObject.P0_InitialStates;
    obj->cSFunObject.W0_states[2] = obj->cSFunObject.P0_InitialStates;
}
obj_0 = &obj->cSFunObject;
/* System object Outputs function: dsp.FIRFilter */
zNext = rtu_0;
for ( int32_T k{0}; k < 1; k++) {
    real_T zCurr;
    real_T zCurr_0;
    real_T zCurr_1;
    real_T zCurr_2;
    /* load input sample */
    /* shift state */
    zCurr = zNext;
    zNext = obj_0->W0_states[0];
    obj_0->W0_states[0] = zCurr;
    /* compute one tap */
    zCurr_0 = obj_0->P1_Coefficients[0] * zCurr;
    /* shift state */
    zCurr = zNext;
    zNext = obj_0->W0_states[1];
    obj_0->W0_states[1] = zCurr;
    /* compute one tap */
    zCurr_1 = obj_0->P1_Coefficients[1] * zCurr;
    /* shift state */
    zCurr = zNext;
    zNext = obj_0->W0_states[2];
    obj_0->W0_states[2] = zCurr;
    /* compute one tap */
    zCurr_2 = obj_0->P1_Coefficients[2] * zCurr;
    /* compute last tap */
    zCurr = obj_0->P1_Coefficients[3] * zNext;
    /* store output sample */
    zNext = ((zCurr_0 + zCurr_1) + zCurr_2) + zCurr;
}
/* {S!d488}MATLABSystem: '<S30>/Lowpass Filter' */
localB->LowpassFilter = zNext;





        



                        
        
            
                    }
        


                                





                                    /* Termination for atomic system: */
                

        


          void sim_ROV_v0_R_LowpassFilter_Term(DW_LowpassFilter_sim_ROV_v0_R_T *localDW)
    {
    
                
    
b_dspcodegen_FIRFilter_sim_RO_T *obj;

    




                                    




                                    
                        
                                    /* {S!d490}Terminate for MATLABSystem: '<S30>/Lowpass Filter' */
if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
        obj = localDW->obj.FilterObj;
        if (obj->isInitialized == 1) {
            obj->isInitialized = 2;
        }
        localDW->obj.NumChannels = -1;
    }
}
if (!localDW->obj._pobj0.matlabCodegenIsDeleted) {
    localDW->obj._pobj0.matlabCodegenIsDeleted = true;
    if (localDW->obj._pobj0.isInitialized == 1) {
        localDW->obj._pobj0.isInitialized = 2;
    }
}
/* {E!d490}End of Terminate for MATLABSystem: '<S30>/Lowpass Filter' */







    




                            }
        


        

                                
        
                            /* System initialize for atomic system: */
                

        


          void sim_ROV_v0__LowpassFilter3_Init(DW_LowpassFilter3_sim_ROV_v0__T *localDW)
    {
    
                
    
b_dspcodegen_FIRFilter_sim_RO_T *iobj_0;

    




                                    




                                                
                                    /* {S!d492}Start for MATLABSystem: '<S30>/Lowpass Filter3' */
localDW->obj._pobj0.matlabCodegenIsDeleted = true;
localDW->obj.NumChannels = -1;
localDW->obj.matlabCodegenIsDeleted = false;
localDW->objisempty = true;
localDW->obj.isInitialized = 1;
if (localDW->obj.NumChannels == -1) {
    localDW->obj.NumChannels = 1;
}
localDW->obj._pobj0.isInitialized = 0;
localDW->obj._pobj0.isInitialized = 0;
/* System object Constructor function: dsp.FIRFilter */
localDW->obj._pobj0.cSFunObject.P0_InitialStates = 0.0;
localDW->obj._pobj0.cSFunObject.P1_Coefficients[0] = 0.1281357124396979;
localDW->obj._pobj0.cSFunObject.P1_Coefficients[1] = 0.37186432519028217;
localDW->obj._pobj0.cSFunObject.P1_Coefficients[2] = 0.37186432519028217;
localDW->obj._pobj0.cSFunObject.P1_Coefficients[3] = 0.1281357124396979;
localDW->obj._pobj0.matlabCodegenIsDeleted = false;
localDW->obj.FilterObj = &localDW->obj._pobj0;
localDW->obj.isSetupComplete = true;
/* {E!d492}End of Start for MATLABSystem: '<S30>/Lowpass Filter3' */

/* {S!d494}InitializeConditions for MATLABSystem: '<S30>/Lowpass Filter3' */
iobj_0 = localDW->obj.FilterObj;
if (iobj_0->isInitialized == 1) {
    /* System object Initialization function: dsp.FIRFilter */
    iobj_0->cSFunObject.W0_states[0] = iobj_0->cSFunObject.P0_InitialStates;
    iobj_0->cSFunObject.W0_states[1] = iobj_0->cSFunObject.P0_InitialStates;
    iobj_0->cSFunObject.W0_states[2] = iobj_0->cSFunObject.P0_InitialStates;
}
/* {E!d494}End of InitializeConditions for MATLABSystem: '<S30>/Lowpass Filter3' */





    




                            }
        


            
        


                    /* Output and update for atomic system: */
            
                        

        


          void sim_ROV_v0_R2018_LowpassFilter3(real_T rtu_0, B_LowpassFilter3_sim_ROV_v0_R_T *localB, DW_LowpassFilter3_sim_ROV_v0__T *localDW)
    {
    
                                            
            
b_dsp_FIRFilter_0_sim_ROV_v0__T *obj_0;
b_dspcodegen_FIRFilter_sim_RO_T *obj;
real_T zNext;

            
        




                                                            
        




                                                    
                                    



/* {S!d496}MATLABSystem: '<S30>/Lowpass Filter3' */
obj = localDW->obj.FilterObj;
if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->isSetupComplete = true;
    /* System object Initialization function: dsp.FIRFilter */
    obj->cSFunObject.W0_states[0] = obj->cSFunObject.P0_InitialStates;
    obj->cSFunObject.W0_states[1] = obj->cSFunObject.P0_InitialStates;
    obj->cSFunObject.W0_states[2] = obj->cSFunObject.P0_InitialStates;
}
obj_0 = &obj->cSFunObject;
/* System object Outputs function: dsp.FIRFilter */
zNext = rtu_0;
for ( int32_T k{0}; k < 1; k++) {
    real_T zCurr;
    real_T zCurr_0;
    real_T zCurr_1;
    real_T zCurr_2;
    /* load input sample */
    /* shift state */
    zCurr = zNext;
    zNext = obj_0->W0_states[0];
    obj_0->W0_states[0] = zCurr;
    /* compute one tap */
    zCurr_0 = obj_0->P1_Coefficients[0] * zCurr;
    /* shift state */
    zCurr = zNext;
    zNext = obj_0->W0_states[1];
    obj_0->W0_states[1] = zCurr;
    /* compute one tap */
    zCurr_1 = obj_0->P1_Coefficients[1] * zCurr;
    /* shift state */
    zCurr = zNext;
    zNext = obj_0->W0_states[2];
    obj_0->W0_states[2] = zCurr;
    /* compute one tap */
    zCurr_2 = obj_0->P1_Coefficients[2] * zCurr;
    /* compute last tap */
    zCurr = obj_0->P1_Coefficients[3] * zNext;
    /* store output sample */
    zNext = ((zCurr_0 + zCurr_1) + zCurr_2) + zCurr;
}
/* {S!d498}MATLABSystem: '<S30>/Lowpass Filter3' */
localB->LowpassFilter3 = zNext;





        



                        
        
            
                    }
        


                                





                                    /* Termination for atomic system: */
                

        


          void sim_ROV_v0__LowpassFilter3_Term(DW_LowpassFilter3_sim_ROV_v0__T *localDW)
    {
    
                
    
b_dspcodegen_FIRFilter_sim_RO_T *obj;

    




                                    




                                    
                        
                                    /* {S!d500}Terminate for MATLABSystem: '<S30>/Lowpass Filter3' */
if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
        obj = localDW->obj.FilterObj;
        if (obj->isInitialized == 1) {
            obj->isInitialized = 2;
        }
        localDW->obj.NumChannels = -1;
    }
}
if (!localDW->obj._pobj0.matlabCodegenIsDeleted) {
    localDW->obj._pobj0.matlabCodegenIsDeleted = true;
    if (localDW->obj._pobj0.isInitialized == 1) {
        localDW->obj._pobj0.isInitialized = 2;
    }
}
/* {E!d500}End of Terminate for MATLABSystem: '<S30>/Lowpass Filter3' */







    




                            }
        


        

        

    

                        

                

         

            
                real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
        {
            uint32_T hi;
uint32_T lo;
/* Uniform random number generator (random number between 0 and 1)

#define IA      16807                      magic multiplier = 7^5
#define IM      2147483647                 modulus = 2^31-1
#define IQ      127773                     IM div IA
#define IR      2836                       IM modulo IA
#define S       4.656612875245797e-10      reciprocal of 2^31-1
test = IA * (seed % IQ) - IR * (seed/IQ)
seed = test < 0 ? (test + IM) : test
return (seed*S)
 */
lo = *u % 127773U * 16807U;
hi = *u / 127773U * 2836U;
if (lo < hi) {
    *u = 2147483647U - (hi - lo);
} else {
    *u = lo - hi;
}
return static_cast<real_T>(*u) * 4.6566128752457969E-10;


        }
            

            



            


                        

                

         

            
                real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u)
        {
            real_T si;
real_T sr;
real_T y;





/* Normal (Gaussian) random number generator */
do {
    sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = sr * sr + si * si;
} while (si > 1.0);
y = std::sqrt(-2.0 * std::log(si) / si) * sr;
return y;


        }
            

            



                        




        /* Model step function */
        
                    
        void sim_ROV_v0_R2018b_step(void) 
        {
            


        

                
        

        

        




                
            

            if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M)) {
        
            /* set solver stop time */
        if (!(sim_ROV_v0_R2018b_M->Timing.clockTick0+1)) {
            rtsiSetSolverStopTime(&sim_ROV_v0_R2018b_M->solverInfo, ((sim_ROV_v0_R2018b_M->Timing.clockTickH0 + 1) * sim_ROV_v0_R2018b_M->Timing.stepSize0 * 4294967296.0));
        } else {
            rtsiSetSolverStopTime(&sim_ROV_v0_R2018b_M->solverInfo, ((sim_ROV_v0_R2018b_M->Timing.clockTick0  + 1) * sim_ROV_v0_R2018b_M->Timing.stepSize0 + sim_ROV_v0_R2018b_M->Timing.clockTickH0 * sim_ROV_v0_R2018b_M->Timing.stepSize0 * 4294967296.0));
        }


    

        } /* end MajorTimeStep */
        /* Update absolute time of base rate at minor time step */
        if (rtmIsMinorTimeStep(sim_ROV_v0_R2018b_M)) {
            sim_ROV_v0_R2018b_M->Timing.t[0] = rtsiGetT(&sim_ROV_v0_R2018b_M->solverInfo);
        }
        





        




                            {
            
real_T rtb_T200TransferFunction1_0[36];
real_T tmp_6[36];
real_T tmp_7[12];
real_T tmp_0[9];
real_T tmp_1[9];
real_T tmp_2[9];
real_T tmp_3[9];
real_T tmp_4[9];
real_T tmp_5[9];
real_T rtb_uDLookupTable[8];
real_T a[6];
real_T tmp[6];
real_T (*lastU)[6];
real_T rtb_Sum4[3];
real_T rtb_Sum4_j[3];
real_T F_g_tmp;
real_T rtb_T200TransferFunction1;
real_T rtb_T200TransferFunction2;
real_T rtb_WhiteNoise_idx_0;
real_T rtb_WhiteNoise_idx_1;
real_T rtb_WhiteNoise_idx_2;
real_T rtb_jxi;
real_T rtb_jxi_tmp;
real_T rtb_kxi;
int32_T i;
int32_T i_0;
int32_T tmp_8;

                                    
                
                                    




/* {S!d632}Integrator: '<S30>/Integrator6' */
sim_ROV_v0_R2018b_B.Integrator6 = sim_ROV_v0_R2018b_X.Integrator6_CSTATE;
/* {S!d634}Integrator: '<S30>/Integrator7' */
sim_ROV_v0_R2018b_B.Integrator7 = sim_ROV_v0_R2018b_X.Integrator7_CSTATE;
/* {S!d636}Integrator: '<S30>/Integrator8' */
sim_ROV_v0_R2018b_B.Integrator8 = sim_ROV_v0_R2018b_X.Integrator8_CSTATE;
/* {S!d638}Integrator: '<S30>/Integrator' */
sim_ROV_v0_R2018b_B.Integrator = sim_ROV_v0_R2018b_X.Integrator_CSTATE;
/* {S!d640}Integrator: '<S30>/Integrator1' */
sim_ROV_v0_R2018b_B.Integrator1 = sim_ROV_v0_R2018b_X.Integrator1_CSTATE;
/* {S!d642}Integrator: '<S30>/Integrator2' */
sim_ROV_v0_R2018b_B.Integrator2 = sim_ROV_v0_R2018b_X.Integrator2_CSTATE;
/* {S!d644}Integrator: '<S30>/Integrator3' */
sim_ROV_v0_R2018b_B.Integrator3 = sim_ROV_v0_R2018b_X.Integrator3_CSTATE;
/* {S!d646}Integrator: '<S30>/Integrator4' */
sim_ROV_v0_R2018b_B.Integrator4 = sim_ROV_v0_R2018b_X.Integrator4_CSTATE;
/* {S!d648}Integrator: '<S30>/Integrator5' */
sim_ROV_v0_R2018b_B.Integrator5 = sim_ROV_v0_R2018b_X.Integrator5_CSTATE;
/* {S!d650}Gain: '<S16>/lbf → N' incorporates:
 *  TransferFcn: '<S20>/T200 Transfer Function 1'
 *  TransferFcn: '<S20>/T200 Transfer Function 2'
 *  TransferFcn: '<S20>/T200 Transfer Function 3'
 *  TransferFcn: '<S20>/T200 Transfer Function 4'
 *  TransferFcn: '<S20>/T200 Transfer Function 5'
 *  TransferFcn: '<S20>/T200 Transfer Function 6'
 *  TransferFcn: '<S20>/T200 Transfer Function 7'
 *  TransferFcn: '<S20>/T200 Transfer Function 8'
 */
sim_ROV_v0_R2018b_B.ThrustN[0] = (((sim_ROV_v0_R2018b_P.T200TransferFunction1_C[0] * sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[0] + sim_ROV_v0_R2018b_P.T200TransferFunction1_C[1] * sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[1]) + sim_ROV_v0_R2018b_P.T200TransferFunction1_C[2] * sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[2]) + sim_ROV_v0_R2018b_P.T200TransferFunction1_C[3] * sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[3]) * sim_ROV_v0_R2018b_P.lbfN_Gain;
sim_ROV_v0_R2018b_B.ThrustN[1] = (((sim_ROV_v0_R2018b_P.T200TransferFunction2_C[0] * sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[0] + sim_ROV_v0_R2018b_P.T200TransferFunction2_C[1] * sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[1]) + sim_ROV_v0_R2018b_P.T200TransferFunction2_C[2] * sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[2]) + sim_ROV_v0_R2018b_P.T200TransferFunction2_C[3] * sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[3]) * sim_ROV_v0_R2018b_P.lbfN_Gain;
sim_ROV_v0_R2018b_B.ThrustN[2] = (((sim_ROV_v0_R2018b_P.T200TransferFunction3_C[0] * sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[0] + sim_ROV_v0_R2018b_P.T200TransferFunction3_C[1] * sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[1]) + sim_ROV_v0_R2018b_P.T200TransferFunction3_C[2] * sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[2]) + sim_ROV_v0_R2018b_P.T200TransferFunction3_C[3] * sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[3]) * sim_ROV_v0_R2018b_P.lbfN_Gain;
sim_ROV_v0_R2018b_B.ThrustN[3] = (((sim_ROV_v0_R2018b_P.T200TransferFunction4_C[0] * sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[0] + sim_ROV_v0_R2018b_P.T200TransferFunction4_C[1] * sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[1]) + sim_ROV_v0_R2018b_P.T200TransferFunction4_C[2] * sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[2]) + sim_ROV_v0_R2018b_P.T200TransferFunction4_C[3] * sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[3]) * sim_ROV_v0_R2018b_P.lbfN_Gain;
sim_ROV_v0_R2018b_B.ThrustN[4] = (((sim_ROV_v0_R2018b_P.T200TransferFunction5_C[0] * sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[0] + sim_ROV_v0_R2018b_P.T200TransferFunction5_C[1] * sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[1]) + sim_ROV_v0_R2018b_P.T200TransferFunction5_C[2] * sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[2]) + sim_ROV_v0_R2018b_P.T200TransferFunction5_C[3] * sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[3]) * sim_ROV_v0_R2018b_P.lbfN_Gain;
sim_ROV_v0_R2018b_B.ThrustN[5] = (((sim_ROV_v0_R2018b_P.T200TransferFunction6_C[0] * sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[0] + sim_ROV_v0_R2018b_P.T200TransferFunction6_C[1] * sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[1]) + sim_ROV_v0_R2018b_P.T200TransferFunction6_C[2] * sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[2]) + sim_ROV_v0_R2018b_P.T200TransferFunction6_C[3] * sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[3]) * sim_ROV_v0_R2018b_P.lbfN_Gain;
sim_ROV_v0_R2018b_B.ThrustN[6] = (((sim_ROV_v0_R2018b_P.T200TransferFunction7_C[0] * sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[0] + sim_ROV_v0_R2018b_P.T200TransferFunction7_C[1] * sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[1]) + sim_ROV_v0_R2018b_P.T200TransferFunction7_C[2] * sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[2]) + sim_ROV_v0_R2018b_P.T200TransferFunction7_C[3] * sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[3]) * sim_ROV_v0_R2018b_P.lbfN_Gain;
sim_ROV_v0_R2018b_B.ThrustN[7] = (((sim_ROV_v0_R2018b_P.T200TransferFunction8_C[0] * sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[0] + sim_ROV_v0_R2018b_P.T200TransferFunction8_C[1] * sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[1]) + sim_ROV_v0_R2018b_P.T200TransferFunction8_C[2] * sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[2]) + sim_ROV_v0_R2018b_P.T200TransferFunction8_C[3] * sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[3]) * sim_ROV_v0_R2018b_P.lbfN_Gain;
for (i = 0; i < 6; i++) {
    /* {S!d652}Gain: '<S2>/Thrust Configuration Matrix' */
    rtb_WhiteNoise_idx_0 = 0.0;
    for (i_0 = 0; i_0 < 8; i_0++) {
        rtb_WhiteNoise_idx_0 += sim_ROV_v0_R2018b_P.TCM[6 * i_0 + i] * sim_ROV_v0_R2018b_B.ThrustN[i_0];
    }
    sim_ROV_v0_R2018b_B.ForcesMoments[i] = rtb_WhiteNoise_idx_0;
    /* {E!d652}End of Gain: '<S2>/Thrust Configuration Matrix' */

    /* {S!d654}Integrator: '<S19>/Integrator' */
    sim_ROV_v0_R2018b_B.Pose[i] = sim_ROV_v0_R2018b_X.Integrator_CSTATE_e[i];
}
/* {S!d656}MATLAB Function: '<S24>/hydrostatics' incorporates:
 *  Constant: '<S24>/Buoyancy'
 *  Constant: '<S24>/CoB'
 *  Constant: '<S24>/CoM'
 *  Constant: '<S24>/Gravity Force'
 *  MATLAB Function: '<S19>/kinematics'
 */
sim_ROV_v0_R2018b_DW.sfEvent_o = sim_ROV_v0_R2018b_CALL_EVENT;
rtb_T200TransferFunction1 = std::sin(sim_ROV_v0_R2018b_B.Pose[4]);
rtb_WhiteNoise_idx_2 = sim_ROV_v0_R2018b_P.W - sim_ROV_v0_R2018b_P.B;
sim_ROV_v0_R2018b_B.F_g[0] = rtb_WhiteNoise_idx_2 * rtb_T200TransferFunction1;
rtb_T200TransferFunction2 = std::cos(sim_ROV_v0_R2018b_B.Pose[4]);
rtb_jxi_tmp = std::sin(sim_ROV_v0_R2018b_B.Pose[3]);
sim_ROV_v0_R2018b_B.F_g[1] = -rtb_WhiteNoise_idx_2 * rtb_T200TransferFunction2 * rtb_jxi_tmp;
rtb_WhiteNoise_idx_0 = std::cos(sim_ROV_v0_R2018b_B.Pose[3]);
rtb_WhiteNoise_idx_1 = std::cos(sim_ROV_v0_R2018b_B.Pose[4]);
sim_ROV_v0_R2018b_B.F_g[2] = -rtb_WhiteNoise_idx_2 * rtb_WhiteNoise_idx_1 * rtb_WhiteNoise_idx_0;
rtb_WhiteNoise_idx_2 = sim_ROV_v0_R2018b_P.r_g[2] * sim_ROV_v0_R2018b_P.W - sim_ROV_v0_R2018b_P.r_b[2] * sim_ROV_v0_R2018b_P.B;
rtb_kxi = sim_ROV_v0_R2018b_P.r_g[1] * sim_ROV_v0_R2018b_P.W - sim_ROV_v0_R2018b_P.r_b[1] * sim_ROV_v0_R2018b_P.B;
sim_ROV_v0_R2018b_B.F_g[3] = -rtb_kxi * rtb_T200TransferFunction2 * rtb_WhiteNoise_idx_0 + rtb_WhiteNoise_idx_2 * rtb_T200TransferFunction2 * rtb_jxi_tmp;
F_g_tmp = sim_ROV_v0_R2018b_P.r_g[0] * sim_ROV_v0_R2018b_P.W - sim_ROV_v0_R2018b_P.r_b[0] * sim_ROV_v0_R2018b_P.B;
sim_ROV_v0_R2018b_B.F_g[4] = F_g_tmp * rtb_T200TransferFunction2 * rtb_WhiteNoise_idx_0 + rtb_WhiteNoise_idx_2 * rtb_T200TransferFunction1;
sim_ROV_v0_R2018b_B.F_g[5] = -F_g_tmp * rtb_T200TransferFunction2 * rtb_jxi_tmp - rtb_kxi * rtb_T200TransferFunction1;
for (i_0 = 0; i_0 < 6; i_0++) {
    /* {S!d658}Product: '<S23>/Product' incorporates:
 *  Abs: '<S23>/Abs'
 *  Integrator: '<S18>/Integrator'
 */
    a[i_0] = sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[i_0] * std::abs(sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[i_0]);
    /* {S!d660}Gain: '<S23>/Linear Damping' incorporates:
 *  Integrator: '<S18>/Integrator'
 */
    rtb_jxi = 0.0;
    for (i = 0; i < 6; i++) {
        rtb_jxi += sim_ROV_v0_R2018b_P.D_linear[6 * i + i_0] * sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[i];
    }
    tmp[i_0] = rtb_jxi;
    /* {E!d660}End of Gain: '<S23>/Linear Damping' */
}
for (i_0 = 0; i_0 < 6; i_0++) {
    /* {S!d662}Gain: '<S23>/Quadratic Damping' */
    rtb_jxi = 0.0;
    for (i = 0; i < 6; i++) {
        rtb_jxi += sim_ROV_v0_R2018b_P.D_quadratic[6 * i + i_0] * a[i];
    }
    /* {S!d664}Sum: '<S23>/Sum' incorporates:
 *  Gain: '<S23>/Quadratic Damping'
 */
    sim_ROV_v0_R2018b_B.Sum[i_0] = tmp[i_0] + rtb_jxi;
}
/* {S!d666}MATLAB Function: '<S22>/Rigid Body Coriolis & Centripetal' incorporates:
 *  Constant: '<S22>/Inertia Tensor'
 *  Integrator: '<S18>/Integrator'
 */
sim_ROV_v0_R2018b_DW.sfEvent_ou = sim_ROV_v0_R2018b_CALL_EVENT;
rtb_T200TransferFunction2 = sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[4];
rtb_jxi = sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[3];
rtb_WhiteNoise_idx_2 = sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[5];
for (i_0 = 0; i_0 < 3; i_0++) {
    rtb_Sum4[i_0] = (sim_ROV_v0_R2018b_P.I[i_0 + 3] * rtb_T200TransferFunction2 + sim_ROV_v0_R2018b_P.I[i_0] * rtb_jxi) + sim_ROV_v0_R2018b_P.I[i_0 + 6] * rtb_WhiteNoise_idx_2;
}
/* {S!d668}MATLAB Function: '<S22>/Added Coriolis & Centripetal' incorporates:
 *  Constant: '<S22>/Added Mass'
 *  Integrator: '<S18>/Integrator'
 */
sim_ROV_v0_R2018b_DW.sfEvent_i = sim_ROV_v0_R2018b_CALL_EVENT;
for (i_0 = 0; i_0 < 6; i_0++) {
    rtb_T200TransferFunction2 = 0.0;
    for (i = 0; i < 6; i++) {
        rtb_T200TransferFunction2 += sim_ROV_v0_R2018b_P.M_addedMass[6 * i + i_0] * sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[i];
    }
    a[i_0] = rtb_T200TransferFunction2;
}
/* {S!d670}MATLAB Function: '<S22>/Rigid Body Coriolis & Centripetal' incorporates:
 *  Constant: '<S22>/CoM'
 *  Constant: '<S22>/Rigid Body Mass'
 *  Integrator: '<S18>/Integrator'
 */
rtb_jxi = -sim_ROV_v0_R2018b_P.m * 0.0;
tmp_0[0] = rtb_jxi;
tmp_0[3] = -sim_ROV_v0_R2018b_P.m * -sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[5];
tmp_0[6] = -sim_ROV_v0_R2018b_P.m * sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[4];
tmp_0[1] = -sim_ROV_v0_R2018b_P.m * sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[5];
tmp_0[4] = rtb_jxi;
tmp_0[7] = -sim_ROV_v0_R2018b_P.m * -sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[3];
tmp_0[2] = -sim_ROV_v0_R2018b_P.m * -sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[4];
tmp_0[5] = -sim_ROV_v0_R2018b_P.m * sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[3];
tmp_0[8] = rtb_jxi;
tmp_1[0] = 0.0;
tmp_1[3] = -sim_ROV_v0_R2018b_P.r_g[2];
tmp_1[6] = sim_ROV_v0_R2018b_P.r_g[1];
tmp_1[1] = sim_ROV_v0_R2018b_P.r_g[2];
tmp_1[4] = 0.0;
tmp_1[7] = -sim_ROV_v0_R2018b_P.r_g[0];
tmp_1[2] = -sim_ROV_v0_R2018b_P.r_g[1];
tmp_1[5] = sim_ROV_v0_R2018b_P.r_g[0];
tmp_1[8] = 0.0;
tmp_3[0] = sim_ROV_v0_R2018b_P.m * 0.0;
tmp_3[3] = sim_ROV_v0_R2018b_P.m * -sim_ROV_v0_R2018b_P.r_g[2];
tmp_3[6] = sim_ROV_v0_R2018b_P.m * sim_ROV_v0_R2018b_P.r_g[1];
tmp_3[1] = sim_ROV_v0_R2018b_P.m * sim_ROV_v0_R2018b_P.r_g[2];
tmp_3[4] = sim_ROV_v0_R2018b_P.m * 0.0;
tmp_3[7] = sim_ROV_v0_R2018b_P.m * -sim_ROV_v0_R2018b_P.r_g[0];
tmp_3[2] = sim_ROV_v0_R2018b_P.m * -sim_ROV_v0_R2018b_P.r_g[1];
tmp_3[5] = sim_ROV_v0_R2018b_P.m * sim_ROV_v0_R2018b_P.r_g[0];
tmp_3[8] = sim_ROV_v0_R2018b_P.m * 0.0;
tmp_4[0] = 0.0;
tmp_4[3] = -sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[5];
tmp_4[6] = sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[4];
tmp_4[1] = sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[5];
tmp_4[4] = 0.0;
tmp_4[7] = -sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[3];
tmp_4[2] = -sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[4];
tmp_4[5] = sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[3];
tmp_4[8] = 0.0;
for (i_0 = 0; i_0 < 3; i_0++) {
    i = 3 * i_0 + 1;
    rtb_jxi = tmp_4[i];
    rtb_WhiteNoise_idx_2 = tmp_4[3 * i_0];
    tmp_8 = 3 * i_0 + 2;
    rtb_T200TransferFunction2 = tmp_4[tmp_8];
    rtb_T200TransferFunction1 = tmp_1[i];
    rtb_kxi = tmp_1[3 * i_0];
    F_g_tmp = tmp_1[tmp_8];
    for (i = 0; i < 3; i++) {
        tmp_8 = 3 * i_0 + i;
        tmp_5[tmp_8] = (tmp_3[i + 3] * rtb_jxi + rtb_WhiteNoise_idx_2 * tmp_3[i]) + tmp_3[i + 6] * rtb_T200TransferFunction2;
        tmp_2[tmp_8] = (tmp_0[i + 3] * rtb_T200TransferFunction1 + rtb_kxi * tmp_0[i]) + tmp_0[i + 6] * F_g_tmp;
    }
}
rtb_T200TransferFunction1_0[0] = sim_ROV_v0_R2018b_P.m * 0.0;
rtb_T200TransferFunction1_0[6] = sim_ROV_v0_R2018b_P.m * -sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[5];
rtb_T200TransferFunction1_0[12] = sim_ROV_v0_R2018b_P.m * sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[4];
rtb_T200TransferFunction1_0[1] = sim_ROV_v0_R2018b_P.m * sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[5];
rtb_T200TransferFunction1_0[7] = sim_ROV_v0_R2018b_P.m * 0.0;
rtb_T200TransferFunction1_0[13] = sim_ROV_v0_R2018b_P.m * -sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[3];
rtb_T200TransferFunction1_0[2] = sim_ROV_v0_R2018b_P.m * -sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[4];
rtb_T200TransferFunction1_0[8] = sim_ROV_v0_R2018b_P.m * sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[3];
rtb_T200TransferFunction1_0[14] = sim_ROV_v0_R2018b_P.m * 0.0;
for (i_0 = 0; i_0 < 3; i_0++) {
    i = (i_0 + 3) * 6;
    rtb_T200TransferFunction1_0[i] = tmp_2[3 * i_0];
    rtb_T200TransferFunction1_0[6 * i_0 + 3] = tmp_5[3 * i_0];
    tmp_8 = 3 * i_0 + 1;
    rtb_T200TransferFunction1_0[i + 1] = tmp_2[tmp_8];
    rtb_T200TransferFunction1_0[6 * i_0 + 4] = tmp_5[tmp_8];
    tmp_8 = 3 * i_0 + 2;
    rtb_T200TransferFunction1_0[i + 2] = tmp_2[tmp_8];
    rtb_T200TransferFunction1_0[6 * i_0 + 5] = tmp_5[tmp_8];
}
rtb_T200TransferFunction1_0[21] = -0.0;
rtb_T200TransferFunction1_0[27] = rtb_Sum4[2];
rtb_T200TransferFunction1_0[33] = -rtb_Sum4[1];
rtb_T200TransferFunction1_0[22] = -rtb_Sum4[2];
rtb_T200TransferFunction1_0[28] = -0.0;
rtb_T200TransferFunction1_0[34] = rtb_Sum4[0];
rtb_T200TransferFunction1_0[23] = rtb_Sum4[1];
rtb_T200TransferFunction1_0[29] = -rtb_Sum4[0];
rtb_T200TransferFunction1_0[35] = -0.0;
/* {S!d672}MATLAB Function: '<S22>/Added Coriolis & Centripetal' */
tmp_6[0] = 0.0;
tmp_6[6] = 0.0;
tmp_6[12] = 0.0;
tmp_6[18] = 0.0;
tmp_6[24] = -a[2];
tmp_6[30] = a[1];
tmp_6[1] = 0.0;
tmp_6[7] = 0.0;
tmp_6[13] = 0.0;
tmp_6[19] = a[2];
tmp_6[25] = 0.0;
tmp_6[31] = -a[0];
tmp_6[2] = 0.0;
tmp_6[8] = 0.0;
tmp_6[14] = 0.0;
tmp_6[20] = -a[1];
tmp_6[26] = a[0];
tmp_6[32] = 0.0;
tmp_6[3] = 0.0;
tmp_6[9] = -a[2];
tmp_6[15] = a[1];
tmp_6[21] = 0.0;
tmp_6[27] = -a[5];
tmp_6[33] = a[4];
tmp_6[4] = a[2];
tmp_6[10] = 0.0;
tmp_6[16] = -a[0];
tmp_6[22] = a[5];
tmp_6[28] = 0.0;
tmp_6[34] = -a[3];
tmp_6[5] = -a[1];
tmp_6[11] = a[0];
tmp_6[17] = 0.0;
tmp_6[23] = -a[4];
tmp_6[29] = a[3];
tmp_6[35] = 0.0;
for (i_0 = 0; i_0 < 6; i_0++) {
    /* {S!d674}MATLAB Function: '<S22>/Rigid Body Coriolis & Centripetal' */
    rtb_jxi = 0.0;
    /* {S!d676}MATLAB Function: '<S22>/Added Coriolis & Centripetal' */
    rtb_WhiteNoise_idx_2 = 0.0;
    for (i = 0; i < 6; i++) {
        /* {S!d678}Integrator: '<S18>/Integrator' incorporates:
 *  MATLAB Function: '<S22>/Rigid Body Coriolis & Centripetal'
 */
        rtb_T200TransferFunction2 = sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[i];
        /* {S!d680}MATLAB Function: '<S22>/Rigid Body Coriolis & Centripetal' incorporates:
 *  Integrator: '<S18>/Integrator'
 *  MATLAB Function: '<S22>/Added Coriolis & Centripetal'
 */
        tmp_8 = 6 * i + i_0;
        rtb_jxi += rtb_T200TransferFunction1_0[tmp_8] * rtb_T200TransferFunction2;
        /* {S!d682}MATLAB Function: '<S22>/Added Coriolis & Centripetal' incorporates:
 *  Integrator: '<S18>/Integrator'
 */
        rtb_WhiteNoise_idx_2 += tmp_6[tmp_8] * rtb_T200TransferFunction2;
    }
    /* {S!d684}Sum: '<S22>/Add' incorporates:
 *  MATLAB Function: '<S22>/Added Coriolis & Centripetal'
 *  MATLAB Function: '<S22>/Rigid Body Coriolis & Centripetal'
 */
    rtb_T200TransferFunction2 = rtb_jxi + rtb_WhiteNoise_idx_2;
    sim_ROV_v0_R2018b_B.Add[i_0] = rtb_T200TransferFunction2;
    /* {S!d686}Sum: '<S18>/Sum' incorporates:
 *  Sum: '<S18>/Sum1'
 *  Sum: '<S18>/Sum2'
 */
    a[i_0] = sim_ROV_v0_R2018b_B.ForcesMoments[i_0] - ((sim_ROV_v0_R2018b_B.F_g[i_0] + sim_ROV_v0_R2018b_B.Sum[i_0]) + rtb_T200TransferFunction2);
}
for (i_0 = 0; i_0 < 6; i_0++) {
    /* {S!d688}Product: '<S18>/Product1' incorporates:
 *  Constant: '<S18>/Inverse of total mass'
 */
    rtb_T200TransferFunction2 = 0.0;
    for (i = 0; i < 6; i++) {
        rtb_T200TransferFunction2 += sim_ROV_v0_R2018b_P.Inverseoftotalmass_Value[6 * i + i_0] * a[i];
    }
    sim_ROV_v0_R2018b_B.BodyAcceleration[i_0] = rtb_T200TransferFunction2;
    /* {E!d688}End of Product: '<S18>/Product1' */
}
/* {S!d690}Sum: '<S35>/Sum4' incorporates:
 *  Constant: '<S35>/Measurement bias'
 *  Constant: '<S35>/Scale factors & Cross-coupling  errors '
 *  Constant: '<S35>/g-sensitive bias'
 *  Gain: '<S35>/Zero-Order Hold'
 *  Gain: '<S35>/Zero-Order Hold1'
 *  Integrator: '<S18>/Integrator'
 *  Product: '<S35>/Product'
 *  Product: '<S35>/Product1'
 *  UnitConversion: '<S33>/Unit Conversion'
 */
/* Unit Conversion - from: m/s^2 to: gn
 Expression: output = (0.101972*input) + (0) */
rtb_T200TransferFunction2 = sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[3];
rtb_jxi = sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[4];
rtb_WhiteNoise_idx_2 = sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[5];
for (i_0 = 0; i_0 < 3; i_0++) {
    rtb_Sum4[i_0] = (((sim_ROV_v0_R2018b_P.ZeroOrderHold_Gain * rtb_T200TransferFunction2 * sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_m[i_0] + sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_m[i_0 + 3] * (sim_ROV_v0_R2018b_P.ZeroOrderHold_Gain * rtb_jxi)) + sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_m[i_0 + 6] * (sim_ROV_v0_R2018b_P.ZeroOrderHold_Gain * rtb_WhiteNoise_idx_2)) + sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_n[i_0]) + 0.10197162129779282 * sim_ROV_v0_R2018b_B.BodyAcceleration[i_0] * sim_ROV_v0_R2018b_P.ZeroOrderHold1_Gain * sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_p[i_0];
}
/* {E!d690}End of Sum: '<S35>/Sum4' */
if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M) &&
sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[2] == 0) {
    /* {S!d692}Sqrt: '<S51>/Sqrt1' incorporates:
 *  Constant: '<S51>/Constant1'
 */
    rtb_T200TransferFunction1 = std::sqrt(sim_ROV_v0_R2018b_P.Randombias_Ts);
    /* {S!d694}Product: '<S51>/Product' incorporates:
 *  Constant: '<S51>/Constant'
 *  Product: '<S51>/Divide'
 *  RandomNumber: '<S51>/White Noise'
 *  Sqrt: '<S51>/Sqrt'
 */
    sim_ROV_v0_R2018b_B.Product[0] = std::sqrt(sim_ROV_v0_R2018b_P.ThreeaxisGyroscope_g_pow[0]) / rtb_T200TransferFunction1 * sim_ROV_v0_R2018b_DW.NextOutput[0];
    sim_ROV_v0_R2018b_B.Product[1] = std::sqrt(sim_ROV_v0_R2018b_P.ThreeaxisGyroscope_g_pow[1]) / rtb_T200TransferFunction1 * sim_ROV_v0_R2018b_DW.NextOutput[1];
    sim_ROV_v0_R2018b_B.Product[2] = std::sqrt(sim_ROV_v0_R2018b_P.ThreeaxisGyroscope_g_pow[2]) / rtb_T200TransferFunction1 * sim_ROV_v0_R2018b_DW.NextOutput[2];
}
/* {S!d696}Switch: '<S50>/Switch' incorporates:
 *  Constant: '<S50>/Constant'
 *  SecondOrderIntegrator: '<S53>/Integrator, Second-Order Limited'
 */
if (sim_ROV_v0_R2018b_P.Constant_Value >= sim_ROV_v0_R2018b_P.Switch_Threshold) {
    rtb_jxi = sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[0];
} else {
    rtb_jxi = rtb_Sum4[0];
}
/* {S!d698}Sum: '<S35>/Sum1' incorporates:
 *  Switch: '<S50>/Switch'
 */
rtb_T200TransferFunction2 = rtb_jxi + sim_ROV_v0_R2018b_B.Product[0];
/* {S!d706}Saturate: '<S35>/Saturation' */
if (rtb_T200TransferFunction2 > sim_ROV_v0_R2018b_P.Saturation_UpperSat[0]) {
    /* {S!d700}Saturate: '<S35>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation[0] = sim_ROV_v0_R2018b_P.Saturation_UpperSat[0];
} else if (rtb_T200TransferFunction2 < sim_ROV_v0_R2018b_P.Saturation_LowerSat[0]) {
    /* {S!d702}Saturate: '<S35>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation[0] = sim_ROV_v0_R2018b_P.Saturation_LowerSat[0];
} else {
    /* {S!d704}Saturate: '<S35>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation[0] = rtb_T200TransferFunction2;
}
/* {S!d708}Switch: '<S50>/Switch' incorporates:
 *  Constant: '<S50>/Constant'
 *  SecondOrderIntegrator: '<S53>/Integrator, Second-Order Limited'
 */
if (sim_ROV_v0_R2018b_P.Constant_Value >= sim_ROV_v0_R2018b_P.Switch_Threshold) {
    rtb_jxi = sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[1];
} else {
    rtb_jxi = rtb_Sum4[1];
}
/* {S!d710}Sum: '<S35>/Sum1' incorporates:
 *  Switch: '<S50>/Switch'
 */
rtb_T200TransferFunction2 = rtb_jxi + sim_ROV_v0_R2018b_B.Product[1];
/* {S!d718}Saturate: '<S35>/Saturation' */
if (rtb_T200TransferFunction2 > sim_ROV_v0_R2018b_P.Saturation_UpperSat[1]) {
    /* {S!d712}Saturate: '<S35>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation[1] = sim_ROV_v0_R2018b_P.Saturation_UpperSat[1];
} else if (rtb_T200TransferFunction2 < sim_ROV_v0_R2018b_P.Saturation_LowerSat[1]) {
    /* {S!d714}Saturate: '<S35>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation[1] = sim_ROV_v0_R2018b_P.Saturation_LowerSat[1];
} else {
    /* {S!d716}Saturate: '<S35>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation[1] = rtb_T200TransferFunction2;
}
/* {S!d720}Switch: '<S50>/Switch' incorporates:
 *  Constant: '<S50>/Constant'
 *  SecondOrderIntegrator: '<S53>/Integrator, Second-Order Limited'
 */
if (sim_ROV_v0_R2018b_P.Constant_Value >= sim_ROV_v0_R2018b_P.Switch_Threshold) {
    rtb_jxi = sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[2];
} else {
    rtb_jxi = rtb_Sum4[2];
}
/* {S!d722}Sum: '<S35>/Sum1' incorporates:
 *  Switch: '<S50>/Switch'
 */
rtb_T200TransferFunction2 = rtb_jxi + sim_ROV_v0_R2018b_B.Product[2];
/* {S!d730}Saturate: '<S35>/Saturation' */
if (rtb_T200TransferFunction2 > sim_ROV_v0_R2018b_P.Saturation_UpperSat[2]) {
    /* {S!d724}Saturate: '<S35>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation[2] = sim_ROV_v0_R2018b_P.Saturation_UpperSat[2];
} else if (rtb_T200TransferFunction2 < sim_ROV_v0_R2018b_P.Saturation_LowerSat[2]) {
    /* {S!d726}Saturate: '<S35>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation[2] = sim_ROV_v0_R2018b_P.Saturation_LowerSat[2];
} else {
    /* {S!d728}Saturate: '<S35>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation[2] = rtb_T200TransferFunction2;
}
if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M) &&
sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[1] == 0) {

        sim_ROV_v0_R2018_LowpassFilter3(sim_ROV_v0_R2018b_B.Saturation[0], &sim_ROV_v0_R2018b_B.LowpassFilter3, &sim_ROV_v0_R2018b_DW.LowpassFilter3);

        sim_ROV_v0_R2018_LowpassFilter3(sim_ROV_v0_R2018b_B.Saturation[1], &sim_ROV_v0_R2018b_B.LowpassFilter4, &sim_ROV_v0_R2018b_DW.LowpassFilter4);

        sim_ROV_v0_R2018_LowpassFilter3(sim_ROV_v0_R2018b_B.Saturation[2], &sim_ROV_v0_R2018b_B.LowpassFilter5, &sim_ROV_v0_R2018b_DW.LowpassFilter5);

}
/* {S!d734}MATLAB Function: '<S19>/kinematics' incorporates:
 *  Integrator: '<S18>/Integrator'
 */
sim_ROV_v0_R2018b_DW.sfEvent = sim_ROV_v0_R2018b_CALL_EVENT;
rtb_WhiteNoise_idx_2 = std::cos(sim_ROV_v0_R2018b_B.Pose[5]);
rtb_T200TransferFunction2 = std::sin(sim_ROV_v0_R2018b_B.Pose[5]);
rtb_T200TransferFunction1 = std::sin(sim_ROV_v0_R2018b_B.Pose[4]);
rtb_kxi = std::tan(sim_ROV_v0_R2018b_B.Pose[4]);
rtb_T200TransferFunction1_0[0] = rtb_WhiteNoise_idx_2 * rtb_WhiteNoise_idx_1;
rtb_T200TransferFunction1_0[6] = rtb_WhiteNoise_idx_2 * rtb_T200TransferFunction1 * rtb_jxi_tmp + -rtb_T200TransferFunction2 * rtb_WhiteNoise_idx_0;
F_g_tmp = rtb_WhiteNoise_idx_2 * rtb_WhiteNoise_idx_0;
rtb_T200TransferFunction1_0[12] = F_g_tmp * rtb_T200TransferFunction1 + rtb_T200TransferFunction2 * rtb_jxi_tmp;
rtb_T200TransferFunction1_0[1] = rtb_T200TransferFunction2 * rtb_WhiteNoise_idx_1;
rtb_T200TransferFunction1_0[7] = rtb_jxi_tmp * rtb_T200TransferFunction1 * rtb_T200TransferFunction2 + F_g_tmp;
rtb_T200TransferFunction1_0[13] = rtb_T200TransferFunction1 * rtb_T200TransferFunction2 * rtb_WhiteNoise_idx_0 + -rtb_WhiteNoise_idx_2 * rtb_jxi_tmp;
rtb_T200TransferFunction1_0[2] = -rtb_T200TransferFunction1;
rtb_T200TransferFunction1_0[8] = rtb_WhiteNoise_idx_1 * rtb_jxi_tmp;
rtb_T200TransferFunction1_0[14] = rtb_WhiteNoise_idx_1 * rtb_WhiteNoise_idx_0;
for (i_0 = 0; i_0 < 3; i_0++) {
    i = (i_0 + 3) * 6;
    rtb_T200TransferFunction1_0[i] = 0.0;
    rtb_T200TransferFunction1_0[6 * i_0 + 3] = 0.0;
    rtb_T200TransferFunction1_0[i + 1] = 0.0;
    rtb_T200TransferFunction1_0[6 * i_0 + 4] = 0.0;
    rtb_T200TransferFunction1_0[i + 2] = 0.0;
    rtb_T200TransferFunction1_0[6 * i_0 + 5] = 0.0;
}
rtb_T200TransferFunction1_0[21] = 1.0;
rtb_T200TransferFunction1_0[27] = rtb_jxi_tmp * rtb_kxi;
rtb_T200TransferFunction1_0[33] = rtb_WhiteNoise_idx_0 * rtb_kxi;
rtb_T200TransferFunction1_0[22] = 0.0;
rtb_T200TransferFunction1_0[28] = rtb_WhiteNoise_idx_0;
rtb_T200TransferFunction1_0[34] = -rtb_jxi_tmp;
rtb_T200TransferFunction1_0[23] = 0.0;
rtb_T200TransferFunction1_0[29] = rtb_jxi_tmp / rtb_WhiteNoise_idx_1;
rtb_T200TransferFunction1_0[35] = rtb_WhiteNoise_idx_0 / rtb_WhiteNoise_idx_1;
for (i_0 = 0; i_0 < 6; i_0++) {
    rtb_WhiteNoise_idx_0 = 0.0;
    for (i = 0; i < 6; i++) {
        rtb_WhiteNoise_idx_0 += rtb_T200TransferFunction1_0[6 * i + i_0] * sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[i];
    }
    sim_ROV_v0_R2018b_B.eta_dot[i_0] = rtb_WhiteNoise_idx_0;
}
/* {S!d740}Derivative: '<S19>/Derivative' */
rtb_T200TransferFunction1 = sim_ROV_v0_R2018b_M->Timing.t[0];
if ((sim_ROV_v0_R2018b_DW.TimeStampA >= rtb_T200TransferFunction1) && (sim_ROV_v0_R2018b_DW.TimeStampB >= rtb_T200TransferFunction1)) {
    /* {S!d736}Derivative: '<S19>/Derivative' */
    for (i = 0; i < 6; i++) {
        sim_ROV_v0_R2018b_B.Acceleration[i] = 0.0;
    }
} else {
    rtb_T200TransferFunction2 = sim_ROV_v0_R2018b_DW.TimeStampA;
    lastU = &sim_ROV_v0_R2018b_DW.LastUAtTimeA;
    if (sim_ROV_v0_R2018b_DW.TimeStampA < sim_ROV_v0_R2018b_DW.TimeStampB) {
        if (sim_ROV_v0_R2018b_DW.TimeStampB < rtb_T200TransferFunction1) {
            rtb_T200TransferFunction2 = sim_ROV_v0_R2018b_DW.TimeStampB;
            lastU = &sim_ROV_v0_R2018b_DW.LastUAtTimeB;
        }
    } else if (sim_ROV_v0_R2018b_DW.TimeStampA >= rtb_T200TransferFunction1) {
        rtb_T200TransferFunction2 = sim_ROV_v0_R2018b_DW.TimeStampB;
        lastU = &sim_ROV_v0_R2018b_DW.LastUAtTimeB;
    }
    rtb_T200TransferFunction1 -= rtb_T200TransferFunction2;
    /* {S!d738}Derivative: '<S19>/Derivative' */
    for (i = 0; i < 6; i++) {
        sim_ROV_v0_R2018b_B.Acceleration[i] = (sim_ROV_v0_R2018b_B.eta_dot[i] - (*lastU)[i]) / rtb_T200TransferFunction1;
    }
}
/* {E!d740}End of Derivative: '<S19>/Derivative' */
if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M) &&
sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[1] == 0) {
}
/* {S!d746}Saturate: '<S7>/Saturation' */
rtb_T200TransferFunction1 = sim_ROV_v0_R2018b_P.force[0] * 9.8;
rtb_T200TransferFunction2 = sim_ROV_v0_R2018b_P.force[200] * 9.8;
/* {S!d748}SignalConversion generated from: '<S1>/Gain2' */
tmp_7[0] = sim_ROV_v0_R2018b_B.Integrator;
tmp_7[1] = sim_ROV_v0_R2018b_B.Integrator1;
tmp_7[2] = sim_ROV_v0_R2018b_B.Integrator2;
tmp_7[3] = sim_ROV_v0_R2018b_B.LowpassFilter3.LowpassFilter3;
tmp_7[4] = sim_ROV_v0_R2018b_B.LowpassFilter4.LowpassFilter3;
tmp_7[5] = sim_ROV_v0_R2018b_B.LowpassFilter5.LowpassFilter3;
tmp_7[6] = sim_ROV_v0_R2018b_B.Integrator6;
tmp_7[7] = sim_ROV_v0_R2018b_B.Integrator7;
tmp_7[8] = sim_ROV_v0_R2018b_B.Integrator8;
tmp_7[9] = sim_ROV_v0_R2018b_B.Integrator3;
tmp_7[10] = sim_ROV_v0_R2018b_B.Integrator4;
tmp_7[11] = sim_ROV_v0_R2018b_B.Integrator5;
for (i_0 = 0; i_0 < 6; i_0++) {
    /* {S!d750}Sum: '<S1>/Sum2' incorporates:
 *  Gain: '<S1>/Gain1'
 *  Integrator: '<S1>/Integrator'
 */
    rtb_jxi = 0.0;
    for (i = 0; i < 6; i++) {
        rtb_jxi += sim_ROV_v0_R2018b_P.Kq[6 * i + i_0] * sim_ROV_v0_R2018b_X.Integrator_CSTATE_i[i];
    }
    /* {S!d752}Gain: '<S1>/Gain2' */
    rtb_WhiteNoise_idx_2 = 0.0;
    for (i = 0; i < 12; i++) {
        rtb_WhiteNoise_idx_2 += sim_ROV_v0_R2018b_P.Kx[6 * i + i_0] * tmp_7[i];
    }
    /* {S!d754}Sum: '<S1>/Sum2' incorporates:
 *  Gain: '<S1>/Gain2'
 */
    a[i_0] = (0.0 - rtb_jxi) - rtb_WhiteNoise_idx_2;
}
for (i = 0; i < 8; i++) {
    /* {S!d756}Gain: '<S7>/Control Allocation' */
    rtb_jxi = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
        rtb_jxi += sim_ROV_v0_R2018b_P.ControlAllocation_Gain[(i_0 << 3) + i] * a[i_0];
    }
    /* {S!d758}Saturate: '<S7>/Saturation' incorporates:
 *  Gain: '<S7>/Control Allocation'
 */
    if (rtb_jxi > rtb_T200TransferFunction2) {
        rtb_jxi = rtb_T200TransferFunction2;
    } else if (rtb_jxi < rtb_T200TransferFunction1) {
        rtb_jxi = rtb_T200TransferFunction1;
    }
    /* {S!d760}Lookup_n-D: '<S7>/1-D Lookup Table' incorporates:
 *  Gain: '<S7>/N → kgf'
 *  Saturate: '<S7>/Saturation'
 */
    rtb_uDLookupTable[i] = look1_binlxpw(sim_ROV_v0_R2018b_P.Nkgf_Gain * rtb_jxi, sim_ROV_v0_R2018b_P.force, sim_ROV_v0_R2018b_P.pwm, 200U);
}
if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M) &&
sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[1] == 0) {
    for (i = 0; i < 6; i++) {
        /* {S!d762}Gain: '<S4>/Gain' incorporates:
 *  Constant: '<S4>/Constant Reference'
 */
        sim_ROV_v0_R2018b_B.Gain[i] = sim_ROV_v0_R2018b_P.Gain_Gain[i] * sim_ROV_v0_R2018b_P.ConstantReference_Value[i];
    }
    /* {S!d764}Gain: '<S4>/Gain1' incorporates:
 *  Constant: '<S4>/Constant'
 */
    sim_ROV_v0_R2018b_B.Gain1 = sim_ROV_v0_R2018b_P.Gain1_Gain * sim_ROV_v0_R2018b_P.Constant_Value_c;
    /* {S!d766}Gain: '<S4>/Gain2' incorporates:
 *  Constant: '<S4>/Constant'
 */
    sim_ROV_v0_R2018b_B.Gain2 = sim_ROV_v0_R2018b_P.Gain2_Gain * sim_ROV_v0_R2018b_P.Constant_Value_c;
}
/* {S!d776}ManualSwitch: '<S4>/Manual Switch' incorporates:
 *  Gain: '<S4>/Gain3'
 *  Step: '<S4>/Step2'
 *  Step: '<S4>/Step3'
 *  Sum: '<S4>/Sum1'
 */
if (sim_ROV_v0_R2018b_P.ManualSwitch_CurrentSetting == 1) {
    for (i = 0; i < 6; i++) {
        a[i] = sim_ROV_v0_R2018b_B.Gain[i];
    }
} else {
    /* {S!d768}Step: '<S4>/Step' incorporates:
 *  Step: '<S4>/Step1'
 *  Step: '<S4>/Step2'
 *  Step: '<S4>/Step3'
 */
    rtb_jxi = sim_ROV_v0_R2018b_M->Timing.t[0];
    if (rtb_jxi < sim_ROV_v0_R2018b_P.Step_Time) {
        rtb_WhiteNoise_idx_2 = sim_ROV_v0_R2018b_P.Step_Y0;
    } else {
        rtb_WhiteNoise_idx_2 = sim_ROV_v0_R2018b_P.Step_YFinal;
    }
    /* {S!d770}Step: '<S4>/Step1' */
    if (rtb_jxi < sim_ROV_v0_R2018b_P.Step1_Time) {
        rtb_T200TransferFunction2 = sim_ROV_v0_R2018b_P.Step1_Y0;
    } else {
        rtb_T200TransferFunction2 = sim_ROV_v0_R2018b_P.Step1_YFinal;
    }
    /* {S!d772}Sum: '<S4>/Sum' incorporates:
 *  Step: '<S4>/Step'
 *  Step: '<S4>/Step1'
 */
    rtb_T200TransferFunction1 = rtb_WhiteNoise_idx_2 - rtb_T200TransferFunction2;
    a[0] = rtb_T200TransferFunction1;
    a[1] = rtb_T200TransferFunction1;
    a[2] = rtb_T200TransferFunction1;
    a[3] = sim_ROV_v0_R2018b_B.Gain1;
    a[4] = sim_ROV_v0_R2018b_B.Gain2;
    /* {S!d774}Gain: '<S4>/Gain3' incorporates:
 *  Step: '<S4>/Step2'
 *  Step: '<S4>/Step3'
 */
    if (rtb_jxi < sim_ROV_v0_R2018b_P.Step2_Time) {
        rtb_WhiteNoise_idx_2 = sim_ROV_v0_R2018b_P.Step2_Y0;
    } else {
        rtb_WhiteNoise_idx_2 = sim_ROV_v0_R2018b_P.Step2_YFinal;
    }
    if (rtb_jxi < sim_ROV_v0_R2018b_P.Step3_Time) {
        rtb_jxi = sim_ROV_v0_R2018b_P.Step3_Y0;
    } else {
        rtb_jxi = sim_ROV_v0_R2018b_P.Step3_YFinal;
    }
    a[5] = (rtb_WhiteNoise_idx_2 - rtb_jxi) * sim_ROV_v0_R2018b_P.Gain3_Gain;
}
/* {E!d776}End of ManualSwitch: '<S4>/Manual Switch' */

/* {S!d778}SignalConversion generated from: '<S1>/Integrator' incorporates:
 *  Sum: '<S8>/Sum'
 *  Sum: '<S8>/Sum1'
 *  Sum: '<S8>/Sum2'
 *  Sum: '<S8>/Sum3'
 *  Sum: '<S8>/Sum4'
 *  Sum: '<S8>/Sum6'
 */
sim_ROV_v0_R2018b_B.TmpSignalConversionAtIntegrator[0] = a[0] - sim_ROV_v0_R2018b_B.Integrator6;
sim_ROV_v0_R2018b_B.TmpSignalConversionAtIntegrator[1] = a[1] - sim_ROV_v0_R2018b_B.Integrator7;
sim_ROV_v0_R2018b_B.TmpSignalConversionAtIntegrator[2] = a[2] - sim_ROV_v0_R2018b_B.Integrator8;
sim_ROV_v0_R2018b_B.TmpSignalConversionAtIntegrator[3] = a[3] - sim_ROV_v0_R2018b_B.Integrator3;
sim_ROV_v0_R2018b_B.TmpSignalConversionAtIntegrator[4] = a[4] - sim_ROV_v0_R2018b_B.Integrator4;
sim_ROV_v0_R2018b_B.TmpSignalConversionAtIntegrator[5] = a[5] - sim_ROV_v0_R2018b_B.Integrator5;
/* {S!d790}MATLAB Function: '<S16>/Normalization' incorporates:
 *  Saturate: '<S16>/Saturation'
 */
sim_ROV_v0_R2018b_DW.sfEvent_c = sim_ROV_v0_R2018b_CALL_EVENT;
for (i = 0; i < 8; i++) {
    /* {S!d780}Saturate: '<S16>/Saturation' */
    rtb_WhiteNoise_idx_0 = rtb_uDLookupTable[i];
    if (rtb_WhiteNoise_idx_0 > sim_ROV_v0_R2018b_P.Saturation_UpperSat_f) {
        rtb_WhiteNoise_idx_0 = sim_ROV_v0_R2018b_P.Saturation_UpperSat_f;
    } else if (rtb_WhiteNoise_idx_0 < sim_ROV_v0_R2018b_P.Saturation_LowerSat_p) {
        rtb_WhiteNoise_idx_0 = sim_ROV_v0_R2018b_P.Saturation_LowerSat_p;
    }
    rtb_WhiteNoise_idx_0 = (rtb_WhiteNoise_idx_0 - 1500.0) * 150.0 / 400.0;
    rtb_uDLookupTable[i] = rtb_WhiteNoise_idx_0;
    /* {S!d788}DeadZone: '<S16>/Dead Zone' incorporates:
 *  Saturate: '<S16>/Saturation'
 */
    if (rtb_WhiteNoise_idx_0 > sim_ROV_v0_R2018b_P.DeadZone_End) {
        /* {S!d782}DeadZone: '<S16>/Dead Zone' */
        sim_ROV_v0_R2018b_B.DeadZone[i] = rtb_WhiteNoise_idx_0 - sim_ROV_v0_R2018b_P.DeadZone_End;
    } else if (rtb_WhiteNoise_idx_0 >= sim_ROV_v0_R2018b_P.DeadZone_Start) {
        /* {S!d784}DeadZone: '<S16>/Dead Zone' */
        sim_ROV_v0_R2018b_B.DeadZone[i] = 0.0;
    } else {
        /* {S!d786}DeadZone: '<S16>/Dead Zone' */
        sim_ROV_v0_R2018b_B.DeadZone[i] = rtb_WhiteNoise_idx_0 - sim_ROV_v0_R2018b_P.DeadZone_Start;
    }
    /* {E!d788}End of DeadZone: '<S16>/Dead Zone' */
}
/* {E!d790}End of MATLAB Function: '<S16>/Normalization' */
if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M) &&
sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[1] == 0) {
    /* {S!d800}Gain: '<S34>/Zero-Order Hold2' incorporates:
 *  Constant: '<S17>/Gravity Acceleration'
 */
    sim_ROV_v0_R2018b_B.ZeroOrderHold2[0] = sim_ROV_v0_R2018b_P.ZeroOrderHold2_Gain * sim_ROV_v0_R2018b_P.GravityAcceleration_Value[0];
    sim_ROV_v0_R2018b_B.ZeroOrderHold2[1] = sim_ROV_v0_R2018b_P.ZeroOrderHold2_Gain * sim_ROV_v0_R2018b_P.GravityAcceleration_Value[1];
    sim_ROV_v0_R2018b_B.ZeroOrderHold2[2] = sim_ROV_v0_R2018b_P.ZeroOrderHold2_Gain * sim_ROV_v0_R2018b_P.GravityAcceleration_Value[2];
    /* {S!d802}Gain: '<S34>/Gain' incorporates:
 *  Constant: '<S17>/CoG'
 *  Constant: '<S34>/wl_ins'
 *  Gain: '<S34>/Zero-Order Hold4'
 *  Sum: '<S34>/Sum7'
 */
    sim_ROV_v0_R2018b_B.Gain_n[0] = (sim_ROV_v0_R2018b_P.ZeroOrderHold4_Gain * sim_ROV_v0_R2018b_P.r_g[0] - sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_g[0]) * sim_ROV_v0_R2018b_P.Gain_Gain_f[0];
    sim_ROV_v0_R2018b_B.Gain_n[1] = (sim_ROV_v0_R2018b_P.ZeroOrderHold4_Gain * sim_ROV_v0_R2018b_P.r_g[1] - sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_g[1]) * sim_ROV_v0_R2018b_P.Gain_Gain_f[1];
    sim_ROV_v0_R2018b_B.Gain_n[2] = (sim_ROV_v0_R2018b_P.ZeroOrderHold4_Gain * sim_ROV_v0_R2018b_P.r_g[2] - sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_g[2]) * sim_ROV_v0_R2018b_P.Gain_Gain_f[2];
}
/* {S!d804}Gain: '<S34>/Zero-Order Hold' incorporates:
 *  Integrator: '<S18>/Integrator'
 */
rtb_WhiteNoise_idx_0 = sim_ROV_v0_R2018b_P.ZeroOrderHold_Gain_a * sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[3];
rtb_WhiteNoise_idx_1 = sim_ROV_v0_R2018b_P.ZeroOrderHold_Gain_a * sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[4];
rtb_WhiteNoise_idx_2 = sim_ROV_v0_R2018b_P.ZeroOrderHold_Gain_a * sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[5];
/* {S!d806}Sum: '<S43>/Sum' incorporates:
 *  Product: '<S46>/i x j'
 *  Product: '<S46>/j x k'
 *  Product: '<S46>/k x i'
 *  Product: '<S47>/i x k'
 *  Product: '<S47>/j x i'
 *  Product: '<S47>/k x j'
 */
rtb_Sum4_j[0] = rtb_WhiteNoise_idx_1 * sim_ROV_v0_R2018b_B.Gain_n[2] - sim_ROV_v0_R2018b_B.Gain_n[1] * rtb_WhiteNoise_idx_2;
rtb_Sum4_j[1] = sim_ROV_v0_R2018b_B.Gain_n[0] * rtb_WhiteNoise_idx_2 - rtb_WhiteNoise_idx_0 * sim_ROV_v0_R2018b_B.Gain_n[2];
rtb_Sum4_j[2] = rtb_WhiteNoise_idx_0 * sim_ROV_v0_R2018b_B.Gain_n[1] - sim_ROV_v0_R2018b_B.Gain_n[0] * rtb_WhiteNoise_idx_1;
/* {S!d808}Sum: '<S42>/Sum' incorporates:
 *  Product: '<S44>/i x j'
 *  Product: '<S44>/j x k'
 *  Product: '<S44>/k x i'
 *  Product: '<S45>/i x k'
 *  Product: '<S45>/j x i'
 *  Product: '<S45>/k x j'
 */
rtb_jxi = rtb_WhiteNoise_idx_1 * rtb_Sum4_j[2] - rtb_Sum4_j[1] * rtb_WhiteNoise_idx_2;
rtb_T200TransferFunction1 = rtb_Sum4_j[0] * rtb_WhiteNoise_idx_2 - rtb_WhiteNoise_idx_0 * rtb_Sum4_j[2];
rtb_T200TransferFunction2 = rtb_WhiteNoise_idx_0 * rtb_Sum4_j[1] - rtb_Sum4_j[0] * rtb_WhiteNoise_idx_1;
/* {S!d810}Gain: '<S34>/Zero-Order Hold3' */
rtb_WhiteNoise_idx_0 = sim_ROV_v0_R2018b_P.ZeroOrderHold3_Gain * sim_ROV_v0_R2018b_B.BodyAcceleration[3];
rtb_WhiteNoise_idx_1 = sim_ROV_v0_R2018b_P.ZeroOrderHold3_Gain * sim_ROV_v0_R2018b_B.BodyAcceleration[4];
rtb_WhiteNoise_idx_2 = sim_ROV_v0_R2018b_P.ZeroOrderHold3_Gain * sim_ROV_v0_R2018b_B.BodyAcceleration[5];
/* {S!d812}Sum: '<S34>/Sum' incorporates:
 *  Gain: '<S34>/Zero-Order Hold1'
 *  Product: '<S48>/i x j'
 *  Product: '<S48>/j x k'
 *  Product: '<S48>/k x i'
 *  Product: '<S49>/i x k'
 *  Product: '<S49>/j x i'
 *  Product: '<S49>/k x j'
 *  Sum: '<S39>/Sum'
 */
rtb_jxi = ((sim_ROV_v0_R2018b_P.ZeroOrderHold1_Gain_m * sim_ROV_v0_R2018b_B.BodyAcceleration[0] - sim_ROV_v0_R2018b_B.ZeroOrderHold2[0]) + rtb_jxi) + (rtb_WhiteNoise_idx_1 * sim_ROV_v0_R2018b_B.Gain_n[2] - sim_ROV_v0_R2018b_B.Gain_n[1] * rtb_WhiteNoise_idx_2);
rtb_WhiteNoise_idx_2 = ((sim_ROV_v0_R2018b_P.ZeroOrderHold1_Gain_m * sim_ROV_v0_R2018b_B.BodyAcceleration[1] - sim_ROV_v0_R2018b_B.ZeroOrderHold2[1]) + rtb_T200TransferFunction1) + (sim_ROV_v0_R2018b_B.Gain_n[0] * rtb_WhiteNoise_idx_2 - rtb_WhiteNoise_idx_0 * sim_ROV_v0_R2018b_B.Gain_n[2]);
rtb_WhiteNoise_idx_0 = ((sim_ROV_v0_R2018b_P.ZeroOrderHold1_Gain_m * sim_ROV_v0_R2018b_B.BodyAcceleration[2] - sim_ROV_v0_R2018b_B.ZeroOrderHold2[2]) + rtb_T200TransferFunction2) + (rtb_WhiteNoise_idx_0 * sim_ROV_v0_R2018b_B.Gain_n[1] - sim_ROV_v0_R2018b_B.Gain_n[0] * rtb_WhiteNoise_idx_1);
/* {S!d814}Sum: '<S34>/Sum4' incorporates:
 *  Constant: '<S34>/Measurement bias'
 *  Constant: '<S34>/Scale factors & Cross-coupling  errors'
 *  Product: '<S34>/Product'
 */
for (i_0 = 0; i_0 < 3; i_0++) {
    rtb_Sum4_j[i_0] = ((sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_l[i_0 + 3] * rtb_WhiteNoise_idx_2 + sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_l[i_0] * rtb_jxi) + sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_l[i_0 + 6] * rtb_WhiteNoise_idx_0) + sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementUni[i_0];
}
/* {E!d814}End of Sum: '<S34>/Sum4' */
if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M) &&
sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[2] == 0) {
    /* {S!d816}Sqrt: '<S37>/Sqrt1' incorporates:
 *  Constant: '<S37>/Constant1'
 */
    rtb_T200TransferFunction1 = std::sqrt(sim_ROV_v0_R2018b_P.Randombias_Ts_e);
    /* {S!d818}Product: '<S37>/Product' incorporates:
 *  Constant: '<S37>/Constant'
 *  Product: '<S37>/Divide'
 *  RandomNumber: '<S37>/White Noise'
 *  Sqrt: '<S37>/Sqrt'
 */
    sim_ROV_v0_R2018b_B.Product_i[0] = std::sqrt(sim_ROV_v0_R2018b_P.ThreeaxisAccelerometer_a_pow[0]) / rtb_T200TransferFunction1 * sim_ROV_v0_R2018b_DW.NextOutput_p[0];
    sim_ROV_v0_R2018b_B.Product_i[1] = std::sqrt(sim_ROV_v0_R2018b_P.ThreeaxisAccelerometer_a_pow[1]) / rtb_T200TransferFunction1 * sim_ROV_v0_R2018b_DW.NextOutput_p[1];
    sim_ROV_v0_R2018b_B.Product_i[2] = std::sqrt(sim_ROV_v0_R2018b_P.ThreeaxisAccelerometer_a_pow[2]) / rtb_T200TransferFunction1 * sim_ROV_v0_R2018b_DW.NextOutput_p[2];
}
/* {S!d820}Switch: '<S36>/Switch' incorporates:
 *  Constant: '<S36>/Constant'
 *  SecondOrderIntegrator: '<S41>/Integrator, Second-Order Limited'
 */
if (sim_ROV_v0_R2018b_P.Constant_Value_b >= sim_ROV_v0_R2018b_P.Switch_Threshold_j) {
    rtb_jxi = sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[0];
} else {
    rtb_jxi = rtb_Sum4_j[0];
}
/* {S!d822}Sum: '<S34>/Sum1' incorporates:
 *  Switch: '<S36>/Switch'
 */
rtb_WhiteNoise_idx_0 = rtb_jxi + sim_ROV_v0_R2018b_B.Product_i[0];
/* {S!d830}Saturate: '<S34>/Saturation' */
if (rtb_WhiteNoise_idx_0 > sim_ROV_v0_R2018b_P.Saturation_UpperSat_e[0]) {
    /* {S!d824}Saturate: '<S34>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation_m[0] = sim_ROV_v0_R2018b_P.Saturation_UpperSat_e[0];
} else if (rtb_WhiteNoise_idx_0 < sim_ROV_v0_R2018b_P.Saturation_LowerSat_a[0]) {
    /* {S!d826}Saturate: '<S34>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation_m[0] = sim_ROV_v0_R2018b_P.Saturation_LowerSat_a[0];
} else {
    /* {S!d828}Saturate: '<S34>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation_m[0] = rtb_WhiteNoise_idx_0;
}
/* {S!d832}Switch: '<S36>/Switch' incorporates:
 *  Constant: '<S36>/Constant'
 *  SecondOrderIntegrator: '<S41>/Integrator, Second-Order Limited'
 */
if (sim_ROV_v0_R2018b_P.Constant_Value_b >= sim_ROV_v0_R2018b_P.Switch_Threshold_j) {
    rtb_jxi = sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[1];
} else {
    rtb_jxi = rtb_Sum4_j[1];
}
/* {S!d834}Sum: '<S34>/Sum1' incorporates:
 *  Switch: '<S36>/Switch'
 */
rtb_WhiteNoise_idx_0 = rtb_jxi + sim_ROV_v0_R2018b_B.Product_i[1];
/* {S!d842}Saturate: '<S34>/Saturation' */
if (rtb_WhiteNoise_idx_0 > sim_ROV_v0_R2018b_P.Saturation_UpperSat_e[1]) {
    /* {S!d836}Saturate: '<S34>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation_m[1] = sim_ROV_v0_R2018b_P.Saturation_UpperSat_e[1];
} else if (rtb_WhiteNoise_idx_0 < sim_ROV_v0_R2018b_P.Saturation_LowerSat_a[1]) {
    /* {S!d838}Saturate: '<S34>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation_m[1] = sim_ROV_v0_R2018b_P.Saturation_LowerSat_a[1];
} else {
    /* {S!d840}Saturate: '<S34>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation_m[1] = rtb_WhiteNoise_idx_0;
}
/* {S!d844}Switch: '<S36>/Switch' incorporates:
 *  Constant: '<S36>/Constant'
 *  SecondOrderIntegrator: '<S41>/Integrator, Second-Order Limited'
 */
if (sim_ROV_v0_R2018b_P.Constant_Value_b >= sim_ROV_v0_R2018b_P.Switch_Threshold_j) {
    rtb_jxi = sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[2];
} else {
    rtb_jxi = rtb_Sum4_j[2];
}
/* {S!d846}Sum: '<S34>/Sum1' incorporates:
 *  Switch: '<S36>/Switch'
 */
rtb_WhiteNoise_idx_0 = rtb_jxi + sim_ROV_v0_R2018b_B.Product_i[2];
/* {S!d854}Saturate: '<S34>/Saturation' */
if (rtb_WhiteNoise_idx_0 > sim_ROV_v0_R2018b_P.Saturation_UpperSat_e[2]) {
    /* {S!d848}Saturate: '<S34>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation_m[2] = sim_ROV_v0_R2018b_P.Saturation_UpperSat_e[2];
} else if (rtb_WhiteNoise_idx_0 < sim_ROV_v0_R2018b_P.Saturation_LowerSat_a[2]) {
    /* {S!d850}Saturate: '<S34>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation_m[2] = sim_ROV_v0_R2018b_P.Saturation_LowerSat_a[2];
} else {
    /* {S!d852}Saturate: '<S34>/Saturation' */
    sim_ROV_v0_R2018b_B.Saturation_m[2] = rtb_WhiteNoise_idx_0;
}
if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M) &&
sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[1] == 0) {

        sim_ROV_v0_R2018b_LowpassFilter(sim_ROV_v0_R2018b_B.Saturation_m[0], &sim_ROV_v0_R2018b_B.LowpassFilter, &sim_ROV_v0_R2018b_DW.LowpassFilter);

        sim_ROV_v0_R2018b_LowpassFilter(sim_ROV_v0_R2018b_B.Saturation_m[1], &sim_ROV_v0_R2018b_B.LowpassFilter1, &sim_ROV_v0_R2018b_DW.LowpassFilter1);

        sim_ROV_v0_R2018b_LowpassFilter(sim_ROV_v0_R2018b_B.Saturation_m[2], &sim_ROV_v0_R2018b_B.LowpassFilter2, &sim_ROV_v0_R2018b_DW.LowpassFilter2);
}
/* {S!d856}Gain: '<S41>/2*zeta * wn' */
rtb_T200TransferFunction1 = 2.0 * sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurement_gc * sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_f;
/* {S!d858}Gain: '<S41>/wn^2' */
rtb_T200TransferFunction2 = sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_f * sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_f;
/* {S!d860}Sum: '<S41>/Sum2' incorporates:
 *  Gain: '<S41>/2*zeta * wn'
 *  Gain: '<S41>/wn^2'
 *  SecondOrderIntegrator: '<S41>/Integrator, Second-Order Limited'
 *  Sum: '<S41>/Sum3'
 */
sim_ROV_v0_R2018b_B.Sum2[0] = (rtb_Sum4_j[0] - sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[0]) * rtb_T200TransferFunction2 - rtb_T200TransferFunction1 * sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[3];
sim_ROV_v0_R2018b_B.Sum2[1] = (rtb_Sum4_j[1] - sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[1]) * rtb_T200TransferFunction2 - rtb_T200TransferFunction1 * sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[4];
sim_ROV_v0_R2018b_B.Sum2[2] = (rtb_Sum4_j[2] - sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[2]) * rtb_T200TransferFunction2 - rtb_T200TransferFunction1 * sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[5];
/* {S!d862}Gain: '<S53>/2*zeta * wn' */
rtb_T200TransferFunction1 = 2.0 * sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_o * sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_h;
/* {S!d864}Gain: '<S53>/wn^2' */
rtb_T200TransferFunction2 = sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_h * sim_ROV_v0_R2018b_P.ThreeaxisInertialMeasurementU_h;
/* {S!d866}Sum: '<S53>/Sum2' incorporates:
 *  Gain: '<S53>/2*zeta * wn'
 *  Gain: '<S53>/wn^2'
 *  SecondOrderIntegrator: '<S53>/Integrator, Second-Order Limited'
 *  Sum: '<S53>/Sum3'
 */
sim_ROV_v0_R2018b_B.Sum2_c[0] = (rtb_Sum4[0] - sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[0]) * rtb_T200TransferFunction2 - rtb_T200TransferFunction1 * sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[3];
sim_ROV_v0_R2018b_B.Sum2_c[1] = (rtb_Sum4[1] - sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[1]) * rtb_T200TransferFunction2 - rtb_T200TransferFunction1 * sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[4];
sim_ROV_v0_R2018b_B.Sum2_c[2] = (rtb_Sum4[2] - sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[2]) * rtb_T200TransferFunction2 - rtb_T200TransferFunction1 * sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[5];






            }
        



                
                    if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M)) {
                        /* Matfile logging */
            
    rt_UpdateTXYLogVars(sim_ROV_v0_R2018b_M->rtwLogInfo, (sim_ROV_v0_R2018b_M->Timing.t));

                } /* end MajorTimeStep */




                    if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M)) {
                        




                            
real_T (*lastU)[6];
int32_T i;

                                    
                                    if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M) &&
sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[2] == 0) {
    /* {S!d868}Update for RandomNumber: '<S51>/White Noise' */
    sim_ROV_v0_R2018b_DW.NextOutput[0] = rt_nrand_Upu32_Yd_f_pw_snf(&sim_ROV_v0_R2018b_DW.RandSeed[0]) * sim_ROV_v0_R2018b_P.WhiteNoise_StdDev + sim_ROV_v0_R2018b_P.WhiteNoise_Mean;
    sim_ROV_v0_R2018b_DW.NextOutput[1] = rt_nrand_Upu32_Yd_f_pw_snf(&sim_ROV_v0_R2018b_DW.RandSeed[1]) * sim_ROV_v0_R2018b_P.WhiteNoise_StdDev + sim_ROV_v0_R2018b_P.WhiteNoise_Mean;
    sim_ROV_v0_R2018b_DW.NextOutput[2] = rt_nrand_Upu32_Yd_f_pw_snf(&sim_ROV_v0_R2018b_DW.RandSeed[2]) * sim_ROV_v0_R2018b_P.WhiteNoise_StdDev + sim_ROV_v0_R2018b_P.WhiteNoise_Mean;
}
/* {S!d870}Update for Derivative: '<S19>/Derivative' */
if (sim_ROV_v0_R2018b_DW.TimeStampA == (rtInf)) {
    sim_ROV_v0_R2018b_DW.TimeStampA = sim_ROV_v0_R2018b_M->Timing.t[0];
    lastU = &sim_ROV_v0_R2018b_DW.LastUAtTimeA;
} else if (sim_ROV_v0_R2018b_DW.TimeStampB == (rtInf)) {
    sim_ROV_v0_R2018b_DW.TimeStampB = sim_ROV_v0_R2018b_M->Timing.t[0];
    lastU = &sim_ROV_v0_R2018b_DW.LastUAtTimeB;
} else if (sim_ROV_v0_R2018b_DW.TimeStampA < sim_ROV_v0_R2018b_DW.TimeStampB) {
    sim_ROV_v0_R2018b_DW.TimeStampA = sim_ROV_v0_R2018b_M->Timing.t[0];
    lastU = &sim_ROV_v0_R2018b_DW.LastUAtTimeA;
} else {
    sim_ROV_v0_R2018b_DW.TimeStampB = sim_ROV_v0_R2018b_M->Timing.t[0];
    lastU = &sim_ROV_v0_R2018b_DW.LastUAtTimeB;
}
for (i = 0; i < 6; i++) {
    (*lastU)[i] = sim_ROV_v0_R2018b_B.eta_dot[i];
}
/* {E!d870}End of Update for Derivative: '<S19>/Derivative' */
if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M) &&
sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[2] == 0) {
    /* {S!d872}Update for RandomNumber: '<S37>/White Noise' */
    sim_ROV_v0_R2018b_DW.NextOutput_p[0] = rt_nrand_Upu32_Yd_f_pw_snf(&sim_ROV_v0_R2018b_DW.RandSeed_l[0]) * sim_ROV_v0_R2018b_P.WhiteNoise_StdDev_j + sim_ROV_v0_R2018b_P.WhiteNoise_Mean_g;
    sim_ROV_v0_R2018b_DW.NextOutput_p[1] = rt_nrand_Upu32_Yd_f_pw_snf(&sim_ROV_v0_R2018b_DW.RandSeed_l[1]) * sim_ROV_v0_R2018b_P.WhiteNoise_StdDev_j + sim_ROV_v0_R2018b_P.WhiteNoise_Mean_g;
    sim_ROV_v0_R2018b_DW.NextOutput_p[2] = rt_nrand_Upu32_Yd_f_pw_snf(&sim_ROV_v0_R2018b_DW.RandSeed_l[2]) * sim_ROV_v0_R2018b_P.WhiteNoise_StdDev_j + sim_ROV_v0_R2018b_P.WhiteNoise_Mean_g;
}





                




                            
                /* External mode */
                rtExtModeUploadCheckTrigger(3);


                    { /* Sample time: [0.0s, 0.0s] */


                    rtExtModeUpload(0, (real_T)sim_ROV_v0_R2018b_M->Timing.t[0]);

                }

                    if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M) &&
sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[1] == 0) { /* Sample time: [0.01s, 0.0s] */


                    rtExtModeUpload(1, (real_T)(((sim_ROV_v0_R2018b_M->Timing.clockTick1+sim_ROV_v0_R2018b_M->Timing.clockTickH1* 4294967296.0))  * 0.01));

                }

                    if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M) &&
sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[2] == 0) { /* Sample time: [0.1s, 0.0s] */


                    rtExtModeUpload(2, (real_T)(((sim_ROV_v0_R2018b_M->Timing.clockTick2+sim_ROV_v0_R2018b_M->Timing.clockTickH2* 4294967296.0))  * 0.1));

                }

            } /* end MajorTimeStep */

                    

        if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M)) {


        
            /* signal main to stop simulation */
            { /* Sample time: [0.0s, 0.0s] */
            if ( (rtmGetTFinal(sim_ROV_v0_R2018b_M)!=-1) &&
            !((rtmGetTFinal(sim_ROV_v0_R2018b_M)-(((sim_ROV_v0_R2018b_M->Timing.clockTick1+sim_ROV_v0_R2018b_M->Timing.clockTickH1* 4294967296.0))  * 0.01)) > (((sim_ROV_v0_R2018b_M->Timing.clockTick1+sim_ROV_v0_R2018b_M->Timing.clockTickH1* 4294967296.0))  * 0.01) * (DBL_EPSILON))) {
                rtmSetErrorStatus(sim_ROV_v0_R2018b_M, "Simulation finished");
            }
                if (rtmGetStopRequested(sim_ROV_v0_R2018b_M)) {
                    rtmSetErrorStatus(sim_ROV_v0_R2018b_M, "Simulation finished");
                }
            }

                rt_ertODEUpdateContinuousStates(&sim_ROV_v0_R2018b_M->solverInfo);

                        /* Update absolute time for base rate */
                        /* The "clockTick0" counts the number of times the code of this task has
        * been executed. The absolute time is the multiplication of "clockTick0"
        * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
        * overflow during the application lifespan selected.
            * Timer of this task consists of two 32 bit unsigned integers.
            * The two integers represent the low bits Timing.clockTick0 and the high bits
            * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
        */

        if(!(++sim_ROV_v0_R2018b_M->Timing.clockTick0)) {
 ++sim_ROV_v0_R2018b_M->Timing.clockTickH0; 
}  sim_ROV_v0_R2018b_M->Timing.t[0] = rtsiGetSolverStopTime(&sim_ROV_v0_R2018b_M->solverInfo);


                {
            /* Update absolute timer for sample time: [0.01s, 0.0s] */
                        /* The "clockTick1" counts the number of times the code of this task has
        * been executed. The resolution of this integer timer is 0.01, which is the step size
        * of the task. Size of "clockTick1" ensures timer will not overflow during the
        * application lifespan selected.
            * Timer of this task consists of two 32 bit unsigned integers.
            * The two integers represent the low bits Timing.clockTick1 and the high bits
            * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
        */

        sim_ROV_v0_R2018b_M->Timing.clockTick1++;
 if (!sim_ROV_v0_R2018b_M->Timing.clockTick1) {
 sim_ROV_v0_R2018b_M->Timing.clockTickH1++; 
}

        }

                if (rtmIsMajorTimeStep(sim_ROV_v0_R2018b_M) &&
sim_ROV_v0_R2018b_M->Timing.TaskCounters.TID[2] == 0) {
            /* Update absolute timer for sample time: [0.1s, 0.0s] */
                        /* The "clockTick2" counts the number of times the code of this task has
        * been executed. The resolution of this integer timer is 0.1, which is the step size
        * of the task. Size of "clockTick2" ensures timer will not overflow during the
        * application lifespan selected.
            * Timer of this task consists of two 32 bit unsigned integers.
            * The two integers represent the low bits Timing.clockTick2 and the high bits
            * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
        */

        sim_ROV_v0_R2018b_M->Timing.clockTick2++;
 if (!sim_ROV_v0_R2018b_M->Timing.clockTick2) {
 sim_ROV_v0_R2018b_M->Timing.clockTickH2++; 
}

        }

            





                    rate_scheduler();


    } /* end MajorTimeStep */


                        

            

        
        



                


        } 
        
                                    /* Derivatives for root system: '<Root>' */
                
        void sim_ROV_v0_R2018b_derivatives(void)
        {

            

            
    
XDot_sim_ROV_v0_R2018b_T *_rtXdot;
int32_T i;

    




                                
        
    




                                                
                                    _rtXdot = ((XDot_sim_ROV_v0_R2018b_T *) sim_ROV_v0_R2018b_M->derivs);
/* {S!d874}Derivatives for Integrator: '<S30>/Integrator6' */
_rtXdot->Integrator6_CSTATE = sim_ROV_v0_R2018b_B.Integrator;
/* {S!d876}Derivatives for Integrator: '<S30>/Integrator7' */
_rtXdot->Integrator7_CSTATE = sim_ROV_v0_R2018b_B.Integrator1;
/* {S!d878}Derivatives for Integrator: '<S30>/Integrator8' */
_rtXdot->Integrator8_CSTATE = sim_ROV_v0_R2018b_B.Integrator2;
/* {S!d880}Derivatives for Integrator: '<S30>/Integrator' */
_rtXdot->Integrator_CSTATE = sim_ROV_v0_R2018b_B.LowpassFilter.LowpassFilter;
/* {S!d882}Derivatives for Integrator: '<S30>/Integrator1' */
_rtXdot->Integrator1_CSTATE = sim_ROV_v0_R2018b_B.LowpassFilter1.LowpassFilter;
/* {S!d884}Derivatives for Integrator: '<S30>/Integrator2' */
_rtXdot->Integrator2_CSTATE = sim_ROV_v0_R2018b_B.LowpassFilter2.LowpassFilter;
/* {S!d886}Derivatives for Integrator: '<S30>/Integrator3' */
_rtXdot->Integrator3_CSTATE = sim_ROV_v0_R2018b_B.LowpassFilter3.LowpassFilter3;
/* {S!d888}Derivatives for Integrator: '<S30>/Integrator4' */
_rtXdot->Integrator4_CSTATE = sim_ROV_v0_R2018b_B.LowpassFilter4.LowpassFilter3;
/* {S!d890}Derivatives for Integrator: '<S30>/Integrator5' */
_rtXdot->Integrator5_CSTATE = sim_ROV_v0_R2018b_B.LowpassFilter5.LowpassFilter3;
/* {S!d892}Derivatives for SecondOrderIntegrator: '<S53>/Integrator, Second-Order Limited' */
if (sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited_MO[0] == 0) {
    _rtXdot->IntegratorSecondOrderLimited_CS[0] = sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[3];
    _rtXdot->IntegratorSecondOrderLimited_CS[3] = sim_ROV_v0_R2018b_B.Sum2_c[0];
}
if (sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited_MO[1] == 0) {
    _rtXdot->IntegratorSecondOrderLimited_CS[1] = sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[4];
    _rtXdot->IntegratorSecondOrderLimited_CS[4] = sim_ROV_v0_R2018b_B.Sum2_c[1];
}
if (sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited_MO[2] == 0) {
    _rtXdot->IntegratorSecondOrderLimited_CS[2] = sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[5];
    _rtXdot->IntegratorSecondOrderLimited_CS[5] = sim_ROV_v0_R2018b_B.Sum2_c[2];
}
/* {E!d892}End of Derivatives for SecondOrderIntegrator: '<S53>/Integrator, Second-Order Limited' */

/* {S!d894}Derivatives for TransferFcn: '<S20>/T200 Transfer Function 1' */
_rtXdot->T200TransferFunction1_CSTATE[0] = sim_ROV_v0_R2018b_P.T200TransferFunction1_A[0] * sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[0];
_rtXdot->T200TransferFunction1_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction1_A[1] * sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[1];
_rtXdot->T200TransferFunction1_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction1_A[2] * sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[2];
_rtXdot->T200TransferFunction1_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction1_A[3] * sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[3];
_rtXdot->T200TransferFunction1_CSTATE[1] = sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[0];
_rtXdot->T200TransferFunction1_CSTATE[2] = sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[1];
_rtXdot->T200TransferFunction1_CSTATE[3] = sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[2];
_rtXdot->T200TransferFunction1_CSTATE[0] += sim_ROV_v0_R2018b_B.DeadZone[0];
/* {S!d896}Derivatives for TransferFcn: '<S20>/T200 Transfer Function 2' */
_rtXdot->T200TransferFunction2_CSTATE[0] = sim_ROV_v0_R2018b_P.T200TransferFunction2_A[0] * sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[0];
_rtXdot->T200TransferFunction2_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction2_A[1] * sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[1];
_rtXdot->T200TransferFunction2_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction2_A[2] * sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[2];
_rtXdot->T200TransferFunction2_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction2_A[3] * sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[3];
_rtXdot->T200TransferFunction2_CSTATE[1] = sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[0];
_rtXdot->T200TransferFunction2_CSTATE[2] = sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[1];
_rtXdot->T200TransferFunction2_CSTATE[3] = sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[2];
_rtXdot->T200TransferFunction2_CSTATE[0] += sim_ROV_v0_R2018b_B.DeadZone[1];
/* {S!d898}Derivatives for TransferFcn: '<S20>/T200 Transfer Function 3' */
_rtXdot->T200TransferFunction3_CSTATE[0] = sim_ROV_v0_R2018b_P.T200TransferFunction3_A[0] * sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[0];
_rtXdot->T200TransferFunction3_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction3_A[1] * sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[1];
_rtXdot->T200TransferFunction3_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction3_A[2] * sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[2];
_rtXdot->T200TransferFunction3_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction3_A[3] * sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[3];
_rtXdot->T200TransferFunction3_CSTATE[1] = sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[0];
_rtXdot->T200TransferFunction3_CSTATE[2] = sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[1];
_rtXdot->T200TransferFunction3_CSTATE[3] = sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[2];
_rtXdot->T200TransferFunction3_CSTATE[0] += sim_ROV_v0_R2018b_B.DeadZone[2];
/* {S!d900}Derivatives for TransferFcn: '<S20>/T200 Transfer Function 4' */
_rtXdot->T200TransferFunction4_CSTATE[0] = sim_ROV_v0_R2018b_P.T200TransferFunction4_A[0] * sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[0];
_rtXdot->T200TransferFunction4_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction4_A[1] * sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[1];
_rtXdot->T200TransferFunction4_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction4_A[2] * sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[2];
_rtXdot->T200TransferFunction4_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction4_A[3] * sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[3];
_rtXdot->T200TransferFunction4_CSTATE[1] = sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[0];
_rtXdot->T200TransferFunction4_CSTATE[2] = sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[1];
_rtXdot->T200TransferFunction4_CSTATE[3] = sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[2];
_rtXdot->T200TransferFunction4_CSTATE[0] += sim_ROV_v0_R2018b_B.DeadZone[3];
/* {S!d902}Derivatives for TransferFcn: '<S20>/T200 Transfer Function 5' */
_rtXdot->T200TransferFunction5_CSTATE[0] = sim_ROV_v0_R2018b_P.T200TransferFunction5_A[0] * sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[0];
_rtXdot->T200TransferFunction5_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction5_A[1] * sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[1];
_rtXdot->T200TransferFunction5_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction5_A[2] * sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[2];
_rtXdot->T200TransferFunction5_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction5_A[3] * sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[3];
_rtXdot->T200TransferFunction5_CSTATE[1] = sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[0];
_rtXdot->T200TransferFunction5_CSTATE[2] = sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[1];
_rtXdot->T200TransferFunction5_CSTATE[3] = sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[2];
_rtXdot->T200TransferFunction5_CSTATE[0] += sim_ROV_v0_R2018b_B.DeadZone[4];
/* {S!d904}Derivatives for TransferFcn: '<S20>/T200 Transfer Function 6' */
_rtXdot->T200TransferFunction6_CSTATE[0] = sim_ROV_v0_R2018b_P.T200TransferFunction6_A[0] * sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[0];
_rtXdot->T200TransferFunction6_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction6_A[1] * sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[1];
_rtXdot->T200TransferFunction6_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction6_A[2] * sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[2];
_rtXdot->T200TransferFunction6_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction6_A[3] * sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[3];
_rtXdot->T200TransferFunction6_CSTATE[1] = sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[0];
_rtXdot->T200TransferFunction6_CSTATE[2] = sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[1];
_rtXdot->T200TransferFunction6_CSTATE[3] = sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[2];
_rtXdot->T200TransferFunction6_CSTATE[0] += sim_ROV_v0_R2018b_B.DeadZone[5];
/* {S!d906}Derivatives for TransferFcn: '<S20>/T200 Transfer Function 7' */
_rtXdot->T200TransferFunction7_CSTATE[0] = sim_ROV_v0_R2018b_P.T200TransferFunction7_A[0] * sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[0];
_rtXdot->T200TransferFunction7_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction7_A[1] * sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[1];
_rtXdot->T200TransferFunction7_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction7_A[2] * sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[2];
_rtXdot->T200TransferFunction7_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction7_A[3] * sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[3];
_rtXdot->T200TransferFunction7_CSTATE[1] = sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[0];
_rtXdot->T200TransferFunction7_CSTATE[2] = sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[1];
_rtXdot->T200TransferFunction7_CSTATE[3] = sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[2];
_rtXdot->T200TransferFunction7_CSTATE[0] += sim_ROV_v0_R2018b_B.DeadZone[6];
/* {S!d908}Derivatives for TransferFcn: '<S20>/T200 Transfer Function 8' */
_rtXdot->T200TransferFunction8_CSTATE[0] = sim_ROV_v0_R2018b_P.T200TransferFunction8_A[0] * sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[0];
_rtXdot->T200TransferFunction8_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction8_A[1] * sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[1];
_rtXdot->T200TransferFunction8_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction8_A[2] * sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[2];
_rtXdot->T200TransferFunction8_CSTATE[0] += sim_ROV_v0_R2018b_P.T200TransferFunction8_A[3] * sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[3];
_rtXdot->T200TransferFunction8_CSTATE[1] = sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[0];
_rtXdot->T200TransferFunction8_CSTATE[2] = sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[1];
_rtXdot->T200TransferFunction8_CSTATE[3] = sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[2];
_rtXdot->T200TransferFunction8_CSTATE[0] += sim_ROV_v0_R2018b_B.DeadZone[7];
for (i = 0; i < 6; i++) {
    /* {S!d910}Derivatives for Integrator: '<S18>/Integrator' */
    _rtXdot->Integrator_CSTATE_o[i] = sim_ROV_v0_R2018b_B.BodyAcceleration[i];
    /* {S!d912}Derivatives for Integrator: '<S19>/Integrator' */
    _rtXdot->Integrator_CSTATE_e[i] = sim_ROV_v0_R2018b_B.eta_dot[i];
    /* {S!d914}Derivatives for Integrator: '<S1>/Integrator' */
    _rtXdot->Integrator_CSTATE_i[i] = sim_ROV_v0_R2018b_B.TmpSignalConversionAtIntegrator[i];
}
/* {S!d916}Derivatives for SecondOrderIntegrator: '<S41>/Integrator, Second-Order Limited' */
if (sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited__o[0] == 0) {
    _rtXdot->IntegratorSecondOrderLimited__a[0] = sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[3];
    _rtXdot->IntegratorSecondOrderLimited__a[3] = sim_ROV_v0_R2018b_B.Sum2[0];
}
if (sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited__o[1] == 0) {
    _rtXdot->IntegratorSecondOrderLimited__a[1] = sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[4];
    _rtXdot->IntegratorSecondOrderLimited__a[4] = sim_ROV_v0_R2018b_B.Sum2[1];
}
if (sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited__o[2] == 0) {
    _rtXdot->IntegratorSecondOrderLimited__a[2] = sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[5];
    _rtXdot->IntegratorSecondOrderLimited__a[5] = sim_ROV_v0_R2018b_B.Sum2[2];
}
/* {E!d916}End of Derivatives for SecondOrderIntegrator: '<S41>/Integrator, Second-Order Limited' */





    




                
        
                }
        



















    /* Model initialize function */
    
            void sim_ROV_v0_R2018b_initialize(void)
    {
            


    




    
        

        



            /* Registration code */
                
    /* initialize non-finites */
    rt_InitInfAndNaN(sizeof(real_T));
    
        /* non-finite (run-time) assignments */
        
sim_ROV_v0_R2018b_P.Saturation_UpperSat[0] = rtInf;



sim_ROV_v0_R2018b_P.Saturation_UpperSat[1] = rtInf;



sim_ROV_v0_R2018b_P.Saturation_UpperSat[2] = rtInf;



sim_ROV_v0_R2018b_P.Saturation_LowerSat[0] = rtMinusInf;



sim_ROV_v0_R2018b_P.Saturation_LowerSat[1] = rtMinusInf;



sim_ROV_v0_R2018b_P.Saturation_LowerSat[2] = rtMinusInf;



sim_ROV_v0_R2018b_P.Saturation_UpperSat_e[0] = rtInf;



sim_ROV_v0_R2018b_P.Saturation_UpperSat_e[1] = rtInf;



sim_ROV_v0_R2018b_P.Saturation_UpperSat_e[2] = rtInf;



sim_ROV_v0_R2018b_P.Saturation_LowerSat_a[0] = rtMinusInf;



sim_ROV_v0_R2018b_P.Saturation_LowerSat_a[1] = rtMinusInf;



sim_ROV_v0_R2018b_P.Saturation_LowerSat_a[2] = rtMinusInf;




        





            
            
        {
            /* Setup solver object */

                rtsiSetSimTimeStepPtr(&sim_ROV_v0_R2018b_M->solverInfo, &sim_ROV_v0_R2018b_M->Timing.simTimeStep);
            rtsiSetTPtr(&sim_ROV_v0_R2018b_M->solverInfo, &rtmGetTPtr(sim_ROV_v0_R2018b_M));
                rtsiSetStepSizePtr(&sim_ROV_v0_R2018b_M->solverInfo, &sim_ROV_v0_R2018b_M->Timing.stepSize0);
                rtsiSetdXPtr(&sim_ROV_v0_R2018b_M->solverInfo, &sim_ROV_v0_R2018b_M->derivs);
                rtsiSetContStatesPtr(&sim_ROV_v0_R2018b_M->solverInfo, (real_T **) &sim_ROV_v0_R2018b_M->contStates);
                rtsiSetNumContStatesPtr(&sim_ROV_v0_R2018b_M->solverInfo, &sim_ROV_v0_R2018b_M->Sizes.numContStates);
                    rtsiSetNumPeriodicContStatesPtr(&sim_ROV_v0_R2018b_M->solverInfo, &sim_ROV_v0_R2018b_M->Sizes.numPeriodicContStates);
                    rtsiSetPeriodicContStateIndicesPtr(&sim_ROV_v0_R2018b_M->solverInfo, &sim_ROV_v0_R2018b_M->periodicContStateIndices);
                    rtsiSetPeriodicContStateRangesPtr(&sim_ROV_v0_R2018b_M->solverInfo, &sim_ROV_v0_R2018b_M->periodicContStateRanges);


            rtsiSetErrorStatusPtr(&sim_ROV_v0_R2018b_M->solverInfo, (&rtmGetErrorStatus(sim_ROV_v0_R2018b_M)));


            rtsiSetRTModelPtr(&sim_ROV_v0_R2018b_M->solverInfo, sim_ROV_v0_R2018b_M);
        }
            rtsiSetSimTimeStep(&sim_ROV_v0_R2018b_M->solverInfo, MAJOR_TIME_STEP);
                    sim_ROV_v0_R2018b_M->intgData.y = sim_ROV_v0_R2018b_M->odeY;
                    sim_ROV_v0_R2018b_M->intgData.f[0] = sim_ROV_v0_R2018b_M->odeF[0];
                    sim_ROV_v0_R2018b_M->intgData.f[1] = sim_ROV_v0_R2018b_M->odeF[1];
                    sim_ROV_v0_R2018b_M->intgData.f[2] = sim_ROV_v0_R2018b_M->odeF[2];
                    sim_ROV_v0_R2018b_M->intgData.f[3] = sim_ROV_v0_R2018b_M->odeF[3];
                
                sim_ROV_v0_R2018b_M->contStates = ((X_sim_ROV_v0_R2018b_T *) &sim_ROV_v0_R2018b_X);



                rtsiSetSolverData(&sim_ROV_v0_R2018b_M->solverInfo, static_cast<void *>(&sim_ROV_v0_R2018b_M->intgData));
                rtsiSetIsMinorTimeStepWithModeChange(&sim_ROV_v0_R2018b_M->solverInfo, false);
        rtsiSetSolverName(&sim_ROV_v0_R2018b_M->solverInfo,"ode4");





            rtmSetTPtr(sim_ROV_v0_R2018b_M, &sim_ROV_v0_R2018b_M->Timing.tArray[0]);







                            rtmSetTFinal(sim_ROV_v0_R2018b_M, 100.0);
                                sim_ROV_v0_R2018b_M->Timing.stepSize0  = 0.01;


                    






                    
        /* Setup for data logging */
        {
                static RTWLogInfo rt_DataLoggingInfo;
                rt_DataLoggingInfo.loggingInterval = (nullptr);

                        sim_ROV_v0_R2018b_M->rtwLogInfo = &rt_DataLoggingInfo;

        }


    /* Setup for data logging */
    {
                        rtliSetLogXSignalInfo(sim_ROV_v0_R2018b_M->rtwLogInfo, (nullptr));

                        rtliSetLogXSignalPtrs(sim_ROV_v0_R2018b_M->rtwLogInfo, (nullptr));


                    rtliSetLogT(sim_ROV_v0_R2018b_M->rtwLogInfo, "tout");

                    rtliSetLogX(sim_ROV_v0_R2018b_M->rtwLogInfo, "");

                    rtliSetLogXFinal(sim_ROV_v0_R2018b_M->rtwLogInfo, "");

                    rtliSetLogVarNameModifier(sim_ROV_v0_R2018b_M->rtwLogInfo, "rt_");

                    rtliSetLogFormat(sim_ROV_v0_R2018b_M->rtwLogInfo, 4);

                    rtliSetLogMaxRows(sim_ROV_v0_R2018b_M->rtwLogInfo, 0);

                    rtliSetLogDecimation(sim_ROV_v0_R2018b_M->rtwLogInfo, 1);





                        rtliSetLogY(sim_ROV_v0_R2018b_M->rtwLogInfo, "");


                        rtliSetLogYSignalInfo(sim_ROV_v0_R2018b_M->rtwLogInfo, (nullptr));

                        rtliSetLogYSignalPtrs(sim_ROV_v0_R2018b_M->rtwLogInfo, (nullptr));

    }



                            /* External mode info */
                                sim_ROV_v0_R2018b_M->Sizes.checksums[0] = (1276681435U);
    sim_ROV_v0_R2018b_M->Sizes.checksums[1] = (2568100812U);
    sim_ROV_v0_R2018b_M->Sizes.checksums[2] = (462248302U);
    sim_ROV_v0_R2018b_M->Sizes.checksums[3] = (1687718604U);


                                {
                    static const sysRanDType  rtAlwaysEnabled{ SUBSYS_RAN_BC_ENABLE };
                    static RTWExtModeInfo rt_ExtModeInfo;
                    static const sysRanDType *systemRan[14];



                sim_ROV_v0_R2018b_M->extModeInfo = (&rt_ExtModeInfo);
                rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
                
                systemRan[0] = &rtAlwaysEnabled;
                systemRan[1] = &rtAlwaysEnabled;
                systemRan[2] = &rtAlwaysEnabled;
                systemRan[3] = &rtAlwaysEnabled;
                systemRan[4] = &rtAlwaysEnabled;
                systemRan[5] = &rtAlwaysEnabled;
                systemRan[6] = &rtAlwaysEnabled;
                systemRan[7] = &rtAlwaysEnabled;
                systemRan[8] = &rtAlwaysEnabled;
                systemRan[9] = &rtAlwaysEnabled;
                systemRan[10] = &rtAlwaysEnabled;
                systemRan[11] = &rtAlwaysEnabled;
                systemRan[12] = &rtAlwaysEnabled;
                systemRan[13] = &rtAlwaysEnabled;


                rteiSetModelMappingInfoPtr(sim_ROV_v0_R2018b_M->extModeInfo, &sim_ROV_v0_R2018b_M->SpecialInfo.mappingInfo);

                rteiSetChecksumsPtr(sim_ROV_v0_R2018b_M->extModeInfo, sim_ROV_v0_R2018b_M->Sizes.checksums);

                    rteiSetTPtr(sim_ROV_v0_R2018b_M->extModeInfo, rtmGetTPtr(sim_ROV_v0_R2018b_M));

        }








        




        /* block I/O */
        
        


                
                (void) std::memset((static_cast<void *>(&sim_ROV_v0_R2018b_B)), 0,
sizeof(B_sim_ROV_v0_R2018b_T));
                

                





        





                



















        



            /* states (continuous) */
            {
                
                (void) std::memset(static_cast<void *>(&sim_ROV_v0_R2018b_X), 0,
sizeof(X_sim_ROV_v0_R2018b_T));


            }






        /* states (dwork) */
        
        



                                            (void) std::memset(static_cast<void *>(&sim_ROV_v0_R2018b_DW),  0,
 sizeof(DW_sim_ROV_v0_R2018b_T));
                        






        
    


        
        
        


        




        







                /* data type transition information */
        {
                static DataTypeTransInfo dtInfo;

                sim_ROV_v0_R2018b_M->SpecialInfo.mappingInfo = (&dtInfo);

                dtInfo.numDataTypes  = 20;
                    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
                    dtInfo.dataTypeNames = &rtDataTypeNames[0];

                    /* Block I/O transition table */
                    dtInfo.BTransTable = &rtBTransTable;

                    /* Parameters transition table */
                    dtInfo.PTransTable = &rtPTransTable;
        }


    
            
    
        




        /* Matfile logging */
        
    rt_StartDataLoggingWithStartTime(sim_ROV_v0_R2018b_M->rtwLogInfo, 0.0, rtmGetTFinal(sim_ROV_v0_R2018b_M), sim_ROV_v0_R2018b_M->Timing.stepSize0, (&rtmGetErrorStatus(sim_ROV_v0_R2018b_M)));











            {
    
real_T tmp;
int32_T i;
int32_T t;
uint32_T tseed;






                




                                                
                                    


/* {S!d516}InitializeConditions for Integrator: '<S30>/Integrator6' */
sim_ROV_v0_R2018b_X.Integrator6_CSTATE = sim_ROV_v0_R2018b_P.Integrator6_IC;
/* {S!d518}InitializeConditions for Integrator: '<S30>/Integrator7' */
sim_ROV_v0_R2018b_X.Integrator7_CSTATE = sim_ROV_v0_R2018b_P.Integrator7_IC;
/* {S!d520}InitializeConditions for Integrator: '<S30>/Integrator8' */
sim_ROV_v0_R2018b_X.Integrator8_CSTATE = sim_ROV_v0_R2018b_P.Integrator8_IC;
/* {S!d522}InitializeConditions for Integrator: '<S30>/Integrator' */
sim_ROV_v0_R2018b_X.Integrator_CSTATE = sim_ROV_v0_R2018b_P.Integrator_IC;
/* {S!d524}InitializeConditions for Integrator: '<S30>/Integrator1' */
sim_ROV_v0_R2018b_X.Integrator1_CSTATE = sim_ROV_v0_R2018b_P.Integrator1_IC;
/* {S!d526}InitializeConditions for Integrator: '<S30>/Integrator2' */
sim_ROV_v0_R2018b_X.Integrator2_CSTATE = sim_ROV_v0_R2018b_P.Integrator2_IC;
/* {S!d528}InitializeConditions for Integrator: '<S30>/Integrator3' */
sim_ROV_v0_R2018b_X.Integrator3_CSTATE = sim_ROV_v0_R2018b_P.Integrator3_IC;
/* {S!d530}InitializeConditions for Integrator: '<S30>/Integrator4' */
sim_ROV_v0_R2018b_X.Integrator4_CSTATE = sim_ROV_v0_R2018b_P.Integrator4_IC;
/* {S!d532}InitializeConditions for Integrator: '<S30>/Integrator5' */
sim_ROV_v0_R2018b_X.Integrator5_CSTATE = sim_ROV_v0_R2018b_P.Integrator5_IC;
/* {S!d534}InitializeConditions for SecondOrderIntegrator: '<S53>/Integrator, Second-Order Limited' */
sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[0] = sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited_IC;
sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[1] = sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited_IC;
sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[2] = sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited_IC;
sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[3] = sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited__c;
sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited_MO[0] = 0;
sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[4] = sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited__c;
sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited_MO[1] = 0;
sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited_CS[5] = sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited__c;
sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited_MO[2] = 0;
/* {S!d536}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 1' */
sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[0] = 0.0;
/* {S!d538}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 2' */
sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[0] = 0.0;
/* {S!d540}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 3' */
sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[0] = 0.0;
/* {S!d542}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 4' */
sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[0] = 0.0;
/* {S!d544}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 5' */
sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[0] = 0.0;
/* {S!d546}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 6' */
sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[0] = 0.0;
/* {S!d548}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 7' */
sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[0] = 0.0;
/* {S!d550}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 8' */
sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[0] = 0.0;
/* {S!d552}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 1' */
sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[1] = 0.0;
/* {S!d554}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 2' */
sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[1] = 0.0;
/* {S!d556}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 3' */
sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[1] = 0.0;
/* {S!d558}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 4' */
sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[1] = 0.0;
/* {S!d560}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 5' */
sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[1] = 0.0;
/* {S!d562}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 6' */
sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[1] = 0.0;
/* {S!d564}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 7' */
sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[1] = 0.0;
/* {S!d566}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 8' */
sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[1] = 0.0;
/* {S!d568}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 1' */
sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[2] = 0.0;
/* {S!d570}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 2' */
sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[2] = 0.0;
/* {S!d572}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 3' */
sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[2] = 0.0;
/* {S!d574}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 4' */
sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[2] = 0.0;
/* {S!d576}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 5' */
sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[2] = 0.0;
/* {S!d578}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 6' */
sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[2] = 0.0;
/* {S!d580}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 7' */
sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[2] = 0.0;
/* {S!d582}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 8' */
sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[2] = 0.0;
/* {S!d584}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 1' */
sim_ROV_v0_R2018b_X.T200TransferFunction1_CSTATE[3] = 0.0;
/* {S!d586}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 2' */
sim_ROV_v0_R2018b_X.T200TransferFunction2_CSTATE[3] = 0.0;
/* {S!d588}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 3' */
sim_ROV_v0_R2018b_X.T200TransferFunction3_CSTATE[3] = 0.0;
/* {S!d590}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 4' */
sim_ROV_v0_R2018b_X.T200TransferFunction4_CSTATE[3] = 0.0;
/* {S!d592}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 5' */
sim_ROV_v0_R2018b_X.T200TransferFunction5_CSTATE[3] = 0.0;
/* {S!d594}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 6' */
sim_ROV_v0_R2018b_X.T200TransferFunction6_CSTATE[3] = 0.0;
/* {S!d596}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 7' */
sim_ROV_v0_R2018b_X.T200TransferFunction7_CSTATE[3] = 0.0;
/* {S!d598}InitializeConditions for TransferFcn: '<S20>/T200 Transfer Function 8' */
sim_ROV_v0_R2018b_X.T200TransferFunction8_CSTATE[3] = 0.0;
for (i = 0; i < 6; i++) {
    /* {S!d600}InitializeConditions for Integrator: '<S18>/Integrator' */
    sim_ROV_v0_R2018b_X.Integrator_CSTATE_o[i] = sim_ROV_v0_R2018b_P.Integrator_IC_m;
    /* {S!d602}InitializeConditions for Integrator: '<S19>/Integrator' */
    sim_ROV_v0_R2018b_X.Integrator_CSTATE_e[i] = sim_ROV_v0_R2018b_P.Integrator_IC_j;
}
/* {S!d604}InitializeConditions for RandomNumber: '<S51>/White Noise' */
tmp = std::floor(sim_ROV_v0_R2018b_P.ThreeaxisGyroscope_g_seeds[0]);
if (std::isnan(tmp) || std::isinf(tmp)) {
    tmp = 0.0;
} else {
    tmp = std::fmod(tmp, 4.294967296E+9);
}
tseed = tmp < 0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(static_cast<uint32_T>(-tmp))) : static_cast<uint32_T>(tmp);
i = static_cast<int32_T>(tseed >> 16U);
t = static_cast<int32_T>(tseed & 32768U);
tseed = ((((tseed - (static_cast<uint32_T>(i) << 16U)) + static_cast<uint32_T>(t)) << 16U) + static_cast<uint32_T>(t)) + static_cast<uint32_T>(i);
if (tseed < 1U) {
    tseed = 1144108930U;
} else if (tseed > 2147483646U) {
    tseed = 2147483646U;
}
sim_ROV_v0_R2018b_DW.RandSeed[0] = tseed;
sim_ROV_v0_R2018b_DW.NextOutput[0] = rt_nrand_Upu32_Yd_f_pw_snf(&sim_ROV_v0_R2018b_DW.RandSeed[0]) * sim_ROV_v0_R2018b_P.WhiteNoise_StdDev + sim_ROV_v0_R2018b_P.WhiteNoise_Mean;
tmp = std::floor(sim_ROV_v0_R2018b_P.ThreeaxisGyroscope_g_seeds[1]);
if (std::isnan(tmp) || std::isinf(tmp)) {
    tmp = 0.0;
} else {
    tmp = std::fmod(tmp, 4.294967296E+9);
}
tseed = tmp < 0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(static_cast<uint32_T>(-tmp))) : static_cast<uint32_T>(tmp);
i = static_cast<int32_T>(tseed >> 16U);
t = static_cast<int32_T>(tseed & 32768U);
tseed = ((((tseed - (static_cast<uint32_T>(i) << 16U)) + static_cast<uint32_T>(t)) << 16U) + static_cast<uint32_T>(t)) + static_cast<uint32_T>(i);
if (tseed < 1U) {
    tseed = 1144108930U;
} else if (tseed > 2147483646U) {
    tseed = 2147483646U;
}
sim_ROV_v0_R2018b_DW.RandSeed[1] = tseed;
sim_ROV_v0_R2018b_DW.NextOutput[1] = rt_nrand_Upu32_Yd_f_pw_snf(&sim_ROV_v0_R2018b_DW.RandSeed[1]) * sim_ROV_v0_R2018b_P.WhiteNoise_StdDev + sim_ROV_v0_R2018b_P.WhiteNoise_Mean;
tmp = std::floor(sim_ROV_v0_R2018b_P.ThreeaxisGyroscope_g_seeds[2]);
if (std::isnan(tmp) || std::isinf(tmp)) {
    tmp = 0.0;
} else {
    tmp = std::fmod(tmp, 4.294967296E+9);
}
tseed = tmp < 0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(static_cast<uint32_T>(-tmp))) : static_cast<uint32_T>(tmp);
i = static_cast<int32_T>(tseed >> 16U);
t = static_cast<int32_T>(tseed & 32768U);
tseed = ((((tseed - (static_cast<uint32_T>(i) << 16U)) + static_cast<uint32_T>(t)) << 16U) + static_cast<uint32_T>(t)) + static_cast<uint32_T>(i);
if (tseed < 1U) {
    tseed = 1144108930U;
} else if (tseed > 2147483646U) {
    tseed = 2147483646U;
}
sim_ROV_v0_R2018b_DW.RandSeed[2] = tseed;
sim_ROV_v0_R2018b_DW.NextOutput[2] = rt_nrand_Upu32_Yd_f_pw_snf(&sim_ROV_v0_R2018b_DW.RandSeed[2]) * sim_ROV_v0_R2018b_P.WhiteNoise_StdDev + sim_ROV_v0_R2018b_P.WhiteNoise_Mean;
/* {E!d604}End of InitializeConditions for RandomNumber: '<S51>/White Noise' */

/* {S!d606}InitializeConditions for Derivative: '<S19>/Derivative' */
sim_ROV_v0_R2018b_DW.TimeStampA = (rtInf);
sim_ROV_v0_R2018b_DW.TimeStampB = (rtInf);
/* {S!d608}InitializeConditions for Integrator: '<S1>/Integrator' */
for (i = 0; i < 6; i++) {
    sim_ROV_v0_R2018b_X.Integrator_CSTATE_i[i] = sim_ROV_v0_R2018b_P.Integrator_IC_a;
}
/* {E!d608}End of InitializeConditions for Integrator: '<S1>/Integrator' */

/* {S!d610}InitializeConditions for SecondOrderIntegrator: '<S41>/Integrator, Second-Order Limited' */
sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[0] = sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited__j;
sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[1] = sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited__j;
sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[2] = sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited__j;
sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[3] = sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited__e;
sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited__o[0] = 0;
/* {S!d612}InitializeConditions for RandomNumber: '<S37>/White Noise' */
tmp = std::floor(sim_ROV_v0_R2018b_P.ThreeaxisAccelerometer_a_seeds[0]);
if (std::isnan(tmp) || std::isinf(tmp)) {
    tmp = 0.0;
} else {
    tmp = std::fmod(tmp, 4.294967296E+9);
}
tseed = tmp < 0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(static_cast<uint32_T>(-tmp))) : static_cast<uint32_T>(tmp);
i = static_cast<int32_T>(tseed >> 16U);
t = static_cast<int32_T>(tseed & 32768U);
tseed = ((((tseed - (static_cast<uint32_T>(i) << 16U)) + static_cast<uint32_T>(t)) << 16U) + static_cast<uint32_T>(t)) + static_cast<uint32_T>(i);
if (tseed < 1U) {
    tseed = 1144108930U;
} else if (tseed > 2147483646U) {
    tseed = 2147483646U;
}
sim_ROV_v0_R2018b_DW.RandSeed_l[0] = tseed;
sim_ROV_v0_R2018b_DW.NextOutput_p[0] = rt_nrand_Upu32_Yd_f_pw_snf(&sim_ROV_v0_R2018b_DW.RandSeed_l[0]) * sim_ROV_v0_R2018b_P.WhiteNoise_StdDev_j + sim_ROV_v0_R2018b_P.WhiteNoise_Mean_g;
/* {S!d614}InitializeConditions for SecondOrderIntegrator: '<S41>/Integrator, Second-Order Limited' */
sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[4] = sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited__e;
sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited__o[1] = 0;
/* {S!d616}InitializeConditions for RandomNumber: '<S37>/White Noise' */
tmp = std::floor(sim_ROV_v0_R2018b_P.ThreeaxisAccelerometer_a_seeds[1]);
if (std::isnan(tmp) || std::isinf(tmp)) {
    tmp = 0.0;
} else {
    tmp = std::fmod(tmp, 4.294967296E+9);
}
tseed = tmp < 0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(static_cast<uint32_T>(-tmp))) : static_cast<uint32_T>(tmp);
i = static_cast<int32_T>(tseed >> 16U);
t = static_cast<int32_T>(tseed & 32768U);
tseed = ((((tseed - (static_cast<uint32_T>(i) << 16U)) + static_cast<uint32_T>(t)) << 16U) + static_cast<uint32_T>(t)) + static_cast<uint32_T>(i);
if (tseed < 1U) {
    tseed = 1144108930U;
} else if (tseed > 2147483646U) {
    tseed = 2147483646U;
}
sim_ROV_v0_R2018b_DW.RandSeed_l[1] = tseed;
sim_ROV_v0_R2018b_DW.NextOutput_p[1] = rt_nrand_Upu32_Yd_f_pw_snf(&sim_ROV_v0_R2018b_DW.RandSeed_l[1]) * sim_ROV_v0_R2018b_P.WhiteNoise_StdDev_j + sim_ROV_v0_R2018b_P.WhiteNoise_Mean_g;
/* {S!d618}InitializeConditions for SecondOrderIntegrator: '<S41>/Integrator, Second-Order Limited' */
sim_ROV_v0_R2018b_X.IntegratorSecondOrderLimited__a[5] = sim_ROV_v0_R2018b_P.IntegratorSecondOrderLimited__e;
sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited__o[2] = 0;
/* {S!d620}InitializeConditions for RandomNumber: '<S37>/White Noise' */
tmp = std::floor(sim_ROV_v0_R2018b_P.ThreeaxisAccelerometer_a_seeds[2]);
if (std::isnan(tmp) || std::isinf(tmp)) {
    tmp = 0.0;
} else {
    tmp = std::fmod(tmp, 4.294967296E+9);
}
tseed = tmp < 0.0 ? static_cast<uint32_T>(-static_cast<int32_T>(static_cast<uint32_T>(-tmp))) : static_cast<uint32_T>(tmp);
i = static_cast<int32_T>(tseed >> 16U);
t = static_cast<int32_T>(tseed & 32768U);
tseed = ((((tseed - (static_cast<uint32_T>(i) << 16U)) + static_cast<uint32_T>(t)) << 16U) + static_cast<uint32_T>(t)) + static_cast<uint32_T>(i);
if (tseed < 1U) {
    tseed = 1144108930U;
} else if (tseed > 2147483646U) {
    tseed = 2147483646U;
}
sim_ROV_v0_R2018b_DW.RandSeed_l[2] = tseed;
sim_ROV_v0_R2018b_DW.NextOutput_p[2] = rt_nrand_Upu32_Yd_f_pw_snf(&sim_ROV_v0_R2018b_DW.RandSeed_l[2]) * sim_ROV_v0_R2018b_P.WhiteNoise_StdDev_j + sim_ROV_v0_R2018b_P.WhiteNoise_Mean_g;
/* {S!d622}SystemInitialize for MATLAB Function: '<S24>/hydrostatics' */
sim_ROV_v0_R2018b_DW.sfEvent_o = sim_ROV_v0_R2018b_CALL_EVENT;
sim_ROV_v0_R2018b_DW.is_active_c1_sim_ROV_v0_R2018b = 0U;
/* {S!d624}SystemInitialize for MATLAB Function: '<S22>/Rigid Body Coriolis & Centripetal' */
sim_ROV_v0_R2018b_DW.sfEvent_ou = sim_ROV_v0_R2018b_CALL_EVENT;
sim_ROV_v0_R2018b_DW.is_active_c2_sim_ROV_v0_R2018b = 0U;
/* {S!d626}SystemInitialize for MATLAB Function: '<S22>/Added Coriolis & Centripetal' */
sim_ROV_v0_R2018b_DW.sfEvent_i = sim_ROV_v0_R2018b_CALL_EVENT;
sim_ROV_v0_R2018b_DW.is_active_c4_sim_ROV_v0_R2018b = 0U;
/* {S!d628}SystemInitialize for MATLAB Function: '<S19>/kinematics' */
sim_ROV_v0_R2018b_DW.sfEvent = sim_ROV_v0_R2018b_CALL_EVENT;
sim_ROV_v0_R2018b_DW.is_active_c3_sim_ROV_v0_R2018b = 0U;
/* {S!d630}SystemInitialize for MATLAB Function: '<S16>/Normalization' */
sim_ROV_v0_R2018b_DW.sfEvent_c = sim_ROV_v0_R2018b_CALL_EVENT;
sim_ROV_v0_R2018b_DW.is_active_c6_sim_ROV_v0_R2018b = 0U;

        sim_ROV_v0__LowpassFilter3_Init(&sim_ROV_v0_R2018b_DW.LowpassFilter3);

        sim_ROV_v0__LowpassFilter3_Init(&sim_ROV_v0_R2018b_DW.LowpassFilter4);

        sim_ROV_v0__LowpassFilter3_Init(&sim_ROV_v0_R2018b_DW.LowpassFilter5);

        sim_ROV_v0_R_LowpassFilter_Init(&sim_ROV_v0_R2018b_DW.LowpassFilter);

        sim_ROV_v0_R_LowpassFilter_Init(&sim_ROV_v0_R2018b_DW.LowpassFilter1);

        sim_ROV_v0_R_LowpassFilter_Init(&sim_ROV_v0_R2018b_DW.LowpassFilter2);












                        }


    





                



        
    }        






        




        
        /* Model terminate function */
                    void sim_ROV_v0_R2018b_terminate(void)

        {
            


                                                            




                        




                                                    

                        
                                    

        sim_ROV_v0__LowpassFilter3_Term(&sim_ROV_v0_R2018b_DW.LowpassFilter3);

        sim_ROV_v0__LowpassFilter3_Term(&sim_ROV_v0_R2018b_DW.LowpassFilter4);

        sim_ROV_v0__LowpassFilter3_Term(&sim_ROV_v0_R2018b_DW.LowpassFilter5);

        sim_ROV_v0_R_LowpassFilter_Term(&sim_ROV_v0_R2018b_DW.LowpassFilter);

        sim_ROV_v0_R_LowpassFilter_Term(&sim_ROV_v0_R2018b_DW.LowpassFilter1);

        sim_ROV_v0_R_LowpassFilter_Term(&sim_ROV_v0_R2018b_DW.LowpassFilter2);





                


                    




                




                                



                        }
            





    




    

    

    

    
