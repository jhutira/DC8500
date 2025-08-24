/*******************************************************************************
** PID reg
********************************************************************************
*
* pid regulation routines
*
*
* v1.0
*
* (c) 13.3.2019
*******************************************************************************/

#include "pid_reg.h"
#include <math.h>
#include <stdio.h>
#include <uart_log.h>

#include "eeprom.h"



/******************************************************************************
** Defines
*******************************************************************************/


/******************************************************************************
** Constants
*******************************************************************************/

/******************************************************************************
** Variables
*******************************************************************************/


/******************************************************************************
** Functions
*******************************************************************************/

/******************************************************************************
 ** pid_install
 *******************************************************************************
 * Description    :  Install PID
 * Input          :  *pid: pointer to object
 * Return         :  None
 *******************************************************************************/
void pid_install(pid_st *pid)
{
	pid_init(pid, PID_NORMAL, 1.0f, 0.5f, 0.1f, 0.0f, 100.0f, 10.0f);
}

/******************************************************************************
 ** pid_setDefault
 *******************************************************************************
 * Description    :  Initialization PID
 * Input          :  *pid: pointer to object
 * Return         :  None
 *******************************************************************************/
void pid_setDefault(pid_st *pid)
{
	pid_init(pid, PID_NORMAL, 1.0f, 0.5f, 0.1f, 0.0f, 100.0f, 10.0f);
}


/******************************************************************************
** pid_init
*******************************************************************************
* Description    :  Initialization PaBURN_PHASES_SID
* Input          :  *pid: pointer to object
* Return         :  None
*******************************************************************************/
void pid_init(pid_st *pid, uint32_t mode,  float Kp, float Ki, float Kd, float outMin, float outMax, float t )
{
	pid->config.mode = mode;
	pid->config.kp = Kp;
    pid->config.ki = Ki;
    pid->config.kd = Kd;
    pid->config.outputMin = outMin;
    pid->config.outputMax = outMax;
    pid->config.dt = t;				// samples
    pid->config.tolerance = 0.0f;
    pid->integral = 0.0f;
    pid->previousError = 0.0f;
    pid->setpoint = 0.0f;
    pid->debug = false;

    pid_enableDebug(pid);
}

/******************************************************************************
** pid_setSetpoint
*******************************************************************************
* Description    :  Set Setpoint
* Input          :  *pidreg: pointer to object
*                :  setpoint: setpoint value
* Return         :  None
*******************************************************************************/
void pid_setSetpoint(pid_st *pid, float setpoint)
{
	pid->setpoint = setpoint;
}

/******************************************************************************
** pid_setDt
*******************************************************************************
* Description    :  Set Dt
* Input          :  *pidreg: pointer to object
*                :  dt:
* Return         :  None
*******************************************************************************/
void pid_setDt(pid_st *pid, float dt)
{
    pid->config.dt = dt;
}

/******************************************************************************
** pid_setDt
*******************************************************************************
* Description    :  Set Dt
* Input          :  *pidreg: pointer to object
*                :  dt:
* Return         :  None
*******************************************************************************/
void pid_setTolerance(pid_st *pid, float tol)
{
    pid->config.tolerance = tol;
}

/******************************************************************************
** PID_EnableDebug
*******************************************************************************
* Description    :  Enable debug
* Input          :  *pidreg: pointer to object
* Return         :  None
*******************************************************************************/
void pid_enableDebug(pid_st *pid)
{
    pid->debug = true;
}

///******************************************************************************
//** pid_reset
//*******************************************************************************
//* Description    :  Reset PID
//* Input          :  *pid: pointer to object
//* Return         :  None
//*******************************************************************************/
void pid_reset(pid_st *pid)
{
    pid->integral = 0;
    pid->previousError = 0;
}

///******************************************************************************
//** pid_isAtSetpoint
//*******************************************************************************
//* Description    :  PID is at setpoint
//* Input          :  *pid: pointer to object
//* Return         :  state:
//*******************************************************************************/
bool pid_isAtSetpoint(pid_st *pid)
{
    return fabsf(pid->previousError) <= pid->config.tolerance;
}

//******************************************************************************
//** pid_calculate
//*******************************************************************************
//* Description    :  Calculate PID
//* Input          :  *pid: pointer to object
//* Return         :  None
//*******************************************************************************/
float pid_compute(pid_st *pid, float input)
{
	float error;
	float output;

	if (pid->config.mode & PID_INVERT) error = input - pid->setpoint;
	else error = pid->setpoint - input;

	pid->integral += error * pid->config.dt;

	// Anti-windup (prevent integral windup by keeping it within output range)
	//float maxI = pid->config.outputMax / fmaxf(pid->config.ki, 0.0001f);
	//float minI = pid->config.outputMin / fmaxf(pid->config.ki, 0.0001f);
	//if (pid->integral > maxI) pid->integral = maxI;
	//  else if (pid->integral < minI) pid->integral = minI;

	if (pid->config.ki > 0.0f)
	{
	    float maxI = pid->config.outputMax / (pid->config.ki / 10);
	    float minI = pid->config.outputMin / (pid->config.ki / 10);
	    pid->integral = fminf(fmaxf(pid->integral, minI), maxI);
	}

	float derivative = (error - pid->previousError) / pid->config.dt;

	output = (pid->config.kp * error) + ((pid->config.ki / 10) * pid->integral) + ((pid->config.kd / 10) * derivative);

	// Output Clamping + anti-windup
	if (output > pid->config.outputMax)
	{
		output = pid->config.outputMax;
	    if (error > 0) pid->integral -= error * pid->config.dt;  	// anti-windup
	}
	else
	if (output < pid->config.outputMin)
	{
		output = pid->config.outputMin;
	    if (error < 0) pid->integral -= error * pid->config.dt;		// anti-windup
	}

	pid->previousError = error;

	if (pid->debug)
	{
		uart_log_printf("PID | SP: %.2f IN: %.2f ERR: %.2f OUT: %.2f\r\n", pid->setpoint, input, error, output);
	}
	return output;
}

/******************************************************************************
** pidreg_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : *pid: pointer to object
*                : addr: address of memory
* Return         : None
*******************************************************************************/
void pid_saveSettings(pid_st *pid, uint16_t addr)
{
	eem_writeBlock(addr, sizeof(pidConfig_st), (uint8_t*) &pid->config);
}

/******************************************************************************
** pidreg_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : *pid: pointer to object
*                : addr: address of memory
* Return         : None
*******************************************************************************/
void pid_loadSettings(pid_st *pid, uint16_t addr)
{
	eem_readBlock(addr, sizeof(pidConfig_st), (uint8_t*) &pid->config);
}



