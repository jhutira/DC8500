/*******************************************************************************
** System
********************************************************************************
*
* System routines
*
*
* v1.0
*
* (c) 5.5.2016
*******************************************************************************/

#include "system.h"
#include "rtc.h"
#include "reg.h"
#include "fireplace.h"
#include "backlight.h"
#include "energy.h"

#include "eeprom.h"
#include "mem_map.h"

/******************************************************************************
** Defines
*******************************************************************************/

/******************************************************************************
** Constants
*******************************************************************************/


/******************************************************************************
** Variables
*******************************************************************************/
system_st mSystem;
modbus_t mb;

uint8_t lang_id;



/******************************************************************************
** Functions
*******************************************************************************/


/******************************************************************************
** system_init
*******************************************************************************
* Description    : initializing mSystem variables
* Input          : None
* Return         : None
*******************************************************************************/
void system_init(void)
{
	mSystem.service_mode = 0;
	mSystem.exservice_mode = 0;

	mSystem.err_state = 0;

	system_setDefault();

	system_loadData();

	datetime = RTC_GetCalendar();

	reg_init();
	reg_setRegScheme(0); 		/* no installation */

	backlight_pwm(mSystem.display.sett.backlight);

	energy_loadAccEng();

}

/******************************************************************************
** system_setDefault
*******************************************************************************
* Description    : Setting to default values
* Input          : None
* Return         : None
*******************************************************************************/
void system_setDefault(void)
{
	lang_id = LANG_SVK;

	regSch = SCH_01;

	mSystem.sound.sett.announ_msg = amALARM | amWARN | amTOUCH;
	mSystem.sound.sett.mute_time_on.h = 23;
	mSystem.sound.sett.mute_time_on.m = 0;
	mSystem.sound.sett.mute_time_off.h = 5;
	mSystem.sound.sett.mute_time_off.m = 0;
	mSystem.sound.mute = 0;
	mSystem.sound.on = 1;

	mSystem.display.sett.backlight = 50;
	mSystem.display.sett.saver_backlight = 3;
	mSystem.display.sett.saver_time = 60;
	mSystem.display.sett.saver_en = 1;

	mSystem.display.timer = 0;

	fireplace_setDefault();

	accum_setDefault();
	boiler_setDefault();

	distrib = ds_WATER_HEAT;

	analog_setDefault();
	digital_setDefault();

	lambda_init();

	airflap_setDefault(PRIM_F);
	airflap_setDefault(SEC_F);

	pid_setDefault(&airflap[PRIM_F].pid);
	pid_setDefault(&airflap[SEC_F].pid);

	contPump_setDefault();

	flowmeter_setDefault();
	energy_setDefault();

	oTemp_setDefault();


}

/******************************************************************************
** system_loadData
*******************************************************************************
* Description    : Load data from EEPROM
* Input          : None
* Return         : None
*******************************************************************************/
void system_loadData(void)
{
	eem_readInt8(aLANG_ID, &lang_id);

	eem_readInt8(aREG_SCH, &regSch);
	eem_readInt8(aDISTRIB, &distrib);

	eem_readBlock(aSOUND_SETT, sizeof(sound_sett_st), (uint8_t*)&mSystem.sound.sett);
	eem_readInt8(aSOUND_MUTE, &mSystem.sound.mute);

	eem_readBlock(aDISP_SETT, sizeof(disp_sett_st), (uint8_t*)&mSystem.display.sett);

	fireplace_loadSettings();

	accum_loadSettings();
	boiler_loadSettings();

	/* Outputs */
	digital_loadSettings();

	/* AirFlap */
	airflap_loadSettings(PRIM_F);
	airflap_loadSettings(SEC_F);

	/* PID */
	pid_loadSettings(&airflap[PRIM_F].pid, aPFLAP_PID);
	pid_loadSettings(&airflap[SEC_F].pid, aSFLAP_PID);


	contPump_loadSettings();

	flowmeter_loadSettings();
	energy_loadSettings();

	oTemp_loadSettings();


}

/******************************************************************************
** system_saveData
*******************************************************************************
* Description    : Save data to EEPROM
* Input          : None
* Return         : None
*******************************************************************************/
void system_saveData(void)
{
	eem_writeInt8(aLANG_ID, lang_id);

	eem_writeInt8(aREG_SCH, regSch);
	eem_writeInt8(aDISTRIB, distrib);

	eem_writeBlock(aSOUND_SETT, sizeof(sound_sett_st), (uint8_t*)&mSystem.sound.sett);
	eem_writeInt8(aSOUND_MUTE, mSystem.sound.mute);

	eem_writeBlock(aDISP_SETT, sizeof(disp_sett_st), (uint8_t*)&mSystem.display.sett);

	fireplace_saveSettings();

	accum_saveSettings();
	boiler_saveSettings();

	//analog_saveSettings();
	digital_saveSettings();

	airflap_saveSettings(PRIM_F);
	airflap_saveSettings(SEC_F);

	/* PID */
	pid_saveSettings(&airflap[PRIM_F].pid, aPFLAP_PID);
	pid_saveSettings(&airflap[SEC_F].pid, aSFLAP_PID);

	contPump_saveSettings();
	flowmeter_saveSettings();
	energy_saveSettings();

	oTemp_saveSettings();

}

/******************************************************************************
** system_checkErrWarnState
*******************************************************************************
* Description    : Checking errors and warnings state
* Input          : None
* Return         : None
*******************************************************************************/
void system_checkErrWarnState(void)
{
	uint8_t i, state;

	state = mSystem.err_state;

	state &= ~eSEN;
	/* TS */
	for (i = 0; i < AIN_COUNT; i++)
	{
		if (sensorIsUsed(i) && (ain[i].status & TS_ERROR))
		{
			state |= eSEN;
			break;
		}
	}
	/* Lambda */
	if (lambda.status & TS_ERROR)
	{
		state |= eSEN;
	}

	/* Outputs */
	state &= ~eMAN;
	for (i = 0; i < OUT_COUNT; i++)
	{
		if (out[i].mode & oMAN)
		{
			state |= eMAN;
		}
	}

	/* Air flaps */
	if (airflap[PRIM_F].mode == mMAN)
	{
		state |= eMAN;
	}
//	if (airflap[PRIM_F].state_r & oFAULT)
//	{
//		state |= eVE_OVC;
//	}
	if (modus & mUSE_FLAP2)
	{
		if (airflap[SEC_F].mode == mMAN)
		{
			state |= eMAN;
		}
		//if (airflap[PRIM_F].state_r & oFAULT)
		//	{
		//		state |= eVE_OVC;
		//	}
	}


	/* Critic temperature */
	if (fireplace.burning.fCriticTemp)
	{
		state |= eOVERHEAT;
	}
	else
	{
		state &= ~eOVERHEAT;
	}


	mSystem.err_state = state;
}
