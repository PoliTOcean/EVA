

        /*
    * sim_ROV_v0_R2018b.h
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


    #ifndef RTW_HEADER_sim_ROV_v0_R2018b_h_
    #define RTW_HEADER_sim_ROV_v0_R2018b_h_



                        #include "rtwtypes.h"
        #include "rtw_extmode.h"
        #include "sysran_types.h"
        #include "rtw_continuous.h"
        #include "rtw_solver.h"
        #include "rt_logging.h"
        #include "dt_info.h"
        #include "ext_work.h"




#include "sim_ROV_v0_R2018b_types.h"

extern "C" {

#include "rt_nonfinite.h"
}

extern "C" {

#include "rtGetInf.h"
}

#include <cfloat>

#include <cstring>


    

    

    

    
            /* Macros for accessing real-time model data structure */
                    #ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm) ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm) ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val) ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm) ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm) ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val) ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm) ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val) ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm) ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val) ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm) ((rtm)->extModeInfo)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm) ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm) ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm) ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val) ((rtm)->derivs = (val))
#endif




        #ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm) ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm) ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm) (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm) (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm) ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm) ((rtm)->Timing.t)
#endif


    







    

    

    

    

                    /* Block signals for system '<S30>/Lowpass Filter' */
                    
        struct B_LowpassFilter_sim_ROV_v0_R2_T {
        




                    
                    


                        



                            
                            
                                   real_T LowpassFilter; /* '<S30>/Lowpass Filter' */

                        
                        
                        


                    




        };

                            /* Block states (default storage) for system '<S30>/Lowpass Filter' */

                    
        struct DW_LowpassFilter_sim_ROV_v0_R_T {
        




                    
                    


                        



                            
                            
                                   dsp_simulink_LowpassFilter_si_T obj; /* '<S30>/Lowpass Filter' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   boolean_T objisempty; /* '<S30>/Lowpass Filter' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   boolean_T isInitialized; /* '<S30>/Lowpass Filter' */

                        
                        
                        


                    




        };

            
                /* Block signals for system '<S30>/Lowpass Filter3' */
                    
        struct B_LowpassFilter3_sim_ROV_v0_R_T {
        




                    
                    


                        



                            
                            
                                   real_T LowpassFilter3; /* '<S30>/Lowpass Filter3' */

                        
                        
                        


                    




        };

                            /* Block states (default storage) for system '<S30>/Lowpass Filter3' */

                    
        struct DW_LowpassFilter3_sim_ROV_v0__T {
        




                    
                    


                        



                            
                            
                                   dsp_simulink_LowpassFilter_si_T obj; /* '<S30>/Lowpass Filter3' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   boolean_T objisempty; /* '<S30>/Lowpass Filter3' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   boolean_T isInitialized; /* '<S30>/Lowpass Filter3' */

                        
                        
                        


                    




        };

            
                /* Block signals (default storage) */
                    
        struct B_sim_ROV_v0_R2018b_T {
        




                    
                    


                        



                            
                            
                                   real_T Integrator6; /* '<S30>/Integrator6' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator7; /* '<S30>/Integrator7' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator8; /* '<S30>/Integrator8' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator; /* '<S30>/Integrator' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator1; /* '<S30>/Integrator1' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator2; /* '<S30>/Integrator2' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator3; /* '<S30>/Integrator3' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator4; /* '<S30>/Integrator4' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator5; /* '<S30>/Integrator5' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThrustN[8]; /* '<S16>/lbf → N' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ForcesMoments[6]; /* '<S2>/Thrust Configuration Matrix' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Pose[6]; /* '<S19>/Integrator' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Sum[6]; /* '<S23>/Sum' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Add[6]; /* '<S22>/Add' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T BodyAcceleration[6]; /* '<S18>/Product1' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Product[3]; /* '<S51>/Product' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Saturation[3]; /* '<S35>/Saturation' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Acceleration[6]; /* '<S19>/Derivative' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Gain[6]; /* '<S4>/Gain' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Gain1; /* '<S4>/Gain1' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Gain2; /* '<S4>/Gain2' */

                        
                        
                        


                    






                    
                    


                        



                            
                                   real_T TmpSignalConversionAtIntegrator[6]; 

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T DeadZone[8]; /* '<S16>/Dead Zone' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ZeroOrderHold2[3]; /* '<S34>/Zero-Order Hold2' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Gain_n[3]; /* '<S34>/Gain' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Product_i[3]; /* '<S37>/Product' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Saturation_m[3]; /* '<S34>/Saturation' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Sum2[3]; /* '<S41>/Sum2' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Sum2_c[3]; /* '<S53>/Sum2' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T eta_dot[6]; /* '<S19>/kinematics' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T F_g[6]; /* '<S24>/hydrostatics' */

                        
                        
                        


                    





                    
                    


                        



                            
                                   B_LowpassFilter3_sim_ROV_v0_R_T LowpassFilter5; /* '<S30>/Lowpass Filter3' */

                        
                        
                        


                    





                    
                    


                        



                            
                                   B_LowpassFilter3_sim_ROV_v0_R_T LowpassFilter4; /* '<S30>/Lowpass Filter3' */

                        
                        
                        


                    





                    
                    


                        



                            
                                   B_LowpassFilter3_sim_ROV_v0_R_T LowpassFilter3; /* '<S30>/Lowpass Filter3' */

                        
                        
                        


                    





                    
                    


                        



                            
                                   B_LowpassFilter_sim_ROV_v0_R2_T LowpassFilter2; /* '<S30>/Lowpass Filter' */

                        
                        
                        


                    





                    
                    


                        



                            
                                   B_LowpassFilter_sim_ROV_v0_R2_T LowpassFilter1; /* '<S30>/Lowpass Filter' */

                        
                        
                        


                    





                    
                    


                        



                            
                                   B_LowpassFilter_sim_ROV_v0_R2_T LowpassFilter; /* '<S30>/Lowpass Filter' */

                        
                        
                        


                    




        };

                            /* Block states (default storage) for system '<Root>' */

                    
        struct DW_sim_ROV_v0_R2018b_T {
        




                    
                    


                        



                            
                            
                                   real_T NextOutput[3]; /* '<S51>/White Noise' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T TimeStampA; /* '<S19>/Derivative' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T LastUAtTimeA[6]; /* '<S19>/Derivative' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T TimeStampB; /* '<S19>/Derivative' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T LastUAtTimeB[6]; /* '<S19>/Derivative' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T NextOutput_p[3]; /* '<S37>/White Noise' */

                        
                        
                        


                    






                    
                    


                        
                                    
                            
        struct {
                    void *LoggedData;
        } Scope_PWORK; /* '<Root>/Scope' */
    

            



                    






                    
                    


                        
                                    
                            
        struct {
                    void *LoggedData[6];
        } VisualizationKinematics_PWORK; /* '<S6>/Visualization (Kinematics)' */
    

            



                    






                    
                    


                        
                                    
                            
        struct {
                    void *LoggedData[2];
        } VisualizationPropulsion_PWORK; /* '<S6>/Visualization (Propulsion)' */
    

            



                    






                    
                    


                        
                                    
                            
        struct {
                    void *LoggedData;
        } Scope_PWORK_i; /* '<S18>/Scope' */
    

            



                    






                    
                    


                        
                                    
                            
        struct {
                    void *LoggedData;
        } Scope1_PWORK; /* '<S18>/Scope1' */
    

            



                    






                    
                    


                        
                                    
                            
        struct {
                    void *LoggedData;
        } Scope2_PWORK; /* '<S18>/Scope2' */
    

            



                    






                    
                    


                        
                                    
                            
        struct {
                    void *LoggedData;
        } Scope3_PWORK; /* '<S18>/Scope3' */
    

            



                    






                    
                    


                        



                            
                            
                                   int32_T sfEvent; /* '<S19>/kinematics' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   int32_T sfEvent_o; /* '<S24>/hydrostatics' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   int32_T sfEvent_ou; /* '<S22>/Rigid Body Coriolis & Centripetal' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   int32_T sfEvent_i; /* '<S22>/Added Coriolis & Centripetal' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   int32_T sfEvent_c; /* '<S16>/Normalization' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   uint32_T RandSeed[3]; /* '<S51>/White Noise' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   uint32_T RandSeed_l[3]; /* '<S37>/White Noise' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   int_T IntegratorSecondOrderLimited_MO[3]; /* '<S53>/Integrator, Second-Order Limited' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   int_T IntegratorSecondOrderLimited__o[3]; /* '<S41>/Integrator, Second-Order Limited' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   uint8_T is_active_c3_sim_ROV_v0_R2018b; /* '<S19>/kinematics' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   uint8_T is_active_c1_sim_ROV_v0_R2018b; /* '<S24>/hydrostatics' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   uint8_T is_active_c2_sim_ROV_v0_R2018b; /* '<S22>/Rigid Body Coriolis & Centripetal' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   uint8_T is_active_c4_sim_ROV_v0_R2018b; /* '<S22>/Added Coriolis & Centripetal' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   uint8_T is_active_c6_sim_ROV_v0_R2018b; /* '<S16>/Normalization' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   boolean_T IntegratorSecondOrderLimited_DW; /* '<S53>/Integrator, Second-Order Limited' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   boolean_T IntegratorSecondOrderLimited__i; /* '<S41>/Integrator, Second-Order Limited' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   boolean_T doneDoubleBufferReInit; /* '<S19>/kinematics' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   boolean_T doneDoubleBufferReInit_e; /* '<S24>/hydrostatics' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   boolean_T doneDoubleBufferReInit_n; /* '<S22>/Rigid Body Coriolis & Centripetal' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   boolean_T doneDoubleBufferReInit_b; /* '<S22>/Added Coriolis & Centripetal' */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   boolean_T doneDoubleBufferReInit_a; /* '<S16>/Normalization' */

                        
                        
                        


                    





                    
                    


                        



                            
                                   DW_LowpassFilter3_sim_ROV_v0__T LowpassFilter5; /* '<S30>/Lowpass Filter3' */

                        
                        
                        


                    





                    
                    


                        



                            
                                   DW_LowpassFilter3_sim_ROV_v0__T LowpassFilter4; /* '<S30>/Lowpass Filter3' */

                        
                        
                        


                    





                    
                    


                        



                            
                                   DW_LowpassFilter3_sim_ROV_v0__T LowpassFilter3; /* '<S30>/Lowpass Filter3' */

                        
                        
                        


                    





                    
                    


                        



                            
                                   DW_LowpassFilter_sim_ROV_v0_R_T LowpassFilter2; /* '<S30>/Lowpass Filter' */

                        
                        
                        


                    





                    
                    


                        



                            
                                   DW_LowpassFilter_sim_ROV_v0_R_T LowpassFilter1; /* '<S30>/Lowpass Filter' */

                        
                        
                        


                    





                    
                    


                        



                            
                                   DW_LowpassFilter_sim_ROV_v0_R_T LowpassFilter; /* '<S30>/Lowpass Filter' */

                        
                        
                        


                    




        };

            
        
                /* Continuous states (default storage) */
                    struct X_sim_ROV_v0_R2018b_T {
                            
                        real_T Integrator6_CSTATE; /* '<S30>/Integrator6' */
                    
                    
                        real_T Integrator7_CSTATE; /* '<S30>/Integrator7' */
                    
                    
                        real_T Integrator8_CSTATE; /* '<S30>/Integrator8' */
                    
                    
                        real_T Integrator_CSTATE; /* '<S30>/Integrator' */
                    
                    
                        real_T Integrator1_CSTATE; /* '<S30>/Integrator1' */
                    
                    
                        real_T Integrator2_CSTATE; /* '<S30>/Integrator2' */
                    
                    
                        real_T Integrator3_CSTATE; /* '<S30>/Integrator3' */
                    
                    
                        real_T Integrator4_CSTATE; /* '<S30>/Integrator4' */
                    
                    
                        real_T Integrator5_CSTATE; /* '<S30>/Integrator5' */
                    
                    
                        real_T IntegratorSecondOrderLimited_CS[6]; /* '<S53>/Integrator, Second-Order Limited' */
                    
                    
                        real_T Integrator_CSTATE_o[6]; /* '<S18>/Integrator' */
                    
                    
                        real_T T200TransferFunction1_CSTATE[4]; /* '<S20>/T200 Transfer Function 1' */
                    
                    
                        real_T T200TransferFunction2_CSTATE[4]; /* '<S20>/T200 Transfer Function 2' */
                    
                    
                        real_T T200TransferFunction3_CSTATE[4]; /* '<S20>/T200 Transfer Function 3' */
                    
                    
                        real_T T200TransferFunction4_CSTATE[4]; /* '<S20>/T200 Transfer Function 4' */
                    
                    
                        real_T T200TransferFunction5_CSTATE[4]; /* '<S20>/T200 Transfer Function 5' */
                    
                    
                        real_T T200TransferFunction6_CSTATE[4]; /* '<S20>/T200 Transfer Function 6' */
                    
                    
                        real_T T200TransferFunction7_CSTATE[4]; /* '<S20>/T200 Transfer Function 7' */
                    
                    
                        real_T T200TransferFunction8_CSTATE[4]; /* '<S20>/T200 Transfer Function 8' */
                    
                    
                        real_T Integrator_CSTATE_e[6]; /* '<S19>/Integrator' */
                    
                    
                        real_T Integrator_CSTATE_i[6]; /* '<S1>/Integrator' */
                    
                    
                        real_T IntegratorSecondOrderLimited__a[6]; /* '<S41>/Integrator, Second-Order Limited' */
                    
    
        };
            
                                /* State derivatives (default storage) */
                            struct XDot_sim_ROV_v0_R2018b_T {
                                
                        real_T Integrator6_CSTATE; /* '<S30>/Integrator6' */
                    
                    
                        real_T Integrator7_CSTATE; /* '<S30>/Integrator7' */
                    
                    
                        real_T Integrator8_CSTATE; /* '<S30>/Integrator8' */
                    
                    
                        real_T Integrator_CSTATE; /* '<S30>/Integrator' */
                    
                    
                        real_T Integrator1_CSTATE; /* '<S30>/Integrator1' */
                    
                    
                        real_T Integrator2_CSTATE; /* '<S30>/Integrator2' */
                    
                    
                        real_T Integrator3_CSTATE; /* '<S30>/Integrator3' */
                    
                    
                        real_T Integrator4_CSTATE; /* '<S30>/Integrator4' */
                    
                    
                        real_T Integrator5_CSTATE; /* '<S30>/Integrator5' */
                    
                    
                        real_T IntegratorSecondOrderLimited_CS[6]; /* '<S53>/Integrator, Second-Order Limited' */
                    
                    
                        real_T Integrator_CSTATE_o[6]; /* '<S18>/Integrator' */
                    
                    
                        real_T T200TransferFunction1_CSTATE[4]; /* '<S20>/T200 Transfer Function 1' */
                    
                    
                        real_T T200TransferFunction2_CSTATE[4]; /* '<S20>/T200 Transfer Function 2' */
                    
                    
                        real_T T200TransferFunction3_CSTATE[4]; /* '<S20>/T200 Transfer Function 3' */
                    
                    
                        real_T T200TransferFunction4_CSTATE[4]; /* '<S20>/T200 Transfer Function 4' */
                    
                    
                        real_T T200TransferFunction5_CSTATE[4]; /* '<S20>/T200 Transfer Function 5' */
                    
                    
                        real_T T200TransferFunction6_CSTATE[4]; /* '<S20>/T200 Transfer Function 6' */
                    
                    
                        real_T T200TransferFunction7_CSTATE[4]; /* '<S20>/T200 Transfer Function 7' */
                    
                    
                        real_T T200TransferFunction8_CSTATE[4]; /* '<S20>/T200 Transfer Function 8' */
                    
                    
                        real_T Integrator_CSTATE_e[6]; /* '<S19>/Integrator' */
                    
                    
                        real_T Integrator_CSTATE_i[6]; /* '<S1>/Integrator' */
                    
                    
                        real_T IntegratorSecondOrderLimited__a[6]; /* '<S41>/Integrator, Second-Order Limited' */
                    
                };                        
                /* State disabled  */
                    struct XDis_sim_ROV_v0_R2018b_T {                            
                        boolean_T Integrator6_CSTATE; /* '<S30>/Integrator6' */
                    
                    
                        boolean_T Integrator7_CSTATE; /* '<S30>/Integrator7' */
                    
                    
                        boolean_T Integrator8_CSTATE; /* '<S30>/Integrator8' */
                    
                    
                        boolean_T Integrator_CSTATE; /* '<S30>/Integrator' */
                    
                    
                        boolean_T Integrator1_CSTATE; /* '<S30>/Integrator1' */
                    
                    
                        boolean_T Integrator2_CSTATE; /* '<S30>/Integrator2' */
                    
                    
                        boolean_T Integrator3_CSTATE; /* '<S30>/Integrator3' */
                    
                    
                        boolean_T Integrator4_CSTATE; /* '<S30>/Integrator4' */
                    
                    
                        boolean_T Integrator5_CSTATE; /* '<S30>/Integrator5' */
                    
                    
                        boolean_T IntegratorSecondOrderLimited_CS[6]; /* '<S53>/Integrator, Second-Order Limited' */
                    
                    
                        boolean_T Integrator_CSTATE_o[6]; /* '<S18>/Integrator' */
                    
                    
                        boolean_T T200TransferFunction1_CSTATE[4]; /* '<S20>/T200 Transfer Function 1' */
                    
                    
                        boolean_T T200TransferFunction2_CSTATE[4]; /* '<S20>/T200 Transfer Function 2' */
                    
                    
                        boolean_T T200TransferFunction3_CSTATE[4]; /* '<S20>/T200 Transfer Function 3' */
                    
                    
                        boolean_T T200TransferFunction4_CSTATE[4]; /* '<S20>/T200 Transfer Function 4' */
                    
                    
                        boolean_T T200TransferFunction5_CSTATE[4]; /* '<S20>/T200 Transfer Function 5' */
                    
                    
                        boolean_T T200TransferFunction6_CSTATE[4]; /* '<S20>/T200 Transfer Function 6' */
                    
                    
                        boolean_T T200TransferFunction7_CSTATE[4]; /* '<S20>/T200 Transfer Function 7' */
                    
                    
                        boolean_T T200TransferFunction8_CSTATE[4]; /* '<S20>/T200 Transfer Function 8' */
                    
                    
                        boolean_T Integrator_CSTATE_e[6]; /* '<S19>/Integrator' */
                    
                    
                        boolean_T Integrator_CSTATE_i[6]; /* '<S1>/Integrator' */
                    
                    
                        boolean_T IntegratorSecondOrderLimited__a[6]; /* '<S41>/Integrator, Second-Order Limited' */
                    
            };            
                #ifndef ODE4_INTG
        #define ODE4_INTG
        /* ODE4 Integration Data */
        struct ODE4_IntgData {
        real_T *y; /* output */
        real_T *f[4]; /* derivatives */
        };
        #endif

                        /* Parameters (default storage) */
                struct P_sim_ROV_v0_R2018b_T_ {
                    




                    
                    


                        



                            
                            
                                   real_T B; /* Variable: B
  * Referenced by: '<S24>/Buoyancy'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T D_linear[36]; /* Variable: D_linear
  * Referenced by: '<S23>/Linear Damping'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T D_quadratic[36]; /* Variable: D_quadratic
  * Referenced by: '<S23>/Quadratic Damping'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T I[9]; /* Variable: I
  * Referenced by: '<S22>/Inertia Tensor'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Kq[36]; /* Variable: Kq
  * Referenced by: '<S1>/Gain1'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Kx[72]; /* Variable: Kx
  * Referenced by: '<S1>/Gain2'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T M_addedMass[36]; /* Variable: M_addedMass
  * Referenced by: '<S22>/Added Mass'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T TCM[48]; /* Variable: TCM
  * Referenced by: '<S2>/Thrust Configuration Matrix'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T W; /* Variable: W
  * Referenced by: '<S24>/Gravity Force'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T force[201]; /* Variable: force
  * Referenced by:
*   '<S7>/1-D Lookup Table'
*   '<S7>/Saturation'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T m; /* Variable: m
  * Referenced by: '<S22>/Rigid Body Mass'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T pwm[201]; /* Variable: pwm
  * Referenced by: '<S7>/1-D Lookup Table'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T r_b[3]; /* Variable: r_b
  * Referenced by: '<S24>/CoB'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T r_g[3]; /* Variable: r_g
  * Referenced by:
*   '<S17>/CoG'
*   '<S22>/CoM'
*   '<S24>/CoM'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Randombias_Ts; /* Mask Parameter: Randombias_Ts
  * Referenced by: '<S51>/Constant1'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Randombias_Ts_e; /* Mask Parameter: Randombias_Ts_e
  * Referenced by: '<S37>/Constant1'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisInertialMeasurementUni[3]; /* Mask Parameter: ThreeaxisInertialMeasurementUni
  * Referenced by: '<S34>/Measurement bias'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisAccelerometer_a_pow[3]; /* Mask Parameter: ThreeaxisAccelerometer_a_pow
  * Referenced by: '<S37>/Constant'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisAccelerometer_a_seeds[3]; /* Mask Parameter: ThreeaxisAccelerometer_a_seeds
  * Referenced by: '<S37>/White Noise'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisInertialMeasurementU_l[9]; /* Mask Parameter: ThreeaxisInertialMeasurementU_l
  * Referenced by: '<S34>/Scale factors & Cross-coupling  errors'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisInertialMeasurementU_n[3]; /* Mask Parameter: ThreeaxisInertialMeasurementU_n
  * Referenced by: '<S35>/Measurement bias'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisGyroscope_g_pow[3]; /* Mask Parameter: ThreeaxisGyroscope_g_pow
  * Referenced by: '<S51>/Constant'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisGyroscope_g_seeds[3]; /* Mask Parameter: ThreeaxisGyroscope_g_seeds
  * Referenced by: '<S51>/White Noise'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisInertialMeasurementU_p[3]; /* Mask Parameter: ThreeaxisInertialMeasurementU_p
  * Referenced by: '<S35>/g-sensitive bias'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisInertialMeasurementU_m[9]; /* Mask Parameter: ThreeaxisInertialMeasurementU_m
  * Referenced by: '<S35>/Scale factors & Cross-coupling  errors '
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisInertialMeasurementU_g[3]; /* Mask Parameter: ThreeaxisInertialMeasurementU_g
  * Referenced by: '<S34>/wl_ins'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisInertialMeasurementU_f; /* Mask Parameter: ThreeaxisInertialMeasurementU_f
  * Referenced by:
*   '<S41>/2*zeta * wn'
*   '<S41>/wn^2'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisInertialMeasurementU_h; /* Mask Parameter: ThreeaxisInertialMeasurementU_h
  * Referenced by:
*   '<S53>/2*zeta * wn'
*   '<S53>/wn^2'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisInertialMeasurement_gc; /* Mask Parameter: ThreeaxisInertialMeasurement_gc
  * Referenced by: '<S41>/2*zeta * wn'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ThreeaxisInertialMeasurementU_o; /* Mask Parameter: ThreeaxisInertialMeasurementU_o
  * Referenced by: '<S53>/2*zeta * wn'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Gain3_Gain; /* Expression: pi/180
  * Referenced by: '<S4>/Gain3'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator6_IC; /* Expression: 0
  * Referenced by: '<S30>/Integrator6'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator7_IC; /* Expression: 0
  * Referenced by: '<S30>/Integrator7'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator8_IC; /* Expression: 0
  * Referenced by: '<S30>/Integrator8'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator_IC; /* Expression: 0
  * Referenced by: '<S30>/Integrator'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator1_IC; /* Expression: 0
  * Referenced by: '<S30>/Integrator1'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator2_IC; /* Expression: 0
  * Referenced by: '<S30>/Integrator2'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator3_IC; /* Expression: 0
  * Referenced by: '<S30>/Integrator3'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator4_IC; /* Expression: 0
  * Referenced by: '<S30>/Integrator4'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator5_IC; /* Expression: 0
  * Referenced by: '<S30>/Integrator5'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T IntegratorSecondOrderLimited_IC; /* Expression: 0
  * Referenced by: '<S53>/Integrator, Second-Order Limited'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T IntegratorSecondOrderLimited__c; /* Expression: 0
  * Referenced by: '<S53>/Integrator, Second-Order Limited'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Constant_Value; /* Expression: dtype_g
  * Referenced by: '<S50>/Constant'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator_IC_m; /* Expression: 0
  * Referenced by: '<S18>/Integrator'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ZeroOrderHold_Gain; /* Expression: 1
  * Referenced by: '<S35>/Zero-Order Hold'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Inverseoftotalmass_Value[36]; /* Expression: inv(M_rigidBody+M_addedMass)
  * Referenced by: '<S18>/Inverse of total mass'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction1_A[4]; /* Computed Parameter: T200TransferFunction1_A
  * Referenced by: '<S20>/T200 Transfer Function 1'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction1_C[4]; /* Computed Parameter: T200TransferFunction1_C
  * Referenced by: '<S20>/T200 Transfer Function 1'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction2_A[4]; /* Computed Parameter: T200TransferFunction2_A
  * Referenced by: '<S20>/T200 Transfer Function 2'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction2_C[4]; /* Computed Parameter: T200TransferFunction2_C
  * Referenced by: '<S20>/T200 Transfer Function 2'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction3_A[4]; /* Computed Parameter: T200TransferFunction3_A
  * Referenced by: '<S20>/T200 Transfer Function 3'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction3_C[4]; /* Computed Parameter: T200TransferFunction3_C
  * Referenced by: '<S20>/T200 Transfer Function 3'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction4_A[4]; /* Computed Parameter: T200TransferFunction4_A
  * Referenced by: '<S20>/T200 Transfer Function 4'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction4_C[4]; /* Computed Parameter: T200TransferFunction4_C
  * Referenced by: '<S20>/T200 Transfer Function 4'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction5_A[4]; /* Computed Parameter: T200TransferFunction5_A
  * Referenced by: '<S20>/T200 Transfer Function 5'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction5_C[4]; /* Computed Parameter: T200TransferFunction5_C
  * Referenced by: '<S20>/T200 Transfer Function 5'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction6_A[4]; /* Computed Parameter: T200TransferFunction6_A
  * Referenced by: '<S20>/T200 Transfer Function 6'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction6_C[4]; /* Computed Parameter: T200TransferFunction6_C
  * Referenced by: '<S20>/T200 Transfer Function 6'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction7_A[4]; /* Computed Parameter: T200TransferFunction7_A
  * Referenced by: '<S20>/T200 Transfer Function 7'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction7_C[4]; /* Computed Parameter: T200TransferFunction7_C
  * Referenced by: '<S20>/T200 Transfer Function 7'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction8_A[4]; /* Computed Parameter: T200TransferFunction8_A
  * Referenced by: '<S20>/T200 Transfer Function 8'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T T200TransferFunction8_C[4]; /* Computed Parameter: T200TransferFunction8_C
  * Referenced by: '<S20>/T200 Transfer Function 8'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T lbfN_Gain; /* Expression: 4.45
  * Referenced by: '<S16>/lbf → N'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator_IC_j; /* Expression: 0
  * Referenced by: '<S19>/Integrator'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ZeroOrderHold1_Gain; /* Expression: 1
  * Referenced by: '<S35>/Zero-Order Hold1'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Switch_Threshold; /* Expression: 0.5
  * Referenced by: '<S50>/Switch'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T WhiteNoise_Mean; /* Expression: 0
  * Referenced by: '<S51>/White Noise'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T WhiteNoise_StdDev; /* Computed Parameter: WhiteNoise_StdDev
  * Referenced by: '<S51>/White Noise'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Saturation_UpperSat[3]; /* Expression: g_sath
  * Referenced by: '<S35>/Saturation'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Saturation_LowerSat[3]; /* Expression: g_satl
  * Referenced by: '<S35>/Saturation'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Integrator_IC_a; /* Expression: 0
  * Referenced by: '<S1>/Integrator'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ControlAllocation_Gain[48]; /* Expression: TCM'*inv(TCM*TCM')
  * Referenced by: '<S7>/Control Allocation'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Nkgf_Gain; /* Expression: 1/9.8
  * Referenced by: '<S7>/N → kgf'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ConstantReference_Value[6]; /* Expression: [0 0 5 0 0 0]
  * Referenced by: '<S4>/Constant Reference'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Gain_Gain[6]; /* Expression: [1 1 1 pi/180 pi/180 pi/180]
  * Referenced by: '<S4>/Gain'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Step_Time; /* Expression: 10
  * Referenced by: '<S4>/Step'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Step_Y0; /* Expression: 0
  * Referenced by: '<S4>/Step'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Step_YFinal; /* Expression: 5
  * Referenced by: '<S4>/Step'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Step1_Time; /* Expression: 60
  * Referenced by: '<S4>/Step1'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Step1_Y0; /* Expression: 0
  * Referenced by: '<S4>/Step1'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Step1_YFinal; /* Expression: 5
  * Referenced by: '<S4>/Step1'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Constant_Value_c; /* Expression: 0
  * Referenced by: '<S4>/Constant'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Gain1_Gain; /* Expression: pi/180
  * Referenced by: '<S4>/Gain1'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Gain2_Gain; /* Expression: pi/180
  * Referenced by: '<S4>/Gain2'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Step2_Time; /* Expression: 10
  * Referenced by: '<S4>/Step2'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Step2_Y0; /* Expression: 0
  * Referenced by: '<S4>/Step2'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Step2_YFinal; /* Expression: 90
  * Referenced by: '<S4>/Step2'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Step3_Time; /* Expression: 60
  * Referenced by: '<S4>/Step3'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Step3_Y0; /* Expression: 0
  * Referenced by: '<S4>/Step3'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Step3_YFinal; /* Expression: 90
  * Referenced by: '<S4>/Step3'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Saturation_UpperSat_f; /* Expression: 1900
  * Referenced by: '<S16>/Saturation'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Saturation_LowerSat_p; /* Expression: 1100
  * Referenced by: '<S16>/Saturation'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T DeadZone_Start; /* Expression: -10
  * Referenced by: '<S16>/Dead Zone'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T DeadZone_End; /* Expression: +10
  * Referenced by: '<S16>/Dead Zone'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T GravityAcceleration_Value[3]; /* Expression: [0 0 0]
  * Referenced by: '<S17>/Gravity Acceleration'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T IntegratorSecondOrderLimited__j; /* Expression: 0
  * Referenced by: '<S41>/Integrator, Second-Order Limited'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T IntegratorSecondOrderLimited__e; /* Expression: 0
  * Referenced by: '<S41>/Integrator, Second-Order Limited'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Constant_Value_b; /* Expression: dtype_a
  * Referenced by: '<S36>/Constant'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ZeroOrderHold1_Gain_m; /* Expression: 1
  * Referenced by: '<S34>/Zero-Order Hold1'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ZeroOrderHold2_Gain; /* Expression: 1
  * Referenced by: '<S34>/Zero-Order Hold2'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ZeroOrderHold_Gain_a; /* Expression: 1
  * Referenced by: '<S34>/Zero-Order Hold'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ZeroOrderHold4_Gain; /* Expression: 1
  * Referenced by: '<S34>/Zero-Order Hold4'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Gain_Gain_f[3]; /* Expression: [1 -1 1]
  * Referenced by: '<S34>/Gain'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T ZeroOrderHold3_Gain; /* Expression: 1
  * Referenced by: '<S34>/Zero-Order Hold3'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Switch_Threshold_j; /* Expression: 0.5
  * Referenced by: '<S36>/Switch'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T WhiteNoise_Mean_g; /* Expression: 0
  * Referenced by: '<S37>/White Noise'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T WhiteNoise_StdDev_j; /* Computed Parameter: WhiteNoise_StdDev_j
  * Referenced by: '<S37>/White Noise'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Saturation_UpperSat_e[3]; /* Expression: a_sath
  * Referenced by: '<S34>/Saturation'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   real_T Saturation_LowerSat_a[3]; /* Expression: a_satl
  * Referenced by: '<S34>/Saturation'
   */

                        
                        
                        


                    






                    
                    


                        



                            
                            
                                   uint8_T ManualSwitch_CurrentSetting; /* Computed Parameter: ManualSwitch_CurrentSetting
  * Referenced by: '<S4>/Manual Switch'
   */

                        
                        
                        


                    




                };

        


            /* Real-time Model Data Structure */
            
    struct tag_RTM_sim_ROV_v0_R2018b_T {
                    const char_T *errorStatus;
                    RTWLogInfo *rtwLogInfo;
        RTWExtModeInfo *extModeInfo;
        RTWSolverInfo solverInfo;
        X_sim_ROV_v0_R2018b_T *contStates;
                    int_T *periodicContStateIndices;
                    real_T *periodicContStateRanges;
                    real_T *derivs;
                    XDis_sim_ROV_v0_R2018b_T *contStateDisabled;
        boolean_T zCCacheNeedsReset;
                    boolean_T derivCacheNeedsReset;
                    boolean_T CTOutputIncnstWithState;
                    real_T odeY[71];
                    real_T odeF[4][71];
                    ODE4_IntgData intgData;

                        /*
        * Sizes:
                * The following substructure contains sizes information
        * for many of the model attributes such as inputs, outputs,
        * dwork, sample times, etc.
         */
 
    struct  {
                    uint32_T checksums[4];
                    int_T numContStates;
                    int_T numPeriodicContStates;
                    int_T numSampTimes;
            


    } Sizes;

                        /*
        * SpecialInfo:
                * The following substructure contains special information
        * related to other components that are dependent on RTW.
         */
 
    struct  {
                    const void *mappingInfo;



    } SpecialInfo;

                        /*
        * Timing:
                * The following substructure contains information regarding
        * the timing information for the model.
         */
 
    struct  {
                    uint32_T clockTick0;
                    uint32_T clockTickH0;
                    time_T stepSize0;
                    uint32_T clockTick1;
                    uint32_T clockTickH1;
                    uint32_T clockTick2;
                    uint32_T clockTickH2;
                        struct {
        uint8_T TID[3];
    }  TaskCounters;
        time_T tFinal;
                    SimTimeStep simTimeStep;
        boolean_T stopRequestedFlag;
                    time_T *t;
                    time_T tArray[3];
            


    } Timing;



            
    };





    

    

    
            /* Block parameters (default storage) */
                #ifdef __cplusplus
                extern "C" {
                    #endif
                        extern                 P_sim_ROV_v0_R2018b_T sim_ROV_v0_R2018b_P;



                #ifdef __cplusplus
            }
            #endif

            /* Block signals (default storage) */
                #ifdef __cplusplus
                extern "C" {
                    #endif
                        extern                 struct B_sim_ROV_v0_R2018b_T sim_ROV_v0_R2018b_B;



                #ifdef __cplusplus
            }
            #endif

            /* Continuous states (default storage) */
                        extern                 X_sim_ROV_v0_R2018b_T sim_ROV_v0_R2018b_X;




                /* Block states (default storage) */
                        extern                 struct DW_sim_ROV_v0_R2018b_T sim_ROV_v0_R2018b_DW;





    
        #ifdef __cplusplus 
