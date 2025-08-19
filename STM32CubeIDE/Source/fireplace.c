/*******************************************************************************
** fireplace.h
********************************************************************************
*
* fireplace regulation routines
*
*
* v1.0
*
* (c) 5.3.2025
*******************************************************************************/

#include "fireplace.h"
#include "system.h"
#include "eeprom.h"
#include "mem_map.h"

#include "pid_reg.h"
#include "lambda_sen.h"

/******************************************************************************
** Defines
*******************************************************************************/



/******************************************************************************
** Constants
*******************************************************************************/


/******************************************************************************
** Variables
*******************************************************************************/
fireplace_st fireplace;


uint16_t burningTimer = 0;


/******************************************************************************
** Functions
*******************************************************************************/

#define setBurningTimer(t) burningTimer = t


/******************************************************************************
** fireplace_setDefault
*******************************************************************************
* Description    : Setting default values
* Input          : None
* Return         : None
*******************************************************************************/
void fireplace_setDefault(void)
{
	fireplace.burning.mode = 0;
	fireplace.burning.status = 0;
	fireplace.burning.phase = BP0_STOP;
	fireplace.burning.phase_prev = BP0_STOP;
	fireplace.burning.step = 0;

	fireplace.burning.fRestartProcess = 0;
	fireplace.burning.fCriticTemp = 0;

	burnProf_setDefault();
	burnPhases_setDefault();

	fireplace.door.usedSwitch = 0;
	fireplace.door.timeout = 10;
	fireplace.door.status = DOOR_CLOSED;

	waterExch_setDefault();
}

/******************************************************************************
** fireplace_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : None
* Return         : None
*******************************************************************************/
void fireplace_saveSettings(void)
{
	eem_writeInt8(aDOOR_SW, fireplace.door.usedSwitch);
	eem_writeInt8(aDOOR_TIMEOUT, fireplace.door.timeout);

	burnProf_saveSettings();
	burnPhases_saveSettings();
	waterExch_saveSettings();
}

/******************************************************************************
** fireplace_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : None
* Return         : None
*******************************************************************************/
void fireplace_loadSettings(void)
{
	eem_readInt8(aDOOR_SW, &fireplace.door.usedSwitch);
	eem_readInt8(aDOOR_TIMEOUT, &fireplace.door.timeout);

	burnProf_loadSettings();
	burnPhases_loadSettings();
	waterExch_loadSettings();
}

/******************************************************************************
** fireplace_install
*******************************************************************************
* Description    : Install fireplace (set default value and save to EEM )
* Input          : None
* Return         : None
*******************************************************************************/
void fireplace_install(void)
{
	fireplace_setDefault();
	fireplace_saveSettings();
}

/******************************************************************************
** burning_startBurn
*******************************************************************************
* Description    :  Start burning process
* Input          :  none
* Return         :  none
*******************************************************************************/
void fireplace_startBurning(void)
{
    fireplace.burning.status = BS_START_BURN;
    fireplace.burning.phase = BP1_STBURN;
    fireplace.burning.phase_prev = fireplace.burning.phase;
    fireplace.burning.step = BP1_STEP_INIT;
}

/******************************************************************************
** fireplace_stopBurn
*******************************************************************************
* Description    :  Stop burning precess
* Input          :  none
* Return         :  none
*******************************************************************************/
void fireplace_stopBurning(void)
{
	fireplace.burning.primFlapPos = 100;          /* Primary AirFlap = 10.0% */
	fireplace.burning.secFlapPos = 0;             /* Close Secondary Airflap */
	fireplace.burning.step = 0;
	fireplace.burning.status = BS_STOP;
	fireplace.burning.phase = BP0_STOP;
}
/******************************************************************************
** fireplace_setBurnProfil
*******************************************************************************
* Description    :  Set burn profil
* Input          :  p: pos
* Return         :  none
*******************************************************************************/
void fireplace_setBurnProfil()
{
    fireplace.burning.rqFlueTemp = fireplace.burnProfile.rqFlueTemp;
}

