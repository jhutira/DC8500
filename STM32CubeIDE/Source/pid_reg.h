/*******************************************************************************
** PID reg
********************************************************************************
*
* pid regulation routines
*
*
* v1.0
*
* (c) 22.4.2025
*******************************************************************************/

#ifndef __PID_REG_H_
#define __PID_REG_H_

#include <stdint.h>
#include <stdbool.h>
#include <float.h>

/******************************************************************************
** Defines
*******************************************************************************/
#define	PID_NORMAL 0x00000000
#define	PID_INVERT 0x00000001

static const int32_t FI_SCALE = 10; // scaling factor to simulate decimals

typedef struct
{
	float kp;            ///< Proportional gain: reacts to the current error
	float ki;            ///< Integral gain: reacts to the accumulation of past errors
	float kd;            ///< Derivative gain: reacts to the prediction of future errors

	float outputMin;     ///< Minimum output limit to prevent undersaturation
	float outputMax;     ///< Maximum output limit to prevent oversaturation

	float tolerance;     ///< Acceptable deviation from setpoint (used in isAtSetpoint())

    float dt;		 	 ///< Sampling time
    uint32_t mode;	 	///< Mode
} pidConfig_st;

typedef struct
{
	pidConfig_st config;

    float setpoint;
	float integral;
	float previousError;

	bool debug;
} pid_st;


/******************************************************************************
** Variable
*******************************************************************************/


/******************************************************************************
** Functions
*******************************************************************************/
void pid_init(pid_st *pid, uint32_t mode,  float Kp, float Ki, float Kd, float outMin, float outMax, float t);
void pid_setDefault(pid_st *pid);
void pid_setSetpoint(pid_st *pid, float setpoint);
void pid_setDt(pid_st *pid, float dt);
void pid_setTolerance(pid_st *pid, float tol);
float pid_compute(pid_st *pid, float input);
bool pid_isAtSetpoint(pid_st *pid);
void pid_enableDebug(pid_st *pid);
void pid_reset(pid_st *pid);

void pid_saveSettings(pid_st *pid, uint16_t addr);
void pid_loadSettings(pid_st *pid, uint16_t addr);


#endif /* PIDREG_H_ */
