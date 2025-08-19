/*******************************************************************************
** Air flap
********************************************************************************
*
* air flap routines
*
*
* v1.0
*
* (c) 13.2.2025
*******************************************************************************/
#include "air_flap.h"
#include "stdlib.h"
#include "system.h"
#include "eeprom.h"
#include "mem_map.h"



flap_st airflap[FLAP_COUNT];



/******************************************************************************
** airflap_init
*******************************************************************************
* Description    :  Initialization air flap
* Input          :  ch: channel [0..1]
* Return         :  None
*******************************************************************************/
void airflap_init(uint8_t ch)
{
    airflap_setDefault(ch);
    //airflap_moveFullClose(ch);
}


/******************************************************************************
** airflap_movePosition
*******************************************************************************
* Description    :  Flap Air move to new position
* Input          :  ch: channel [0..1]
*                :  pos: new position [0..1000]
* Return         :  None
*******************************************************************************/
void airflap_movePosition(uint8_t ch, uint16_t pos)
{
    if (airflap[ch].mode == mMAN)
    {
        return;
    }
    airflap[ch].status = mMOVE_OPEN;
    airflap[ch].pos = pos;
}


/******************************************************************************
** airflap_calculOut
*******************************************************************************
* Description    :  calculate new out value
* Input          :  ch: channel [0..1]
*                :  iVal : input value
*                :  rVal : request value
* Return         :  pos: new value
*******************************************************************************/
uint16_t airflap_compute(uint8_t ch, int16_t iVal, int16_t rVal)
{
	uint8_t status;
	uint16_t new_pos;

	status = airflap[ch].status;
	new_pos = airflap[ch].pos;

	if (airflap[ch].mode == mMAN)
	{
		return airflap[ch].pos;
	}

	if (airflap[ch].pos >= 100)
	{
		status = mOPENED;
	}

	if (airflap[ch].pos == 0)
	{
		status = mCLOSED;
	}


	if (airflap[ch].updateTimer)
	{
		airflap[ch].updateTimer--;
	}
	else
	{
		airflap[ch].updateTimer = (uint32_t) (airflap[ch].pid.config.dt * 10);

		pid_setSetpoint(&airflap[ch].pid, (float)rVal / 10);
		new_pos = pid_compute(&airflap[ch].pid, (float)iVal / 10);

		if (new_pos > airflap[ch].pos)
		{
			if (status != mOPENED)
			{
				status = mMOVE_OPEN;
			}
		}
		else if (new_pos < airflap[ch].pos)
		{
			if (status != mCLOSED)
			{
				status = mMOVE_CLOSE;
			}
		}
	}

	airflap[ch].status = status; // save status
	return new_pos;
}


/******************************************************************************
** airflap_SetDefault
*******************************************************************************
* Description    : Setting default values
* Input          : ch: channel [0..1]
* Return         : None
*******************************************************************************/
void airflap_setDefault(uint8_t ch)
{
    if (ch == 0)
    {
        airflap[0].mode = mAUT;
        airflap[0].pos = 0;
    }
    else
    {
        airflap[1].mode = mAUT;
        airflap[1].pos = 0;
    }

}

/******************************************************************************
** airflap_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : None
* Return         : None
*******************************************************************************/
void airflap_saveSettings(uint8_t ch)
{
    uint16_t adr = aPFLAP + ((uint16_t)ch * 10);

    eem_writeInt8(adr, airflap[ch].mode);
    eem_writeInt8(adr + 1, airflap[ch].pos);
}

/******************************************************************************
** airflap_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : None
* Return         : None
*******************************************************************************/
void airflap_loadSettings(uint8_t ch)
{
	uint16_t adr = aPFLAP + ((uint16_t)ch * 10);

    eem_readInt8(adr, &airflap[ch].mode);
    eem_readInt8(adr + 1, &airflap[ch].pos);
}

/******************************************************************************
** airflap_saveMode
*******************************************************************************
* Description    : Save Mode settings
* Input          : None
* Return         : None
*******************************************************************************/
void airflap_saveMode(uint8_t ch)
{
	uint16_t adr = aPFLAP + ((uint16_t)ch * 10);

	eem_writeInt8(adr, airflap[ch].mode);
	eem_writeInt8(adr + 1, airflap[ch].pos);
}