/******************************************************************************
** fireplace_regProcess
*******************************************************************************
* Description    :  BURNING process
* Input          :  none
* Return         :  none
*******************************************************************************/
void fireplace_regProcess(void)
{
	if (fireplace.door.status == DOOR_OPENED)
	{
		fireplace.burning.primFlapPos = 0;                /* Close Primary Airflap */
		fireplace.burning.secFlapPos = 0;                 /* Close Secondary Airflap */
		return;
	}

	switch (fireplace.burning.phase)
	{
	/* Emergency stop  */
		case BP0_ESTOP:
			fireplace.burning.primFlapPos = 0;            /* Close Primary Airflap */
			fireplace.burning.secFlapPos = 0;             /* Close Secondary Airflap */
			fireplace.burning.step = 0;
			fireplace.burning.status = BS_STOP;

			/* restart after error */
			if (fireplace.burning.fRestartProcess)
			{
				fireplace.burning.fRestartProcess = 0;    /* clear flag */
				if (fireplace.burning.phase_prev == BP0_STOP)
				{
					fireplace.burning.phase = BP0_STOP;
				}
				else
				{
					fireplace_startBurning();
				}
			}
			break;

		/* Stop  */
		case BP0_STOP:
			fireplace.burning.primFlapPos = 0;            	/* Close Primary Airflap */
			fireplace.burning.secFlapPos = 0;             	/* Close Secondary Airflap */
			fireplace.burning.step = 0;
			fireplace.burning.status = BS_STOP;
			break;


		/* Start burning  */
		case BP1_STBURN:
			if (fireplace.burning.step == BP1_STEP_INIT)
			{
				if (sensorOk(SN_E) == 0)
				{
					break;                      			/* Sensor not OK */
				}
				fireplace.burning.primFlapPos = 100;     	/* Primary Airflap = 100.0% */
				setUserTimer1(fireplace.burnPhases.phStartBurning.timeout * 60);
				fireplace.burning.status = BS_START_BURN;
				fireplace.burning.step = BP1_STEP_WAIT_MINTEMP;
			}

			if (fireplace.burning.step == BP1_STEP_WAIT_MINTEMP)
			{
				fireplace.burning.primFlapPos = 100;     	/* Primary Airflap = 100.0% */

				if (getUserTimer1() == 0)       			/* timeout, skip to BP3_BURN_OUT */
				{
					fireplace.burning.phase = BP2_BURNING;
					fireplace.burning.step = BP2_STEP_INIT;
				}

				if (fireplace.burning.flueTemp >= fireplace.burnPhases.phStartBurning.minTempForBurn)
				{
					fireplace.burning.phase = BP2_BURNING;
					fireplace.burning.step = BP2_STEP_INIT;
				}
			}
			break;

		/* Burn */
		case BP2_BURNING:
			if (fireplace.burning.step == BP2_STEP_INIT)
			{
				fireplace.burning.step = BP2_STEP_WAIT_TEMP;
				fireplace.burning.status = BS_BURNING;
				setBurningTimer(fireplace.burnPhases.phBurning.timeoutForBurnOut * 60);
				pid_reset(&airflap[PRIM_F].pid);
			}
			if (fireplace.burning.step == BP2_STEP_WAIT_TEMP)
			{
				if (fireplace.burning.flueTemp > fireplace.burnPhases.phBurning.tempForBurnOut+30)		// Restart timer
				{
					setBurningTimer(fireplace.burnPhases.phBurning.timeoutForBurnOut * 60);
				}
				if (fireplace.burning.flueTemp < fireplace.burnPhases.phBurning.tempForBurnOut)
				{
					if (burningTimer)
					{
						burningTimer--;
					}
				}
				if (burningTimer == 0)
				{
					fireplace.burning.phase = BP3_BURN_OUT;
					fireplace.burning.step = BP3_STEP_INIT;
					break;
				}
				fireplace.burning.primFlapPos = airflap_compute(PRIM_F, fireplace.burning.flueTemp, fireplace.burning.rqFlueTemp);
			}
			break;

		/* Burn out */
		case BP3_BURN_OUT:
			if (fireplace.burning.step == BP3_STEP_INIT)
			{
				fireplace.burning.step = BP3_STEP_WAIT_TEMP;
				fireplace.burning.status = BS_LOW_FUEL;
				setBurningTimer(fireplace.burnPhases.phBurning.timeoutForBurnOut * 60);
			}
			fireplace.burning.primFlapPos = fireplace.burnPhases.phBurningOut.pflap;     				/* Primary Airflap */

			if (fireplace.burning.step == BP3_STEP_WAIT_TEMP)
			{
				if (fireplace.burning.flueTemp > (fireplace.burnPhases.phStartBurning.minTempForBurn)) /* skip to BURN_F2 */
				{
					fireplace.burning.phase = BP2_BURNING;
					fireplace.burning.step = BP2_STEP_INIT;
				}

				if (fireplace.burning.flueTemp > fireplace.burnPhases.phBurningOut.tempForGlowEmb+30)	/* Restart timer */
				{
					setBurningTimer(fireplace.burnPhases.phBurning.timeoutForBurnOut * 60);
				}

				if (fireplace.burning.flueTemp < fireplace.burnPhases.phBurningOut.tempForGlowEmb) 		/* skip to BP4_GLOW_EMBERS */
				{
					if (burningTimer)
					{
						burningTimer--;
					}
				}

				if (burningTimer == 0)
				{
					fireplace.burning.phase = BP4_GLOW_EMBERS;
					fireplace.burning.step = BP4_STEP_INIT;
				}
			}
			break;

		/* Glowing Embers */
		case BP4_GLOW_EMBERS:
			if (fireplace.burning.step == BP4_STEP_INIT)
			{
				setUserTimer1(fireplace.burnPhases.phGlowingEmbers.timeout * 60);
				fireplace.burning.step = BP4_STEP_WAIT_TIME;
				fireplace.burning.status = BS_BURNING;
			}
			fireplace.burning.primFlapPos = fireplace.burnPhases.phGlowingEmbers.pflap;  /* Primary Airflap */

			if (fireplace.burning.step == BP4_STEP_WAIT_TIME)
			{
				if (getUserTimer1() == 0)
				{
					fireplace.burning.phase = BP5_VENTIL;
					fireplace.burning.step = BP5_STEP_INIT;
					break;
				}

				if (fireplace.burning.flueTemp > (fireplace.burnPhases.phBurningOut.tempForGlowEmb + 100)) /* skip to BP3_BURN_OUT */
				{
					fireplace.burning.phase = BP3_BURN_OUT;
					fireplace.burning.step = BP3_STEP_INIT;
				}
			}
			break;

		/* Ventilation */
		case BP5_VENTIL:
			if (fireplace.burning.step == BP5_STEP_INIT)
			{
				setUserTimer1(fireplace.burnPhases.phVentilation.timeout * 60);
				fireplace.burning.step = BP5_STEP_WAIT_TIME;
				fireplace.burning.status = BS_STOP;
			}
			fireplace.burning.primFlapPos = 1000;     				/* Primary Airflap = 100.0% */

			if (fireplace.burning.step == BP5_STEP_WAIT_TIME)
			{
				if (getUserTimer1() == 0)
				{
					fireplace.burning.phase = BP0_STOP;
					fireplace.burning.step = 0;
				}
			}
			break;
	};


}



