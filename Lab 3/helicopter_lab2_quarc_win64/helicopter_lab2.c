/*
 * helicopter_lab2.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_lab2".
 *
 * Model version              : 11.5
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Thu Mar  9 11:45:26 2023
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter_lab2.h"
#include "helicopter_lab2_private.h"
#include "helicopter_lab2_dt.h"

/* Block signals (default storage) */
B_helicopter_lab2_T helicopter_lab2_B;

/* Continuous states */
X_helicopter_lab2_T helicopter_lab2_X;

/* Block states (default storage) */
DW_helicopter_lab2_T helicopter_lab2_DW;

/* Real-time model */
static RT_MODEL_helicopter_lab2_T helicopter_lab2_M_;
RT_MODEL_helicopter_lab2_T *const helicopter_lab2_M = &helicopter_lab2_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  helicopter_lab2_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter_lab2_output(void)
{
  /* local block i/o variables */
  real_T rtb_Derivative;
  real_T rtb_Frontgain;
  real_T rtb_Clock;
  real_T rtb_Backgain;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_Clock_tmp;
  real_T rtb_K_pp;
  real_T *lastU;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopter_lab2_M)) {
    /* set solver stop time */
    if (!(helicopter_lab2_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter_lab2_M->solverInfo,
                            ((helicopter_lab2_M->Timing.clockTickH0 + 1) *
        helicopter_lab2_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter_lab2_M->solverInfo,
                            ((helicopter_lab2_M->Timing.clockTick0 + 1) *
        helicopter_lab2_M->Timing.stepSize0 +
        helicopter_lab2_M->Timing.clockTickH0 *
        helicopter_lab2_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter_lab2_M)) {
    helicopter_lab2_M->Timing.t[0] = rtsiGetT(&helicopter_lab2_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopter_lab2_DW.IfActionSubsystem_SubsysRanBC);
  if (rtmIsMajorTimeStep(helicopter_lab2_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter_lab2/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopter_lab2_DW.HILReadEncoderTimebase_Task, 1,
         &helicopter_lab2_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter_lab2_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter_lab2_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter_lab2_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopter_lab2_B.TravelCounttorad = helicopter_lab2_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter_lab2_P.TravelCounttorad_Gain;

    /* Gain: '<S12>/Gain' */
    helicopter_lab2_B.Gain = helicopter_lab2_P.Gain_Gain *
      helicopter_lab2_B.TravelCounttorad;

    /* Sum: '<Root>/Sum5' incorporates:
     *  Constant: '<Root>/Constant'
     */
    helicopter_lab2_B.Traveldeg = helicopter_lab2_P.Constant_Value +
      helicopter_lab2_B.Gain;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopter_lab2_B.PitchCounttorad = helicopter_lab2_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    helicopter_lab2_B.Gain_i = helicopter_lab2_P.Gain_Gain_a *
      helicopter_lab2_B.PitchCounttorad;
  }

  /* Clock: '<S3>/Clock' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  rtb_Clock = 0.0;
  rtb_Clock += helicopter_lab2_P.TravelTransferFcn_C *
    helicopter_lab2_X.TravelTransferFcn_CSTATE;
  rtb_Clock += helicopter_lab2_P.TravelTransferFcn_D *
    helicopter_lab2_B.TravelCounttorad;

  /* Gain: '<S13>/Gain' */
  helicopter_lab2_B.Gain_d = helicopter_lab2_P.Gain_Gain_l * rtb_Clock;

  /* Clock: '<S3>/Clock' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  rtb_Clock = 0.0;
  rtb_Clock += helicopter_lab2_P.PitchTransferFcn_C *
    helicopter_lab2_X.PitchTransferFcn_CSTATE;
  rtb_Clock += helicopter_lab2_P.PitchTransferFcn_D *
    helicopter_lab2_B.PitchCounttorad;

  /* Gain: '<S10>/Gain' */
  helicopter_lab2_B.Gain_b = helicopter_lab2_P.Gain_Gain_ae * rtb_Clock;
  if (rtmIsMajorTimeStep(helicopter_lab2_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopter_lab2_B.ElevationCounttorad = helicopter_lab2_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopter_lab2_P.ElevationCounttorad_Gain;

    /* Gain: '<S7>/Gain' */
    helicopter_lab2_B.Gain_e = helicopter_lab2_P.Gain_Gain_lv *
      helicopter_lab2_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter_lab2_B.Sum = helicopter_lab2_B.Gain_e +
      helicopter_lab2_P.elavation_offsetdeg_Value;
  }

  /* Clock: '<S3>/Clock' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  rtb_Clock = 0.0;
  rtb_Clock += helicopter_lab2_P.ElevationTransferFcn_C *
    helicopter_lab2_X.ElevationTransferFcn_CSTATE;
  rtb_Clock += helicopter_lab2_P.ElevationTransferFcn_D *
    helicopter_lab2_B.ElevationCounttorad;

  /* Gain: '<S8>/Gain' */
  helicopter_lab2_B.Gain_dg = helicopter_lab2_P.Gain_Gain_n * rtb_Clock;

  /* Gain: '<S2>/Gain1' */
  helicopter_lab2_B.Gain1[0] = helicopter_lab2_P.Gain1_Gain *
    helicopter_lab2_B.Traveldeg;
  helicopter_lab2_B.Gain1[1] = helicopter_lab2_P.Gain1_Gain *
    helicopter_lab2_B.Gain_d;
  helicopter_lab2_B.Gain1[2] = helicopter_lab2_P.Gain1_Gain *
    helicopter_lab2_B.Gain_i;
  helicopter_lab2_B.Gain1[3] = helicopter_lab2_P.Gain1_Gain *
    helicopter_lab2_B.Gain_b;
  helicopter_lab2_B.Gain1[4] = helicopter_lab2_P.Gain1_Gain *
    helicopter_lab2_B.Sum;
  helicopter_lab2_B.Gain1[5] = helicopter_lab2_P.Gain1_Gain *
    helicopter_lab2_B.Gain_dg;
  if (rtmIsMajorTimeStep(helicopter_lab2_M)) {
  }

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_lab2_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_lab2_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_lab2_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter_lab2_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[220]) {
      currTimeIndex = 219;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_lab2_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          helicopter_lab2_B.FromWorkspace1 = pDataValues[currTimeIndex];
        } else {
          helicopter_lab2_B.FromWorkspace1 = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        helicopter_lab2_B.FromWorkspace1 = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 221;
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace2' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_lab2_DW.FromWorkspace2_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_lab2_DW.FromWorkspace2_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_lab2_DW.FromWorkspace2_IWORK.PrevIndex;
    real_T t = helicopter_lab2_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[220]) {
      currTimeIndex = 219;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_lab2_DW.FromWorkspace2_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Clock = pDataValues[currTimeIndex];
        } else {
          rtb_Clock = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Clock = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 221;
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace3' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_lab2_DW.FromWorkspace3_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_lab2_DW.FromWorkspace3_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_lab2_DW.FromWorkspace3_IWORK.PrevIndex;
    real_T t = helicopter_lab2_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[220]) {
      currTimeIndex = 219;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_lab2_DW.FromWorkspace3_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Derivative = pDataValues[currTimeIndex];
        } else {
          rtb_Derivative = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Derivative = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 221;
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace4' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_lab2_DW.FromWorkspace4_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_lab2_DW.FromWorkspace4_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_lab2_DW.FromWorkspace4_IWORK.PrevIndex;
    real_T t = helicopter_lab2_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[220]) {
      currTimeIndex = 219;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_lab2_DW.FromWorkspace4_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Frontgain = pDataValues[currTimeIndex];
        } else {
          rtb_Frontgain = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Frontgain = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 221;
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace5' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_lab2_DW.FromWorkspace5_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_lab2_DW.FromWorkspace5_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_lab2_DW.FromWorkspace5_IWORK.PrevIndex;
    real_T t = helicopter_lab2_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[220]) {
      currTimeIndex = 219;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_lab2_DW.FromWorkspace5_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Backgain = pDataValues[currTimeIndex];
        } else {
          rtb_Backgain = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Backgain = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 221;
      }
    }
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Gain: '<Root>/Gain'
   *  Sum: '<Root>/Sum4'
   */
  rtb_Backgain = (((helicopter_lab2_B.Gain1[0] - rtb_Clock) *
                   helicopter_lab2_P.K[0] + (helicopter_lab2_B.Gain1[1] -
    rtb_Derivative) * helicopter_lab2_P.K[1]) + (helicopter_lab2_B.Gain1[2] -
    rtb_Frontgain) * helicopter_lab2_P.K[2]) + (helicopter_lab2_B.Gain1[3] -
    rtb_Backgain) * helicopter_lab2_P.K[3];

  /* Sum: '<Root>/Sum3' */
  helicopter_lab2_B.Sum3 = helicopter_lab2_B.FromWorkspace1 - rtb_Backgain;
  if (rtmIsMajorTimeStep(helicopter_lab2_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S5>/Sum2'
   */
  rtb_Backgain = helicopter_lab2_B.Sum3 - helicopter_lab2_B.Gain1[2];

  /* Gain: '<S5>/K_pp' */
  rtb_K_pp = helicopter_lab2_P.K_pp * rtb_Backgain;

  /* Gain: '<S1>/Back gain' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S5>/K_pd'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<S5>/Sum3'
   */
  rtb_Backgain = helicopter_lab2_P.K_pd * helicopter_lab2_B.Gain1[3];
  rtb_Backgain = (rtb_K_pp - rtb_Backgain) + helicopter_lab2_P.Vd_ff;

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter_lab2_X.Integrator_CSTATE >=
      helicopter_lab2_P.Integrator_UpperSat) {
    helicopter_lab2_X.Integrator_CSTATE = helicopter_lab2_P.Integrator_UpperSat;
  } else {
    if (helicopter_lab2_X.Integrator_CSTATE <=
        helicopter_lab2_P.Integrator_LowerSat) {
      helicopter_lab2_X.Integrator_CSTATE =
        helicopter_lab2_P.Integrator_LowerSat;
    }
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Integrator: '<S3>/Integrator'
   */
  rtb_Frontgain = helicopter_lab2_X.Integrator_CSTATE;

  /* Derivative: '<S4>/Derivative' incorporates:
   *  Constant: '<Root>/elevation_ref'
   *  Sum: '<S3>/Sum'
   */
  rtb_Derivative = helicopter_lab2_P.elevation_ref_Value -
    helicopter_lab2_B.Gain1[4];

  /* Clock: '<S3>/Clock' incorporates:
   *  Gain: '<S3>/K_ed'
   */
  rtb_Clock = helicopter_lab2_P.K_ed * helicopter_lab2_B.Gain1[5];

  /* Gain: '<S1>/Front gain' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ep'
   *  Sum: '<Root>/Sum2'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Frontgain = ((helicopter_lab2_P.K_ep * rtb_Derivative + rtb_Frontgain) -
                   rtb_Clock) + helicopter_lab2_P.Vs_ff;

  /* Sum: '<S1>/Add' */
  rtb_K_pp = rtb_Backgain + rtb_Frontgain;

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Backgain = (rtb_Frontgain - rtb_Backgain) *
    helicopter_lab2_P.Backgain_Gain;

  /* Gain: '<S1>/Front gain' */
  rtb_Frontgain = helicopter_lab2_P.Frontgain_Gain * rtb_K_pp;

  /* Clock: '<S3>/Clock' incorporates:
   *  Derivative: '<S4>/Derivative'
   */
  rtb_Clock_tmp = helicopter_lab2_M->Timing.t[0];

  /* Clock: '<S3>/Clock' */
  rtb_Clock = rtb_Clock_tmp;

  /* If: '<S3>/If' incorporates:
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S6>/In1'
   */
  if (rtmIsMajorTimeStep(helicopter_lab2_M)) {
    rtAction = (int8_T)!(rtb_Clock >= 2.0);
    helicopter_lab2_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopter_lab2_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    helicopter_lab2_B.In1 = helicopter_lab2_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopter_lab2_M)) {
      srUpdateBC(helicopter_lab2_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */
  if (rtmIsMajorTimeStep(helicopter_lab2_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((helicopter_lab2_DW.TimeStampA >= rtb_Clock_tmp) &&
      (helicopter_lab2_DW.TimeStampB >= rtb_Clock_tmp)) {
    /* Derivative: '<S4>/Derivative' */
    rtb_Derivative = 0.0;
  } else {
    rtb_K_pp = helicopter_lab2_DW.TimeStampA;
    lastU = &helicopter_lab2_DW.LastUAtTimeA;
    if (helicopter_lab2_DW.TimeStampA < helicopter_lab2_DW.TimeStampB) {
      if (helicopter_lab2_DW.TimeStampB < rtb_Clock_tmp) {
        rtb_K_pp = helicopter_lab2_DW.TimeStampB;
        lastU = &helicopter_lab2_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_lab2_DW.TimeStampA >= rtb_Clock_tmp) {
        rtb_K_pp = helicopter_lab2_DW.TimeStampB;
        lastU = &helicopter_lab2_DW.LastUAtTimeB;
      }
    }

    /* Derivative: '<S4>/Derivative' */
    rtb_Derivative = (helicopter_lab2_B.PitchCounttorad - *lastU) /
      (rtb_Clock_tmp - rtb_K_pp);
  }

  /* Gain: '<S11>/Gain' */
  helicopter_lab2_B.Gain_l = helicopter_lab2_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter_lab2_M)) {
  }

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Backgain > helicopter_lab2_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_lab2_B.BackmotorSaturation =
      helicopter_lab2_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Backgain < helicopter_lab2_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_lab2_B.BackmotorSaturation =
      helicopter_lab2_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_lab2_B.BackmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_lab2_M)) {
  }

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Frontgain > helicopter_lab2_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_lab2_B.FrontmotorSaturation =
      helicopter_lab2_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Frontgain < helicopter_lab2_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_lab2_B.FrontmotorSaturation =
      helicopter_lab2_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_lab2_B.FrontmotorSaturation = rtb_Frontgain;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_lab2_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter_lab2/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter_lab2_DW.HILWriteAnalog_Buffer[0] =
        helicopter_lab2_B.FrontmotorSaturation;
      helicopter_lab2_DW.HILWriteAnalog_Buffer[1] =
        helicopter_lab2_B.BackmotorSaturation;
      result = hil_write_analog(helicopter_lab2_DW.HILInitialize_Card,
        helicopter_lab2_P.HILWriteAnalog_channels, 2,
        &helicopter_lab2_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter_lab2_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter_lab2_DW.TimeStampA == (rtInf)) {
    helicopter_lab2_DW.TimeStampA = helicopter_lab2_M->Timing.t[0];
    lastU = &helicopter_lab2_DW.LastUAtTimeA;
  } else if (helicopter_lab2_DW.TimeStampB == (rtInf)) {
    helicopter_lab2_DW.TimeStampB = helicopter_lab2_M->Timing.t[0];
    lastU = &helicopter_lab2_DW.LastUAtTimeB;
  } else if (helicopter_lab2_DW.TimeStampA < helicopter_lab2_DW.TimeStampB) {
    helicopter_lab2_DW.TimeStampA = helicopter_lab2_M->Timing.t[0];
    lastU = &helicopter_lab2_DW.LastUAtTimeA;
  } else {
    helicopter_lab2_DW.TimeStampB = helicopter_lab2_M->Timing.t[0];
    lastU = &helicopter_lab2_DW.LastUAtTimeB;
  }

  *lastU = helicopter_lab2_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter_lab2_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter_lab2_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++helicopter_lab2_M->Timing.clockTick0)) {
    ++helicopter_lab2_M->Timing.clockTickH0;
  }

  helicopter_lab2_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopter_lab2_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++helicopter_lab2_M->Timing.clockTick1)) {
      ++helicopter_lab2_M->Timing.clockTickH1;
    }

    helicopter_lab2_M->Timing.t[1] = helicopter_lab2_M->Timing.clockTick1 *
      helicopter_lab2_M->Timing.stepSize1 +
      helicopter_lab2_M->Timing.clockTickH1 *
      helicopter_lab2_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter_lab2_derivatives(void)
{
  XDot_helicopter_lab2_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopter_lab2_T *) helicopter_lab2_M->derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_lab2_P.TravelTransferFcn_A *
    helicopter_lab2_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_lab2_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_lab2_P.PitchTransferFcn_A *
    helicopter_lab2_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_lab2_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_lab2_P.ElevationTransferFcn_A *
    helicopter_lab2_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter_lab2_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter_lab2_X.Integrator_CSTATE <=
          helicopter_lab2_P.Integrator_LowerSat);
  usat = (helicopter_lab2_X.Integrator_CSTATE >=
          helicopter_lab2_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter_lab2_B.In1 > 0.0)) || (usat &&
       (helicopter_lab2_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter_lab2_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter_lab2_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_lab2/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter_lab2_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter_lab2_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter_lab2_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
      return;
    }

    if ((helicopter_lab2_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopter_lab2_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter_lab2_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopter_lab2_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter_lab2_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter_lab2_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(helicopter_lab2_DW.HILInitialize_Card,
        helicopter_lab2_P.HILInitialize_AIChannels, 8U,
        &helicopter_lab2_DW.HILInitialize_AIMinimums[0],
        &helicopter_lab2_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_lab2_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopter_lab2_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter_lab2_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopter_lab2_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter_lab2_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter_lab2_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopter_lab2_DW.HILInitialize_Card,
         helicopter_lab2_P.HILInitialize_AOChannels, 8U,
         &helicopter_lab2_DW.HILInitialize_AOMinimums[0],
         &helicopter_lab2_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_lab2_P.HILInitialize_AOStart && !is_switching) ||
        (helicopter_lab2_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_lab2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_lab2_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopter_lab2_DW.HILInitialize_Card,
        helicopter_lab2_P.HILInitialize_AOChannels, 8U,
        &helicopter_lab2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_lab2_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_lab2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_lab2_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter_lab2_DW.HILInitialize_Card,
         helicopter_lab2_P.HILInitialize_AOChannels, 8U,
         &helicopter_lab2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_lab2_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopter_lab2_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter_lab2_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter_lab2_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopter_lab2_DW.HILInitialize_Card,
         helicopter_lab2_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopter_lab2_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_lab2_P.HILInitialize_EIStart && !is_switching) ||
        (helicopter_lab2_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter_lab2_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopter_lab2_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopter_lab2_DW.HILInitialize_Card,
        helicopter_lab2_P.HILInitialize_EIChannels, 8U,
        &helicopter_lab2_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_lab2_P.HILInitialize_POPStart && !is_switching) ||
        (helicopter_lab2_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_lab2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_lab2_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopter_lab2_DW.HILInitialize_Card,
        helicopter_lab2_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopter_lab2_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopter_lab2_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &helicopter_lab2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopter_lab2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            helicopter_lab2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopter_lab2_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopter_lab2_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            helicopter_lab2_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] = helicopter_lab2_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter_lab2_DW.HILInitialize_Card,
          &helicopter_lab2_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &helicopter_lab2_DW.HILInitialize_POSortedFreqs
          [0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter_lab2_DW.HILInitialize_Card,
          &helicopter_lab2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter_lab2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_lab2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_lab2_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopter_lab2_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter_lab2_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter_lab2_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter_lab2_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter_lab2_DW.HILInitialize_Card,
        helicopter_lab2_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &helicopter_lab2_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter_lab2_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter_lab2_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopter_lab2_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopter_lab2_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter_lab2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_lab2_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopter_lab2_DW.HILInitialize_Card,
        helicopter_lab2_P.HILInitialize_POChannels, 8U,
        &helicopter_lab2_DW.HILInitialize_POSortedFreqs[0],
        &helicopter_lab2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_lab2_P.HILInitialize_POStart && !is_switching) ||
        (helicopter_lab2_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_lab2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_lab2_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopter_lab2_DW.HILInitialize_Card,
        helicopter_lab2_P.HILInitialize_POChannels, 8U,
        &helicopter_lab2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_lab2_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_lab2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_lab2_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter_lab2_DW.HILInitialize_Card,
         helicopter_lab2_P.HILInitialize_POChannels, 8U,
         &helicopter_lab2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter_lab2/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopter_lab2_DW.HILInitialize_Card,
       helicopter_lab2_P.HILReadEncoderTimebase_SamplesI,
       helicopter_lab2_P.HILReadEncoderTimebase_Channels, 3,
       &helicopter_lab2_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopter_lab2_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (helicopter_lab2_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
    }
  }

  /* Start for FromWorkspace: '<Root>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0, 35.25, 35.5, 35.75, 36.0,
      36.25, 36.5, 36.75, 37.0, 37.25, 37.5, 37.75, 38.0, 38.25, 38.5, 38.75,
      39.0, 39.25, 39.5, 39.75, 40.0, 40.25, 40.5, 40.75, 41.0, 41.25, 41.5,
      41.75, 42.0, 42.25, 42.5, 42.75, 43.0, 43.25, 43.5, 43.75, 44.0, 44.25,
      44.5, 44.75, 45.0, 45.25, 45.5, 45.75, 46.0, 46.25, 46.5, 46.75, 47.0,
      47.25, 47.5, 47.75, 48.0, 48.25, 48.5, 48.75, 49.0, 49.25, 49.5, 49.75,
      50.0, 50.25, 50.5, 50.75, 51.0, 51.25, 51.5, 51.75, 52.0, 52.25, 52.5,
      52.75, 53.0, 53.25, 53.5, 53.75, 54.0, 54.25, 54.5, 54.75, 55.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877560561874, 0.52359877560243773,
      0.52359877559967882, 0.52359877560176293, 0.52359877560250567,
      0.52359877559879708, 0.523598775601886, 0.48789589211690976,
      0.34971187068198772, 0.22862453939368321, 0.12361824412228262,
      0.033621435678587663, -0.042474371213739148, -0.10579616716527829,
      -0.1574723836113574, -0.19861769233059073, -0.23031990327360963,
      -0.25362901646162456, -0.2695483693600485, -0.27902775197638452,
      -0.28295832332992721, -0.282169144438834, -0.2774251374368274,
      -0.26942628311931704, -0.25880787701330971, -0.24614167493421862,
      -0.2319377716052306, -0.21664706939463596, -0.20066420798890355,
      -0.18433083946977491, -0.16793914653320974, -0.1517355142929353,
      -0.13592427812631835, -0.12067148126441607, -0.10610858625019387,
      -0.092336093964110078, -0.07942703263727624, -0.0674302871475923,
      -0.056373745943501641, -0.046267249192563642, -0.0371053272442784,
      -0.028869723270250169, -0.02153169804541244, -0.015054118309729803,
      -0.0093933330500299839, -0.0045008444163011641, -0.00032478188550688625,
      0.0031888102427672926, 0.0060948608437053631, 0.0084483235272315715,
      0.0103033793675813, 0.011712778199718943, 0.012727305885465223,
      0.013395365138720638, 0.013762657834992087, 0.013871957186847195,
      0.013762958718040452, 0.013472199591795242, 0.01303303652261667,
      0.012475673208138915, 0.011827228942350554, 0.011111840800780426,
      0.010350792510642193, 0.0095626638251978813, 0.0087634949041146548,
      0.0079669608543352366, 0.007184552204344663, 0.0064257576653433679,
      0.00569824607345959, 0.0050080449064697774, 0.0043597132260854154,
      0.00375650731295063, 0.0032005376369405036, 0.0026929161415080172,
      0.0022338931194832989, 0.0018229832210291397, 0.0014590803648616424,
      0.0011405615241664169, 0.00086537953202614482, 0.000631145201325567,
      0.00043519918545331659, 0.0002746741243856432, 0.00014654773359501494,
      4.7687611652746931E-5, -2.51113174962736E-5, -7.5095625605481331E-5,
      -0.00010552709432021246, -0.00011965954800363665, -0.00012071641349342688,
      -0.00011186568160814758, -9.6187572839689928E-5, -7.6628292929425967E-5,
      -5.5930824064076567E-5, -3.653115928026196E-5, -2.0407226918428556E-5,
      -8.87193000354003E-6, -2.3207706419947627E-6, 2.2423174428354287E-12,
      2.2422064205329661E-12, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_lab2_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_lab2_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_lab2_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace2' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0, 35.25, 35.5, 35.75, 36.0,
      36.25, 36.5, 36.75, 37.0, 37.25, 37.5, 37.75, 38.0, 38.25, 38.5, 38.75,
      39.0, 39.25, 39.5, 39.75, 40.0, 40.25, 40.5, 40.75, 41.0, 41.25, 41.5,
      41.75, 42.0, 42.25, 42.5, 42.75, 43.0, 43.25, 43.5, 43.75, 44.0, 44.25,
      44.5, 44.75, 45.0, 45.25, 45.5, 45.75, 46.0, 46.25, 46.5, 46.75, 47.0,
      47.25, 47.5, 47.75, 48.0, 48.25, 48.5, 48.75, 49.0, 49.25, 49.5, 49.75,
      50.0, 50.25, 50.5, 50.75, 51.0, 51.25, 51.5, 51.75, 52.0, 52.25, 52.5,
      52.75, 53.0, 53.25, 53.5, 53.75, 54.0, 54.25, 54.5, 54.75, 55.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1378421413628796,
      3.1262155534590508, 3.1033093000312753, 3.0666274151926292,
      3.014453922395651, 2.9456562771196104, 2.8595077632954782,
      2.7558073259615177, 2.6355434416064383, 2.5007315960809082,
      2.3540419646005355, 2.1984466981367543, 2.0369525052709658,
      1.8724212606771795, 1.70746165134267, 1.5443722376840752,
      1.3851193897200611, 1.2313377619747634, 1.084344677034049,
      0.94516260709943922, 0.81454593599937186, 0.69300953525459641,
      0.58085758134157262, 0.4782116243499428, 0.38503729687455357,
      0.30116929848631241, 0.22633445299366967, 0.16017274341930116,
      0.10225630243745035, 0.0521063860116434, 0.0092083926790348346,
      -0.026974984917693443, -0.056992373034600988, -0.081393980110083461,
      -0.10072338928314997, -0.11551075563777662, -0.12626728283685437,
      -0.13348085509340527, -0.13761270339363377, -0.13909498918597024,
      -0.13832919408585967, -0.13568521025758057, -0.13150103280621078,
      -0.12608296255207607, -0.11970623480413517, -0.11261599705906473,
      -0.10502856581238532, -0.097132899778658077, -0.089092233701274892,
      -0.081045823524040772, -0.073110759948836535, -0.065383813279096856,
      -0.057943277923115745, -0.050850789988729807, -0.044153096035537014,
      -0.037883755262336727, -0.032064761202882382, -0.026708072393367165,
      -0.021817044476218284, -0.017387758834953089, -0.013410245135285638,
      -0.0098695971009826, -0.0067469825029098946, -0.0040205497106447548,
      -0.0016662342724360706, 0.00034153012458697707, 0.0020291912825299574,
      0.0034235431819580023, 0.0045512698710344478, 0.0054385625005659976,
      0.006110803379750702, 0.0065923109598145643, 0.0069061397719682423,
      0.0070739295367997371, 0.0071157979105585792, 0.0070502716269881137,
      0.0068942511204199966, 0.0066630040664217216, 0.0063701836417806778,
      0.0060278676780718453, 0.0056466152557060282, 0.0052355376521854248,
      0.0048023809139604605, 0.0043536176608643395, 0.0038945460508059537,
      0.0034293941251199531, 0.0029614280156192506, 0.0024930627148619109,
      0.0020259742800656116, 0.0015612124415638952, 0.0010993125938950771,
      0.0006404060254672746, 0.00018432694173208815, -0.00026928570489996481,
      -0.00072089440885930365, -0.0011709813238870604, -0.0016199838401650167,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    } ;

    helicopter_lab2_DW.FromWorkspace2_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_lab2_DW.FromWorkspace2_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_lab2_DW.FromWorkspace2_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace3' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0, 35.25, 35.5, 35.75, 36.0,
      36.25, 36.5, 36.75, 37.0, 37.25, 37.5, 37.75, 38.0, 38.25, 38.5, 38.75,
      39.0, 39.25, 39.5, 39.75, 40.0, 40.25, 40.5, 40.75, 41.0, 41.25, 41.5,
      41.75, 42.0, 42.25, 42.5, 42.75, 43.0, 43.25, 43.5, 43.75, 44.0, 44.25,
      44.5, 44.75, 45.0, 45.25, 45.5, 45.75, 46.0, 46.25, 46.5, 46.75, 47.0,
      47.25, 47.5, 47.75, 48.0, 48.25, 48.5, 48.75, 49.0, 49.25, 49.5, 49.75,
      50.0, 50.25, 50.5, 50.75, 51.0, 51.25, 51.5, 51.75, 52.0, 52.25, 52.5,
      52.75, 53.0, 53.25, 53.5, 53.75, 54.0, 54.25, 54.5, 54.75, 55.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.01500204890656333,
      -0.046506351616179109, -0.091625013709456624, -0.14672753935569904,
      -0.20869397118820723, -0.27519058110691275, -0.34459405529640907,
      -0.41480174933452263, -0.48105553742129337, -0.53924738210369716,
      -0.58675852592175626, -0.62238106585451269, -0.6459767714626985,
      -0.65812497837516559, -0.659838437337216, -0.65235765463537054,
      -0.63701139185646583, -0.61512651098007154, -0.58797233976318208,
      -0.55672827973842087, -0.52246668440016464, -0.4861456029790247,
      -0.448607815652071, -0.4105838279663982, -0.37269730990166317,
      -0.33547199355304, -0.29933938197059484, -0.26464683829742924,
      -0.23166576392741245, -0.20059966570318619, -0.17159197333043966,
      -0.14473351038684309, -0.12006955246778667, -0.097606428301749162,
      -0.077317636692324332, -0.059149465418467453, -0.043026108796262758,
      -0.028854289026261422, -0.016527393200825153, -0.0059291431693221566,
      0.0030631804004240485, 0.010575935313022101, 0.016736709805491516,
      0.021672281016505684, 0.0255069109917853, 0.02836095098028896,
      0.030349724986739629, 0.031582664134881734, 0.032162664309489712,
      0.03218564070897284, 0.031740254300854573, 0.030907786678922008,
      0.029762141423938078, 0.028369951737531367, 0.026790775812789543,
      0.025077363092780035, 0.023275976237823973, 0.021426755238051147,
      0.019564111668596267, 0.017717142565056784, 0.015910054798669547,
      0.014162592137211633, 0.012490458392291244, 0.010905731169060752,
      0.00941726175283719, 0.0080310575880885166, 0.0067506446317744436,
      0.0055774075977103616, 0.0045109067563033848, 0.0035491705181318017,
      0.0026889635167396393, 0.0019260303202602554, 0.0012553152486133971,
      0.00067115905932383843, 0.00016747349503473769, -0.0002621051342807392,
      -0.000624082026274541, -0.00092498821599404791, -0.0011712816985660695,
      -0.0013692638548292639, -0.0015250096894597904, -0.0016443104140825373,
      -0.0017326269529012465, -0.0017950530123850362, -0.0018362864402340882,
      -0.0018606077027435496, -0.0018718644380027933, -0.0018734612030289807,
      -0.0018683537391858392, -0.001859047354006321, -0.0018475993906754695,
      -0.0018356262737114278, -0.0018243163349405144, -0.0018144505865283504,
      -0.0018064348158372005, -0.0018003476601109931, -0.0017960100651118315,
      -0.0017930800755657408, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_lab2_DW.FromWorkspace3_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_lab2_DW.FromWorkspace3_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_lab2_DW.FromWorkspace3_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace4' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0, 35.25, 35.5, 35.75, 36.0,
      36.25, 36.5, 36.75, 37.0, 37.25, 37.5, 37.75, 38.0, 38.25, 38.5, 38.75,
      39.0, 39.25, 39.5, 39.75, 40.0, 40.25, 40.5, 40.75, 41.0, 41.25, 41.5,
      41.75, 42.0, 42.25, 42.5, 42.75, 43.0, 43.25, 43.5, 43.75, 44.0, 44.25,
      44.5, 44.75, 45.0, 45.25, 45.5, 45.75, 46.0, 46.25, 46.5, 46.75, 47.0,
      47.25, 47.5, 47.75, 48.0, 48.25, 48.5, 48.75, 49.0, 49.25, 49.5, 49.75,
      50.0, 50.25, 50.5, 50.75, 51.0, 51.25, 51.5, 51.75, 52.0, 52.25, 52.5,
      52.75, 53.0, 53.25, 53.5, 53.75, 54.0, 54.25, 54.5, 54.75, 55.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.10602875206157947,
      0.22266037932492488, 0.31888147181824933, 0.3894436063137956,
      0.43795507377952358, 0.46997264230631586, 0.49051724877798242,
      0.49620116751189258, 0.46825647032084605, 0.41127773340780038,
      0.3357906189114076, 0.25176650717163274, 0.16676543549643508,
      0.085858886776146726, 0.012110073534532972, -0.05287131505877718,
      -0.1084615242217622, -0.15467397967191054, -0.19191531135768641,
      -0.22082108341782736, -0.24214787054821191, -0.25670353161802395,
      -0.26530274426991723, -0.26873902271412292, -0.26776743993909324,
      -0.263094318736156, -0.25537149877825033, -0.24519364879080907,
      -0.23309763740724576, -0.2195633173813864, -0.20501529097683346,
      -0.18982535821095181, -0.17431543483204842, -0.15876078241253483,
      -0.1433934303325945, -0.1284056957139193, -0.11395372671868254,
      -0.10016100958442298, -0.087121791764035172, -0.0749043835025981,
      -0.0635543086112616, -0.05309728242509032, -0.043542001166887168,
      -0.034882732307646047, -0.027101700128050854, -0.020171264612098061,
      -0.014055895116430461, -0.0087139430087471714, -0.0040992197160493182,
      -0.00016238841325832976, 0.003147821031485476, 0.0058835632150775474,
      0.00809698311637963, 0.0098394649960453773, 0.011161012314529262,
      0.01210974671500864, 0.012731514301768554, 0.013069587767997826,
      0.013164453364339468, 0.013053672225603608, 0.012771806166277377,
      0.012350398696818643, 0.011818002684607198, 0.011200246771879807,
      0.010519933355056965, 0.009797161615069494, 0.0090494697580514316,
      0.0082919912725331058, 0.0075376206278430224, 0.006797184424246927,
      0.0060796145550342517, 0.005392120453069027, 0.0047403579669591522,
      0.004128592845259349, 0.0035598572014762242, 0.0030360976881895763,
      0.0025583144274451408, 0.0021266900281566858, 0.0017407082719027578,
      0.0013992622688442369, 0.0011007520785315528, 0.0008431719602477461,
      0.00062418756856874591, 0.00044120354880905488, 0.00029142212240529375,
      0.0001718933969463432, 7.9558308014426871E-5, 1.1285327767729392E-5,
      -3.609760136191742E-5, -6.5773973673688424E-5, -8.0909830129094473E-5,
      -8.4621415423868918E-5, -7.9934325225017311E-5, -6.9727339336189686E-5,
      -5.6652403340295976E-5, -4.3021689350775105E-5, -3.0656462330469481E-5,
      -2.0708047080764125E-5, -1.3505271479918868E-5, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_lab2_DW.FromWorkspace4_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_lab2_DW.FromWorkspace4_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_lab2_DW.FromWorkspace4_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace5' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0, 35.25, 35.5, 35.75, 36.0,
      36.25, 36.5, 36.75, 37.0, 37.25, 37.5, 37.75, 38.0, 38.25, 38.5, 38.75,
      39.0, 39.25, 39.5, 39.75, 40.0, 40.25, 40.5, 40.75, 41.0, 41.25, 41.5,
      41.75, 42.0, 42.25, 42.5, 42.75, 43.0, 43.25, 43.5, 43.75, 44.0, 44.25,
      44.5, 44.75, 45.0, 45.25, 45.5, 45.75, 46.0, 46.25, 46.5, 46.75, 47.0,
      47.25, 47.5, 47.75, 48.0, 48.25, 48.5, 48.75, 49.0, 49.25, 49.5, 49.75,
      50.0, 50.25, 50.5, 50.75, 51.0, 51.25, 51.5, 51.75, 52.0, 52.25, 52.5,
      52.75, 53.0, 53.25, 53.5, 53.75, 54.0, 54.25, 54.5, 54.75, 55.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500824011378,
      0.46652650906198218, 0.38488436997254627, 0.28224853798169158,
      0.19404586986348327, 0.1280702741068617, 0.082178425886042836,
      0.022735674934001696, -0.11177878876619858, -0.22791494765357151,
      -0.30194845798715719, -0.33609644696036334, -0.3400042866982827,
      -0.32362619488350647, -0.29499525296694445, -0.25992555437393422,
      -0.22236083665245693, -0.1848498218018628, -0.14896532674260493,
      -0.11562308824098454, -0.085307148521815951, -0.058222644279305805,
      -0.034396850607721977, -0.013745113776794951, 0.003886331100246949,
      0.018692484811857809, 0.030891279831751006, 0.040711399949960911,
      0.048384045534549017, 0.054137280103662984, 0.058192105618514262,
      0.060759731063656029, 0.062039693515435729, 0.062218609678418142,
      0.061469408319385722, 0.059950938475281594, 0.057807875980971431,
      0.055170868536958372, 0.052156871281762981, 0.048869633045788459,
      0.045400299565761894, 0.041828104744963839, 0.0382211250329898,
      0.034637075436858511, 0.031124128718412986, 0.027721742063934213,
      0.024461477982962526, 0.021367808430804026, 0.018458893170828879,
      0.01574732521127949, 0.013240837778919479, 0.010942968734440428,
      0.0088536796052147478, 0.0069699275187056512, 0.0052861892739733555,
      0.0037949376019703216, 0.0024870703470625628, 0.0013522938649174804,
      0.0003794623853893726, -0.00044312455493952579, -0.0011274642373042716,
      -0.0016856298778388182, -0.0021295840488528947, -0.0024710236509044594,
      -0.0027212536672985592, -0.00289108695995347, -0.0029907674280874323,
      -0.0030299139421043645, -0.003017482578752471, -0.0029617448144070744,
      -0.0028702794768879496, -0.0027499764078650129, -0.002607049944466464,
      -0.0024470604868432988, -0.0022749425751742488, -0.0020950380531787756,
      -0.0019111330430095982, -0.0017264975971977706, -0.0015439270250515557,
      -0.0013657840122814676, -0.0011940407612980734, -0.0010303204731883979,
      -0.00087593756676595874, -0.00073193607908741563, -0.00059912570567203236,
      -0.00047811490189565904, -0.00036934035578977954, -0.00027309192104124066,
      -0.00018953171657720415, -0.00011870548930284935, -6.0543425875285191E-5,
      -1.484634122899948E-5, 1.8748360750467846E-5, 4.0827943518984636E-5,
      5.2299743957345837E-5, 5.4522855944650814E-5, 4.9460908085498348E-5,
      3.9793661023502818E-5, 2.8811102451277326E-5, 1.9654628380546675E-5, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_lab2_DW.FromWorkspace5_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_lab2_DW.FromWorkspace5_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_lab2_DW.FromWorkspace5_IWORK.PrevIndex = 0;
  }

  /* Start for If: '<S3>/If' */
  helicopter_lab2_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter_lab2_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter_lab2_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter_lab2_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter_lab2_X.Integrator_CSTATE = helicopter_lab2_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter_lab2_DW.TimeStampA = (rtInf);
  helicopter_lab2_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter_lab2_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_lab2/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter_lab2_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter_lab2_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter_lab2_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopter_lab2_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_lab2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_lab2_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopter_lab2_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopter_lab2_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_lab2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_lab2_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter_lab2_DW.HILInitialize_Card
                         , helicopter_lab2_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopter_lab2_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter_lab2_DW.HILInitialize_AOVoltages[0]
                         , &helicopter_lab2_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter_lab2_DW.HILInitialize_Card,
            helicopter_lab2_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &helicopter_lab2_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter_lab2_DW.HILInitialize_Card,
            helicopter_lab2_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &helicopter_lab2_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_lab2_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter_lab2_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter_lab2_DW.HILInitialize_Card);
    hil_close(helicopter_lab2_DW.HILInitialize_Card);
    helicopter_lab2_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  helicopter_lab2_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter_lab2_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  helicopter_lab2_initialize();
}

void MdlTerminate(void)
{
  helicopter_lab2_terminate();
}

/* Registration function */
RT_MODEL_helicopter_lab2_T *helicopter_lab2(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter_lab2_P.Integrator_UpperSat = rtInf;
  helicopter_lab2_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter_lab2_M, 0,
                sizeof(RT_MODEL_helicopter_lab2_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter_lab2_M->solverInfo,
                          &helicopter_lab2_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter_lab2_M->solverInfo, &rtmGetTPtr(helicopter_lab2_M));
    rtsiSetStepSizePtr(&helicopter_lab2_M->solverInfo,
                       &helicopter_lab2_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter_lab2_M->solverInfo, &helicopter_lab2_M->derivs);
    rtsiSetContStatesPtr(&helicopter_lab2_M->solverInfo, (real_T **)
                         &helicopter_lab2_M->contStates);
    rtsiSetNumContStatesPtr(&helicopter_lab2_M->solverInfo,
      &helicopter_lab2_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter_lab2_M->solverInfo,
      &helicopter_lab2_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter_lab2_M->solverInfo,
      &helicopter_lab2_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter_lab2_M->solverInfo,
      &helicopter_lab2_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter_lab2_M->solverInfo, (&rtmGetErrorStatus
      (helicopter_lab2_M)));
    rtsiSetRTModelPtr(&helicopter_lab2_M->solverInfo, helicopter_lab2_M);
  }

  rtsiSetSimTimeStep(&helicopter_lab2_M->solverInfo, MAJOR_TIME_STEP);
  helicopter_lab2_M->intgData.f[0] = helicopter_lab2_M->odeF[0];
  helicopter_lab2_M->contStates = ((real_T *) &helicopter_lab2_X);
  rtsiSetSolverData(&helicopter_lab2_M->solverInfo, (void *)
                    &helicopter_lab2_M->intgData);
  rtsiSetSolverName(&helicopter_lab2_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter_lab2_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter_lab2_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter_lab2_M->Timing.sampleTimes =
      (&helicopter_lab2_M->Timing.sampleTimesArray[0]);
    helicopter_lab2_M->Timing.offsetTimes =
      (&helicopter_lab2_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter_lab2_M->Timing.sampleTimes[0] = (0.0);
    helicopter_lab2_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter_lab2_M->Timing.offsetTimes[0] = (0.0);
    helicopter_lab2_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter_lab2_M, &helicopter_lab2_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter_lab2_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter_lab2_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter_lab2_M, -1);
  helicopter_lab2_M->Timing.stepSize0 = 0.002;
  helicopter_lab2_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter_lab2_M->Sizes.checksums[0] = (167187459U);
  helicopter_lab2_M->Sizes.checksums[1] = (1425379368U);
  helicopter_lab2_M->Sizes.checksums[2] = (3126342999U);
  helicopter_lab2_M->Sizes.checksums[3] = (3837151622U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopter_lab2_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &helicopter_lab2_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopter_lab2_M->extModeInfo,
      &helicopter_lab2_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter_lab2_M->extModeInfo,
                        helicopter_lab2_M->Sizes.checksums);
    rteiSetTPtr(helicopter_lab2_M->extModeInfo, rtmGetTPtr(helicopter_lab2_M));
  }

  helicopter_lab2_M->solverInfoPtr = (&helicopter_lab2_M->solverInfo);
  helicopter_lab2_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter_lab2_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter_lab2_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter_lab2_M->blockIO = ((void *) &helicopter_lab2_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      helicopter_lab2_B.Gain1[i] = 0.0;
    }

    helicopter_lab2_B.TravelCounttorad = 0.0;
    helicopter_lab2_B.Gain = 0.0;
    helicopter_lab2_B.Traveldeg = 0.0;
    helicopter_lab2_B.Gain_d = 0.0;
    helicopter_lab2_B.PitchCounttorad = 0.0;
    helicopter_lab2_B.Gain_i = 0.0;
    helicopter_lab2_B.Gain_b = 0.0;
    helicopter_lab2_B.ElevationCounttorad = 0.0;
    helicopter_lab2_B.Gain_e = 0.0;
    helicopter_lab2_B.Sum = 0.0;
    helicopter_lab2_B.Gain_dg = 0.0;
    helicopter_lab2_B.FromWorkspace1 = 0.0;
    helicopter_lab2_B.Sum3 = 0.0;
    helicopter_lab2_B.Gain_l = 0.0;
    helicopter_lab2_B.BackmotorSaturation = 0.0;
    helicopter_lab2_B.FrontmotorSaturation = 0.0;
    helicopter_lab2_B.In1 = 0.0;
  }

  /* parameters */
  helicopter_lab2_M->defaultParam = ((real_T *)&helicopter_lab2_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter_lab2_X;
    helicopter_lab2_M->contStates = (x);
    (void) memset((void *)&helicopter_lab2_X, 0,
                  sizeof(X_helicopter_lab2_T));
  }

  /* states (dwork) */
  helicopter_lab2_M->dwork = ((void *) &helicopter_lab2_DW);
  (void) memset((void *)&helicopter_lab2_DW, 0,
                sizeof(DW_helicopter_lab2_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_lab2_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_lab2_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_lab2_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_lab2_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_lab2_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_lab2_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_lab2_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_lab2_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter_lab2_DW.TimeStampA = 0.0;
  helicopter_lab2_DW.LastUAtTimeA = 0.0;
  helicopter_lab2_DW.TimeStampB = 0.0;
  helicopter_lab2_DW.LastUAtTimeB = 0.0;
  helicopter_lab2_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter_lab2_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter_lab2_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter_lab2_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter_lab2_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopter_lab2_M->Sizes.numY = (0); /* Number of model outputs */
  helicopter_lab2_M->Sizes.numU = (0); /* Number of model inputs */
  helicopter_lab2_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter_lab2_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter_lab2_M->Sizes.numBlocks = (70);/* Number of blocks */
  helicopter_lab2_M->Sizes.numBlockIO = (18);/* Number of block outputs */
  helicopter_lab2_M->Sizes.numBlockPrms = (171);/* Sum of parameter "widths" */
  return helicopter_lab2_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
