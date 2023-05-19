/*
 * sim_ROV_v0_R2018b_private.h
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

#ifndef RTW_HEADER_sim_ROV_v0_R2018b_private_h_
#define RTW_HEADER_sim_ROV_v0_R2018b_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "sim_ROV_v0_R2018b.h"
#include "sim_ROV_v0_R2018b_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
extern void sim_ROV_v0_R_LowpassFilter_Init(DW_LowpassFilter_sim_ROV_v0_R_T
  *localDW);
extern void sim_ROV_v0_R2018b_LowpassFilter(real_T rtu_0,
  B_LowpassFilter_sim_ROV_v0_R2_T *localB, DW_LowpassFilter_sim_ROV_v0_R_T
  *localDW);
extern void sim_ROV_v0_R_LowpassFilter_Term(DW_LowpassFilter_sim_ROV_v0_R_T
  *localDW);

/* private model entry point functions */
extern void sim_ROV_v0_R2018b_derivatives(void);

#endif                             /* RTW_HEADER_sim_ROV_v0_R2018b_private_h_ */
