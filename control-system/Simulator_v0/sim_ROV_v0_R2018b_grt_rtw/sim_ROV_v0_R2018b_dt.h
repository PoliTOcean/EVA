/*
* sim_ROV_v0_R2018b_dt.h
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

    #include "ext_types.h"




    /* data type size table */
    static uint_T rtDataTypeSizes[]{
        

                        sizeof(real_T),


                        sizeof(real32_T),


                        sizeof(int8_T),


                        sizeof(uint8_T),


                        sizeof(int16_T),


                        sizeof(uint16_T),


                        sizeof(int32_T),


                        sizeof(uint32_T),


                        sizeof(boolean_T),


                        sizeof(fcn_call_T),


                        sizeof(int_T),


                        sizeof(pointer_T),


                        sizeof(action_T),


                        2*sizeof(uint32_T),


                        sizeof(int32_T),


                        sizeof(dsp_simulink_LowpassFilter_si_T),


                        sizeof(uint_T),


                        sizeof(char_T),


                        sizeof(uchar_T),


                        sizeof(time_T)
    };

    /* data type name table */
    static const char_T * rtDataTypeNames[]{
        
                        "real_T",

                        "real32_T",

                        "int8_T",

                        "uint8_T",

                        "int16_T",

                        "uint16_T",

                        "int32_T",

                        "uint32_T",

                        "boolean_T",

                        "fcn_call_T",

                        "int_T",

                        "pointer_T",

                        "action_T",

                        "timer_uint32_pair_T",

                        "physical_connection",

                        "dsp_simulink_LowpassFilter_si_T",

                        "uint_T",

                        "char_T",

                        "uchar_T",

                        "time_T"
    };

    /* data type transitions for block I/O structure */
    static DataTypeTransition rtBTransitions[]{
        
                                        {(char_T *)(&sim_ROV_v0_R2018b_B.Integrator6), 0, 0,                        111}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_B.LowpassFilter5.LowpassFilter3), 0, 0,                        1}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_B.LowpassFilter4.LowpassFilter3), 0, 0,                        1}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_B.LowpassFilter3.LowpassFilter3), 0, 0,                        1}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_B.LowpassFilter2.LowpassFilter), 0, 0,                        1}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_B.LowpassFilter1.LowpassFilter), 0, 0,                        1}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_B.LowpassFilter.LowpassFilter), 0, 0,                        1}


        ,

                                        {(char_T *)(&sim_ROV_v0_R2018b_DW.NextOutput[0]), 0, 0,                        20}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.Scope_PWORK.LoggedData), 11, 0,                        13}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.sfEvent), 6, 0,                        5}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.RandSeed[0]), 7, 0,                        6}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited_MO[0]), 10, 0,                        6}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.is_active_c3_sim_ROV_v0_R2018b), 3, 0,                        5}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.IntegratorSecondOrderLimited_DW), 8, 0,                        7}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.LowpassFilter5.obj), 15, 0,                        1}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.LowpassFilter5.objisempty), 8, 0,                        2}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.LowpassFilter4.obj), 15, 0,                        1}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.LowpassFilter4.objisempty), 8, 0,                        2}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.LowpassFilter3.obj), 15, 0,                        1}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.LowpassFilter3.objisempty), 8, 0,                        2}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.LowpassFilter2.obj), 15, 0,                        1}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.LowpassFilter2.objisempty), 8, 0,                        2}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.LowpassFilter1.obj), 15, 0,                        1}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.LowpassFilter1.objisempty), 8, 0,                        2}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.LowpassFilter.obj), 15, 0,                        1}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_DW.LowpassFilter.objisempty), 8, 0,                        2}



    


    };

    /* data type transition table for block I/O structure */
    static DataTypeTransitionTable rtBTransTable{
                        26U,
        rtBTransitions

    };

    /* data type transitions for Parameters structure */
    static DataTypeTransition rtPTransitions[]{
                                                {(char_T *)(&sim_ROV_v0_R2018b_P.B), 0, 0,                        963}                        ,
{(char_T *)(&sim_ROV_v0_R2018b_P.ManualSwitch_CurrentSetting), 3, 0,                        1}

    };

    /* data type transition table for Parameters structure */
    static DataTypeTransitionTable rtPTransTable{
                        2U,
        rtPTransitions

    };

/* [EOF] sim_ROV_v0_R2018b_dt.h */
