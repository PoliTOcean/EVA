/*
 * sim_ROV_v0_R2018b_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "sim_ROV_v0_R2018b".
 *
 * Model version              : 1.435
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C++ source code generated on : Fri Apr 21 14:16:52 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_sim_ROV_v0_R2018b_types_h_
#define RTW_HEADER_sim_ROV_v0_R2018b_types_h_
#include "rtwtypes.h"
#ifndef struct_b_dsp_FIRFilter_0_sim_ROV_v0__T
#define struct_b_dsp_FIRFilter_0_sim_ROV_v0__T

struct b_dsp_FIRFilter_0_sim_ROV_v0__T
{
  int32_T S0_isInitialized;
  real_T W0_states[3];
  real_T P0_InitialStates;
  real_T P1_Coefficients[4];
};

#endif                              /* struct_b_dsp_FIRFilter_0_sim_ROV_v0__T */

#ifndef struct_b_dspcodegen_FIRFilter_sim_RO_T
#define struct_b_dspcodegen_FIRFilter_sim_RO_T

struct b_dspcodegen_FIRFilter_sim_RO_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  b_dsp_FIRFilter_0_sim_ROV_v0__T cSFunObject;
};

#endif                              /* struct_b_dspcodegen_FIRFilter_sim_RO_T */

#ifndef struct_cell_wrap_sim_ROV_v0_R2018b_T
#define struct_cell_wrap_sim_ROV_v0_R2018b_T

struct cell_wrap_sim_ROV_v0_R2018b_T
{
  uint32_T f1[8];
};

#endif                                /* struct_cell_wrap_sim_ROV_v0_R2018b_T */

#ifndef struct_dsp_simulink_LowpassFilter_si_T
#define struct_dsp_simulink_LowpassFilter_si_T

struct dsp_simulink_LowpassFilter_si_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_sim_ROV_v0_R2018b_T inputVarSize;
  int32_T NumChannels;
  b_dspcodegen_FIRFilter_sim_RO_T *FilterObj;
  b_dspcodegen_FIRFilter_sim_RO_T _pobj0;
};

#endif                              /* struct_dsp_simulink_LowpassFilter_si_T */

/* Parameters (default storage) */
typedef struct P_sim_ROV_v0_R2018b_T_ P_sim_ROV_v0_R2018b_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_sim_ROV_v0_R2018b_T RT_MODEL_sim_ROV_v0_R2018b_T;

#endif                               /* RTW_HEADER_sim_ROV_v0_R2018b_types_h_ */