extern "C"{ 
 #endif

            /* Model entry point functions */
                                        extern void sim_ROV_v0_R2018b_initialize(void);
                


                                                                extern void sim_ROV_v0_R2018b_step(void);
                        

                                        extern void sim_ROV_v0_R2018b_terminate(void);
                        #ifdef __cplusplus 
 } 
 #endif




    

    
                    /* Real-time Model object */

                        #ifdef __cplusplus
                        extern "C" {
                            #endif
                                extern                         RT_MODEL_sim_ROV_v0_R2018b_T *const sim_ROV_v0_R2018b_M;



                        #ifdef __cplusplus
                    }
                    #endif



    

    

    

            
    /*-
    * The generated code includes comments that allow you to trace directly
    * back to the appropriate location in the model.  The basic format
        * is <system>/block_name, where system is the system number (uniquely
        * assigned by Simulink) and block_name is the name of the block.
        *
        * Use the MATLAB hilite_system command to trace the generated code back
        * to the model.  For example,
        *
            * hilite_system('<S3>')    - opens system 3
            * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
        *
        * Here is the system hierarchy for this model
        *
            * '<Root>' : 'sim_ROV_v0_R2018b'
                * '<S1>'   : 'sim_ROV_v0_R2018b/Controller (LQR)'
                * '<S2>'   : 'sim_ROV_v0_R2018b/ROV (EVA)'
                * '<S3>'   : 'sim_ROV_v0_R2018b/Reference Generator'
                * '<S4>'   : 'sim_ROV_v0_R2018b/Reference Generator1'
                * '<S5>'   : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation'
                * '<S6>'   : 'sim_ROV_v0_R2018b/Visualization'
                * '<S7>'   : 'sim_ROV_v0_R2018b/Controller (LQR)/Control Allocation'
                * '<S8>'   : 'sim_ROV_v0_R2018b/Controller (LQR)/Errors'
                * '<S9>'   : 'sim_ROV_v0_R2018b/Controller (LQR)/Test'
                * '<S10>'  : 'sim_ROV_v0_R2018b/Controller (LQR)/Errors/Feedback (filtered)'
                * '<S11>'  : 'sim_ROV_v0_R2018b/Controller (LQR)/Errors/Reference Signals'
                * '<S12>'  : 'sim_ROV_v0_R2018b/Controller (LQR)/Test/Chirp'
                * '<S13>'  : 'sim_ROV_v0_R2018b/Controller (LQR)/Test/Impulse'
                * '<S14>'  : 'sim_ROV_v0_R2018b/Controller (LQR)/Test/Step'
                * '<S15>'  : 'sim_ROV_v0_R2018b/Controller (LQR)/Test/Chirp/Chirp Signal'
                * '<S16>'  : 'sim_ROV_v0_R2018b/ROV (EVA)/Actuators Dynamics'
                * '<S17>'  : 'sim_ROV_v0_R2018b/ROV (EVA)/Post-Processing'
                * '<S18>'  : 'sim_ROV_v0_R2018b/ROV (EVA)/Rigid Body Dynamics'
                * '<S19>'  : 'sim_ROV_v0_R2018b/ROV (EVA)/Rigid Body Kinematics'
                * '<S20>'  : 'sim_ROV_v0_R2018b/ROV (EVA)/Actuators Dynamics/Motors Transfer Functions'
                * '<S21>'  : 'sim_ROV_v0_R2018b/ROV (EVA)/Actuators Dynamics/Normalization'
                * '<S22>'  : 'sim_ROV_v0_R2018b/ROV (EVA)/Rigid Body Dynamics/Coriolis & Centripetal Forces'
                * '<S23>'  : 'sim_ROV_v0_R2018b/ROV (EVA)/Rigid Body Dynamics/Damping Forces'
                * '<S24>'  : 'sim_ROV_v0_R2018b/ROV (EVA)/Rigid Body Dynamics/Hydrostatics Forces'
                * '<S25>'  : 'sim_ROV_v0_R2018b/ROV (EVA)/Rigid Body Dynamics/Coriolis & Centripetal Forces/Added Coriolis & Centripetal'
                * '<S26>'  : 'sim_ROV_v0_R2018b/ROV (EVA)/Rigid Body Dynamics/Coriolis & Centripetal Forces/Rigid Body Coriolis & Centripetal'
                * '<S27>'  : 'sim_ROV_v0_R2018b/ROV (EVA)/Rigid Body Dynamics/Hydrostatics Forces/hydrostatics'
                * '<S28>'  : 'sim_ROV_v0_R2018b/ROV (EVA)/Rigid Body Kinematics/kinematics'
                * '<S29>'  : 'sim_ROV_v0_R2018b/Reference Generator/Step'
                * '<S30>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Internal Filter'
                * '<S31>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)'
                * '<S32>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit'
                * '<S33>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Acceleration Conversion'
                * '<S34>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer'
                * '<S35>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Gyroscope'
                * '<S36>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/Dynamics'
                * '<S37>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/Random bias'
                * '<S38>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/w x (w x d)'
                * '<S39>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/wdot x d'
                * '<S40>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/Dynamics/No Dynamics'
                * '<S41>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/Dynamics/Second-order Dynamics'
                * '<S42>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/w x (w x d)/w x (w x d)'
                * '<S43>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/w x (w x d)/w x d'
                * '<S44>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/w x (w x d)/w x (w x d)/Subsystem'
                * '<S45>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/w x (w x d)/w x (w x d)/Subsystem1'
                * '<S46>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/w x (w x d)/w x d/Subsystem'
                * '<S47>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/w x (w x d)/w x d/Subsystem1'
                * '<S48>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/wdot x d/Subsystem'
                * '<S49>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Accelerometer/wdot x d/Subsystem1'
                * '<S50>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Gyroscope/Dynamics'
                * '<S51>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Gyroscope/Random bias'
                * '<S52>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Gyroscope/Dynamics/No Dynamics'
                * '<S53>'  : 'sim_ROV_v0_R2018b/Sensor Data and State Estimation/Sensor (IMU)/Three-axis Inertial Measurement Unit/Three-axis Gyroscope/Dynamics/Second-order Dynamics'
                * '<S54>'  : 'sim_ROV_v0_R2018b/Visualization/6DoF Animation'
    */


    

    #endif /* RTW_HEADER_sim_ROV_v0_R2018b_h_ */