/******************************************************************************
** fireplace_secAirRegProcess
*******************************************************************************
* Description    : AirFlap Regulation precess
* Input          : None
* Return         : None
*******************************************************************************/
void fireplace_secAirRegProcess(void)
{
    uint16_t posF;

    if ((fireplace.burning.phase == BP2_BURNING) || (fireplace.burning.phase == BP3_BURN_OUT))
    {
    	if (fireplace.burning.flueTemp >= 700)      /* 70C */
		{
			lambda_heatingOn();
		}
		if (fireplace.burning.flueTemp < 650)       /* 65 */
		{
			lambda_heatingOff();
			pid_reset(&airflap[SEC_F].pid);
		}

    	if ((fireplace.burning.flueTemp >= 800) && (lambda.status & sLS_OK))
        {

            fireplace.burning.secFlapPos = airflap_compute(SEC_F, lambda.value, fireplace.burnPhases.phBurning.o2);
        }
        else
        {
        	//posF = getSecFlapFromTab(fireplace.burning.flueTemp / 10);
        	posF = 0;
            fireplace.burning.secFlapPos = posF;
            pid_reset(&airflap[SEC_F].pid);
        }
    }
    else
    {
    	lambda_heatingOff();
    	pid_reset(&airflap[SEC_F].pid);
    }

    if (fireplace.burning.phase == BP4_GLOW_EMBERS)
    {
        fireplace.burning.secFlapPos = fireplace.burnPhases.phGlowingEmbers.sflap;
    }
}



/******************************************************************************
** waterExch_install
*******************************************************************************
* Description    : Install Water exchanger (set default value and save to EEM )
* Input          : dist: distribution [ds_A, ds_B, ds_AB, ds_BA]
* Return         : None
*******************************************************************************/
void waterExch_install(void)
{
    waterExch_setDefault();
    waterExch_saveSettings();
}

/******************************************************************************
** waterExch_setDefault
*******************************************************************************
* Description    : Setting default values
* Input          : None
* Return         : None
*******************************************************************************/
void waterExch_setDefault(void)
{
	fireplace.waterExch.perStirr.enable = 0;
	fireplace.waterExch.perStirr.step = PSW_S_INIT;
	fireplace.waterExch.perStirr.period = 5;
	fireplace.waterExch.perStirr.runTime = 20;
	fireplace.waterExch.perStirr.phaseEn = PSW_PH_START_BURN | PSW_PH_BURN_OUT;
	fireplace.waterExch.perStirr.fRun = 0;

	fireplace.waterExch.minTemp.temp = 600;
	fireplace.waterExch.minTemp.hyst = 50;

	fireplace.waterExch.critTemp.temp = 900;
	fireplace.waterExch.critTemp.hyst = 50;
	fireplace.waterExch.critTemp.flap = 10;

	fireplace.waterExch.status = 0;
	fireplace.waterExch.pumpPwm = 0;
}

/******************************************************************************
** waterExch_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : None
* Return         : None
*******************************************************************************/
void waterExch_loadSettings(void)
{
    eem_readInt8(aEXCH_PSW_PERIOD, &fireplace.waterExch.perStirr.period);
    eem_readInt8(aEXCH_PSW_RUNTIME, &fireplace.waterExch.perStirr.runTime);
    eem_readInt8(aEXCH_PSW_PHASEEN, &fireplace.waterExch.perStirr.phaseEn);
    eem_readInt16(aEXCH_MT_TEMP, &fireplace.waterExch.minTemp.temp);
    eem_readInt8(aEXCH_MT_HYST, &fireplace.waterExch.minTemp.hyst);
    eem_readInt16(aEXCH_CT_TEMP, &fireplace.waterExch.critTemp.temp);
    eem_readInt8(aEXCH_CT_HYST, &fireplace.waterExch.critTemp.hyst);
    eem_readInt8(aEXCH_CT_FLAP, &fireplace.waterExch.critTemp.flap);
}

/******************************************************************************
** waterExch_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : None
* Return         : None
*******************************************************************************/
void waterExch_saveSettings(void)
{
    eem_writeInt8(aEXCH_PSW_PERIOD, fireplace.waterExch.perStirr.period);
    eem_writeInt8(aEXCH_PSW_RUNTIME, fireplace.waterExch.perStirr.runTime);
    eem_writeInt8(aEXCH_PSW_PHASEEN, fireplace.waterExch.perStirr.phaseEn);
    eem_writeInt16(aEXCH_MT_TEMP, fireplace.waterExch.minTemp.temp);
    eem_writeInt8(aEXCH_MT_HYST, fireplace.waterExch.minTemp.hyst);
    eem_writeInt16(aEXCH_CT_TEMP, fireplace.waterExch.critTemp.temp);
    eem_writeInt8(aEXCH_CT_HYST, fireplace.waterExch.critTemp.hyst);
    eem_writeInt8(aEXCH_CT_FLAP, fireplace.waterExch.critTemp.flap);
}

/******************************************************************************
** burnProf_setDefault
*******************************************************************************
* Description    : Setting default values
* Input          : None
* Return         : None
*******************************************************************************/
void burnProf_setDefault(void)
{
	fireplace.burnProfile.minFlueTemp = 1200;
	fireplace.burnProfile.maxFlueTemp = 1600;
	fireplace.burnProfile.rqFlueTemp = fireplace.burnProfile.minFlueTemp;
}

/******************************************************************************
** burnProf_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : None
* Return         : None
*******************************************************************************/
void burnProf_saveSettings(void)
{
	eem_writeInt16(aBPROF_MINT, fireplace.burnProfile.minFlueTemp);
	eem_writeInt16(aBPROF_MAXT, fireplace.burnProfile.maxFlueTemp);
}

/******************************************************************************
** burnProf_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : None
* Return         : None
*******************************************************************************/
void burnProf_loadSettings(void)
{
    eem_readInt16(aBPROF_MINT, &fireplace.burnProfile.minFlueTemp);
	eem_readInt16(aBPROF_MAXT, &fireplace.burnProfile.maxFlueTemp);
}

/******************************************************************************
** burnPhases_setDefault
*******************************************************************************
* Description    : Setting default values
* Input          : None
* Return         : None
*******************************************************************************/
void burnPhases_setDefault(void)
{
	fireplace.burnPhases.phStartBurning.timeout = 30;			// 30min
	fireplace.burnPhases.phStartBurning.minTempForBurn = 900;	// 90.0°C

	fireplace.burnPhases.phBurning.tempForBurnOut = 800;		// 80.0°C
	fireplace.burnPhases.phBurning.timeoutForBurnOut = 20;		// 20min
	fireplace.burnPhases.phBurning.o2 = 60;						// 6%

	fireplace.burnPhases.phBurningOut.tempForGlowEmb = 600;  	// 60.0°C
	fireplace.burnPhases.phBurningOut.timeoutForGlowEmb = 20;	// 20min
	fireplace.burnPhases.phBurningOut.pflap = 15;				// 15.0%

	fireplace.burnPhases.phGlowingEmbers.timeout = 10;			// 10hod
	fireplace.burnPhases.phGlowingEmbers.pflap = 10;			// 10.0%
	fireplace.burnPhases.phGlowingEmbers.sflap = 0;				// 0.0%

	fireplace.burnPhases.phVentilation.timeout = 1;				// 1min
	fireplace.burnPhases.phVentilation.pflap = 100;				// 100.0%
	fireplace.burnPhases.phVentilation.sflap = 100;				// 100.0%
}

/******************************************************************************
** burnPhases_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : None
* Return         : None
*******************************************************************************/
void burnPhases_saveSettings(void)
{
	eem_writeBlock(aBURN_PHASES_S, sizeof(burnPhases_st), (uint8_t*) &fireplace.burnPhases);
}

/******************************************************************************
** burnPhases_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : None
* Return         : None
*******************************************************************************/
void burnPhases_loadSettings(void)
{
	eem_readBlock(aBURN_PHASES_S, sizeof(burnPhases_st), (uint8_t*) &fireplace.burnPhases);

}
