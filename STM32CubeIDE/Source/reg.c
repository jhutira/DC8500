/*******************************************************************************
** reg
********************************************************************************
*
* regulation routines
*
*
* v1.0
*
* (c) 2.3.2025
*******************************************************************************/

#include "reg.h"

#include "eeprom.h"
#include "mem_map.h"

#include "digital.h"
#include "rtc.h"
#include "energy.h"

/******************************************************************************
** Defines
*******************************************************************************/

#define S_PSW_INIT     0
#define S_PSW_WAITRUN  1
#define S_PSW_WAITPER  2


/******************************************************************************
** Constants
*******************************************************************************/


/******************************************************************************
** Variables
*******************************************************************************/
uint8_t regSch;

uint16_t modus = 0;

uint8_t distrib;

uint8_t selAccum;

uint8_t extHeatSrcOn;

uint8_t fAntiBlockFunStart;

contPump_st contPump;

accum_st accum;

boiler_st boiler;

st_auxOut auxOut;

outdoorTemp_st outdoorTemp;


/******************************************************************************
 ** Functions
 *******************************************************************************/
void checkDoorSwitch(void);
void checkTempSensor(void);


/******************************************************************************
** reg_init
*******************************************************************************
* Description    :  Reg initialization
* Input          :  none
* Return         :  none
*******************************************************************************/
void reg_init(void)
{
	extHeatSrcOn = 0;
	fAntiBlockFunStart = 0;
	selAccum = ACCUM_A;
}

/******************************************************************************
** reg process
*******************************************************************************
* Description    :  Regulation process
* Input          :  none
* Return         :  none
*******************************************************************************/
void reg_process(void)
{
	uint16_t maxPos;
	datetime_st datetime;

	checkTempSensor();
	checkDoorSwitch();
	datetime = RTC_GetCalendar();

	fireplace.burning.flueTemp = ain[SN_E].t;
	fireplace_setBurnProfil();

	fireplace_regProcess();

	if (modus & mUSE_FLAP2)
	{
		fireplace_secAirRegProcess();
	}
	else
	{
		fireplace.burning.secFlapPos = 0;
	}

	airflap_movePosition(PRIM_F, fireplace.burning.primFlapPos);  /* 100.0  */
	airflap_movePosition(SEC_F, fireplace.burning.secFlapPos);

	/* Critical temperature */
	if (ain[SN_W].t >= fireplace.waterExch.critTemp.temp) fireplace.burning.fCriticTemp = 1;
	if (ain[SN_W].t <= (fireplace.waterExch.critTemp.temp - fireplace.waterExch.critTemp.hyst))


	if ((fireplace.door.status == DOOR_CLOSED) && (fireplace.burning.phase > BP0_STOP) && (fireplace.burning.fCriticTemp))
	{
		maxPos = fireplace.waterExch.critTemp.flap;
		if (airflap[0].pos > maxPos)
		{
			airflap_movePosition(PRIM_F, maxPos);
		}
	}

	/* External heating */
	if ((fireplace.burning.phase == BP2_BURNING) || (fireplace.burning.phase == BP3_BURN_OUT))
	{
		extHeatSrcOn = 0;
	}
	else
	{
		extHeatSrcOn = 1;
	}

	/* Anti-block protection for pumps */
	// Sunday 12:00 ->
	if ((datetime.WeekDay == 6) && (datetime.Hours == 12) && (datetime.Minutes == 0))
	{
		fAntiBlockFunStart = 1;
	}
	else
	{
		fAntiBlockFunStart = 0; // anti-block protect pump
	}

	/* Water exchanger */
	if (modus & mUSE_WATER_EXCH)
	{
		/* Periodic stirred water function */
		if ( ((fireplace.burning.phase == BP1_STBURN) && (fireplace.waterExch.perStirr.phaseEn & PSW_PH_START_BURN)) ||
			 ((fireplace.burning.phase == BP2_BURNING) && (fireplace.waterExch.perStirr.phaseEn & PSW_PH_BURN)) ||
			 ((fireplace.burning.phase == BP3_BURN_OUT) && (fireplace.waterExch.perStirr.phaseEn & PSW_PH_BURN_OUT)) )
		{
			fireplace.waterExch.perStirr.enable = 1;
		}
		else
		{
			fireplace.waterExch.perStirr.enable = 0;
		}

		waterExch_regProcess();
		if (((fireplace.burning.fCriticTemp) || (fireplace.waterExch.status & sWEXCH_TS_ERR)) && ((accum.status & sACCUM_FULL) == 0))  /* Overheat or SW error -> pump running on max speed */
		{
			fireplace.waterExch.pumpPwm = contPump.maxVal;
			selAccum = ACCUM_A;
		}

		if (modus & mUSE_2LOOPS)
		{
			if (modus & mUSE_PUMP2)
			{
				if (selAccum == ACCUM_A)
				{
					contPump.value = fireplace.waterExch.pumpPwm;
					out[OUT_P2].value = 0;
				}
				else
				if (selAccum == ACCUM_B)
				{
					contPump.value = 0;
					out[OUT_P2].value = fireplace.waterExch.pumpPwm;
				}
				else
				{
					contPump.value = 0;
					out[OUT_P2].value = 0;
				}
			}
			else
			{
				contPump.value = fireplace.waterExch.pumpPwm;
				if (selAccum == ACCUM_A)
				{
					out[OUT_P2].value = 0;
				}
				else
				if (selAccum == ACCUM_B)
				{
					out[OUT_P2].value = 100;
				}
			}
		}
		else
		{
			contPump.value = fireplace.waterExch.pumpPwm;
			if ((modus & mUSE_BOILER))
			{
				out[OUT_P2].value = boiler.pump_pwm;
			}
		}

	}

//	if (modus & mUSE_MIXVAL)
//	{
//		/* Week service */
//	status |= sWEXCH_TS_ERR;
//		week_regService();
//		if (week.state & sWEEK_ON)
//		{
//			eqreg_eneble(&eqReg);
//		}
//		else
//		{
//			eqreg_disable(&eqReg);
//		}
//		/* Equithermal regulation service */
//		eqreg_service(&eqReg, &eqReg.eqTab[0], SN_O, SN_M, SN_H);
//		if (valve3w_isManualMode(&mixValve) == 0)
//		{
//			valve3w_setPosition(&mixValve, eqReg.rqValvePos / 10);
//		}
//		//debug = eqReg.pidreg.pid.accrual;
//
//		/* Valve service */
//		valve3w_service(&mixValve);
//		eqReg.valvePos = mixValve.pos;
//		/* Outputs service */
//		// if ((out[OUT_CP].status & oMAN) == 0)     /* AUTO */
//		// {
//		//     if (eqReg.state & sEQREG_PUMP_RUN)
//		//     {
//		//         out[OUT_CP].value = 100;
//		//     }
//		//     else
//		//     {
//		//         out[OUT_CP].value = 0;
//		//     }
//		// }
//
//		// if ((out[OUT_MVO].status & oMAN) == 0)     /* AUTO */
//		// {
//		//     if (mixValve.state & sVALVE_MOV_OPEN)
//		//     {
//		//         out[OUT_MVO].value = 100;
//		//     }
//		//     else
//		//     {
//		//         out[OUT_MVO].value = 0;
//		//     }
//		// }
//		// if ((out[OUT_MVC].status & oMAN) == 0)     /* AUTO */
//		// {
//		//     if (mixValve.state & sVALVE_MOV_CLOSE)
//		//     {
//		//         out[OUT_MVC].value = 100;
//		//     }
//		//     else
//		//     {
//		//         out[OUT_MVC].value = 0;
//		//     }
//		// }
//
//		if (modus & mUSE_PUMP3)
//		{
//			if (eqReg.state & sEQREG_PUMP_RUN)
//			{
//				out[OUT_XY3].value = 100;
//			}
//			else
//			{
//				out[OUT_XY3].value = 0;
//			}
//		}
//		else
//		{
//			if (eqReg.state & sEQREG_PUMP_RUN)
//			{
//				out[OUT_CP].value = 100;
//			}
//			else
//			{
//				out[OUT_CP].value = 0;
//			}
//		}
//
//		if (mixValve.state & sVALVE_MOV_OPEN)
//		{
//			out[OUT_MVO].value = 100;
//		}
//		else
//		{
//			out[OUT_MVO].value = 0;
//		}
//
//		if (mixValve.state & sVALVE_MOV_CLOSE)
//		{
//			out[OUT_MVC].value = 100;
//		}
//		else
//		{
//			out[OUT_MVC].value = 0;
//		}
//	}

	/* AuxOut */
	if (auxOut.mode == mAO_EXTSRC)
	{
		if (extHeatSrcOn)
		{
			out[OUT_Y3].value = 100;
		}
		else
		{
			out[OUT_Y3].value = 0;
		}
	}
	else
	if (auxOut.mode == mAO_DOOR)
	{
		if (fireplace.door.status == DOOR_OPENED)
		{
			out[OUT_Y3].value = 100;
		}
		else
		{
			out[OUT_Y3].value = 0;
		}
	}
	else
	if (auxOut.mode == mAO_UNUSED)
	{
		out[OUT_Y3].value = 0;
	}


}

/******************************************************************************
** waterExch_regProcess
*******************************************************************************
* Description    : water exchanger regulation process
* Input          : None
* Return         : None
*******************************************************************************/
void waterExch_regProcess(void)
{
	static uint16_t circ_timer = 0;
	int16_t tempSW, tempMIN, hyst;
	uint8_t status;
	uint8_t sen_err;
	uint8_t pumpPwm;

	tempSW = ain[SN_W].t;
	tempMIN = (int16_t) fireplace.waterExch.minTemp.temp;
	hyst = (int16_t) fireplace.waterExch.minTemp.hyst;
	status = fireplace.waterExch.status;
	pumpPwm = 0;

	while (1)
	{
		/* Check accumulator tanks */
		if (modus & mUSE_ACCUM)
		{
			accum_check();
		}
		if (modus & mUSE_BOILER)
		{
			boiler_check();
		}

		/* Tmin */
		if (tempSW >= tempMIN)
		{
			status |= sTMIN;
		}
		else
		if (tempSW < (tempMIN - hyst))
		{
			status &= ~(sTMIN);
		}

		/* Distribution */
		sen_err = 0;
		selAccum = ACCUM_NONE;

		if (distrib == DS_HEAT)
		{
			if (modus & mUSE_ACCUM)
			{
				if ( ((accum.status & sACCUM_FULL) == 0) && sensorOk(SN_A) )
				{
					selAccum = ACCUM_A;
					accum_regProcess(status & sTMIN);
					pumpPwm = accum.pump_pwm;
				}
				/* Check sensor */
				if (sensorErr(SN_A))
				{
					sen_err = 1;
				}
			}
			else
			{
				if (status & sTMIN)
				{
					selAccum = ACCUM_A;
					pumpPwm = contPump.maxVal;
				}
			}
		}
		else
		if (distrib == DS_WATER)
		{
			if ( ((boiler.status & sACCUM_FULL) == 0) && sensorOk(SN_B) && sensorOk(boiler.setup.sen_src) )
			{
				selAccum = ACCUM_B;
				boiler_regProcess(status & sTMIN);
				pumpPwm = boiler.pump_pwm;
			}
			/* Check sensor */
			if (sensorErr(SN_B) || sensorErr(boiler.setup.sen_src) )
			{
				sen_err = 1;
			}
		}
		else
		if (distrib == DS_WATER_HEAT)
		{
			if ( ((boiler.status & sACCUM_FULL) == 0) && sensorOk(SN_B) && sensorOk(boiler.setup.sen_src) )
			{
				selAccum = ACCUM_B;
				boiler_regProcess(status & sTMIN);
				pumpPwm = boiler.pump_pwm;
			}
			else
			{
				if (modus & mUSE_ACCUM)
				{
					if ( ((accum.status & sACCUM_FULL) == 0) && sensorOk(SN_A) )
					{
						selAccum = ACCUM_A;
						accum_regProcess(status & sTMIN);
						pumpPwm = accum.pump_pwm;
					}
				}
				else
				{
					if (status & sTMIN)
					{
						selAccum = ACCUM_A;
						pumpPwm = contPump.maxVal;
					}
				}
			}

			/* Check sensor */
			if (selAccum == ACCUM_NONE)
			{
				if ((modus & mUSE_ACCUM) && (sensorErr(SN_A)))
				{
					sen_err = 1;
				}
				if (sensorErr(SN_B) || sensorErr(boiler.setup.sen_src))
				{
					sen_err = 1;
				}
			}
		}
//		else
//		if (waterExch.distrib == DS_P_WATER_HEAT)
//		{
//			/* Check sensor */
//			if (sensorErr(SN_A))
//			{
//				sen_err = 1;
//			}
//			if ( ((accum.status & sACCUM_FULL) == 0) && sensorOk(SN_A) )
//			{
//				selAccum = ACCUM_A;
//				accum_regService(status & stTMIN);
//				pumpPwm = accum.pump_pwm;
//			}
//
//			if (sensorErr(SN_B) || sensorErr(boiler.setup.sen_src))
//			{
//				sen_err = 1;
//			}
//			if ( ((boiler.status & sACCUM_FULL) == 0) && (sensorOk(SN_A)) && (sensorOk(boiler.setup.sen_src)) )
//			{
//				//selAccum = ACCUM_B;
//				boiler_regService(state & stTMIN);
//			}
//			else
//			{
//				boiler.pump_pwm = 0;
//			}11
//
//		}

		/* Check sensor */
		if (sensorErr(SN_W) || (sen_err != 0))
		{
			status |= sWEXCH_TS_ERR;
			selAccum = ACCUM_NONE;
		}
		else
		{
			status &= ~(sWEXCH_TS_ERR);
		}


		/* Periodic stirred water function */
		if ((fireplace.waterExch.perStirr.enable) && ((status & sTMIN) == 0))
		{
			if (fireplace.waterExch.perStirr.step == S_PSW_INIT)
			{
				circ_timer = fireplace.waterExch.perStirr.period;
				fireplace.waterExch.perStirr.step = S_PSW_WAITPER;
			}

			if (fireplace.waterExch.perStirr.step == S_PSW_WAITPER)
			{
				if ((fTick_1min) && (circ_timer))
				{
					circ_timer--;
				}
				if (circ_timer == 0)
				{
					fireplace.waterExch.perStirr.fRun = 1;
					circ_timer = fireplace.waterExch.perStirr.runTime;
					fireplace.waterExch.perStirr.step = S_PSW_WAITRUN;
				}

			}

			if (fireplace.waterExch.perStirr.step == S_PSW_WAITRUN)
			{
				if ((fTick_1sec) && (circ_timer))
				{
					circ_timer--;
				}
				if (circ_timer == 0)
				{
					fireplace.waterExch.perStirr.fRun = 0;
					fireplace.waterExch.perStirr.step = S_PSW_INIT;
				}
			}
		}
		else
		{
			fireplace.waterExch.perStirr.step = S_PSW_INIT;
			fireplace.waterExch.perStirr.fRun = 0;
		}
		break;
	}


	/* Periodic stirred water function */
	if (fireplace.waterExch.perStirr.fRun)
	{
		pumpPwm = contPump.maxVal;
		selAccum = ACCUM_A;
	}

	/* Anti-block protection for pumps */
	if (fAntiBlockFunStart)
	{
		pumpPwm = contPump.maxVal;
		selAccum = ACCUM_A;
	}

	if (pumpPwm > 0) status |= sWEXCH_PUMP_ON;
	  else status &= ~(sWEXCH_PUMP_ON);

	fireplace.waterExch.status = status;
	fireplace.waterExch.pumpPwm = pumpPwm;
}




/******************************************************************************
** checkDoorSwitch
*******************************************************************************
* Description    :  Check door switch
* Input          :  none
* Return         :  none
*******************************************************************************/
void checkDoorSwitch(void)
{
	if (fireplace.door.usedSwitch == 0)
    {
        return;
    }

    if (din[DI2].status & iSTAT)
    {
    	fireplace.door.status = DOOR_CLOSED;
    }
    else
    {
    	fireplace.door.status = DOOR_OPENED;
    }

    if ((fireplace.door.status_prev == DOOR_OPENED) && (fireplace.door.status == DOOR_CLOSED))
    {
        fireplace_startBurning();
    }
    fireplace.door.status_prev = fireplace.door.status;
}


/******************************************************************************
** checkTempSensor
*******************************************************************************
* Description    :  Check Temperature sensor
* Input          :  none
* Return         :  none
*******************************************************************************/
void checkTempSensor(void)
{
//    int16_t hyst;
//    uint8_t sen_err;
//
//    sen_err = 0;
    // Emergency stops
//    if (burning.phase == BURN_F0_ERR)
//    {
//        if ((regMode == rmFIRE_WATER) || (regMode == rmFIRE_LS_WATER))
//        {
//            if (waterExch.state & stWEXCH_ERR)
//            {
//                sen_err = 1;
//            }
//        }
//        if (sensorOk(SN_E) && (sen_err == 0))
//        {
//            burning.fRestartProcess = 1;        /* restart process */
//        }
//    }
//    else
//    {
//        if ((regMode == rmFIRE_WATER) || (regMode == rmFIRE_LS_WATER))
//        {
//            if (waterExch.state & stWEXCH_ERR)
//            {
//                sen_err = 1;
//            }
//        }
//        if ((sensorStatus(SN_E) & SN_ERROR) || (sen_err != 0))
//        {
//            burning.lastPhase = burning.phase;  /* save last phase */
//            burning.phase = BURN_F0_ERR;
//        }
//    }
//
//    /* test critical temperature */
//    hyst = (int16_t) burning.critTHyst * 10;
//    if (ain[SN_W].t >= burning.critTemp)
//    {
//        burning.fCritTemp = 1;
//    }
//    if (ain[SN_W].t <= (burning.critTemp - hyst))
//    {
//        burning.fCritTemp = 0;
//    }
}

/******************************************************************************
** contPump_install
*******************************************************************************
* Description    : Install contPump
* Input          : None
* Return         : None
*******************************************************************************/
void contPump_install(void)
{
	contPump_setDefault();
	contPump_saveSettings();
}

/******************************************************************************
 ** contPump_setDefault
 *******************************************************************************
 * Description    : Setting to default values
 * Input          : None
 * Return         : None
 *******************************************************************************/
void contPump_setDefault(void)
{
	contPump.mode = CO_M_PWM;
	contPump.minVal = 20;
	contPump.maxVal = 100;
}

/******************************************************************************
** contPump_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : None
* Return         : None
*******************************************************************************/
void contPump_loadSettings(void)
{
	eem_readInt8(aCONT_PUMP, &contPump.mode);
	eem_readInt8(aCONT_PUMP + 1, &contPump.minVal);
	eem_readInt8(aCONT_PUMP + 2, &contPump.maxVal);
}

/******************************************************************************
** contPump_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : None
* Return         : None
*******************************************************************************/
void contPump_saveSettings(void)
{
	eem_writeInt8(aCONT_PUMP, contPump.mode);
	eem_writeInt8(aCONT_PUMP + 1, contPump.minVal);
	eem_writeInt8(aCONT_PUMP + 2, contPump.maxVal);
}

/******************************************************************************
** accum_install
*******************************************************************************
* Description    : Install accum
* Input          : None
* Return         : None
*******************************************************************************/
void accum_install(void)
{
    accum_setDefault();
    accum_saveSettings();
}

/******************************************************************************
** accum_setDefault
*******************************************************************************
* Description    : Setting default values
* Input          : None
* Return         : None
*******************************************************************************/
void accum_setDefault(void)
{
	accum.setup.deltaOn = 10;
	accum.setup.deltaOff = 2;
	accum.setup.rqTemp = 850;
	accum.setup.hyst = 5;

	accum.mode = 0;
    accum.status = 0;
    accum.temp = 0;
    accum.level = 0;
    accum.pump_pwm = 0;
}

/******************************************************************************
** accum_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : None
* Return         : None
*******************************************************************************/
void accum_loadSettings(void)
{
	eem_readBlock(aACCUM_SETUP, sizeof(accum_setup_st), (uint8_t*) &accum.setup);
}

/******************************************************************************
** accum_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : None
* Return         : None
*******************************************************************************/
void accum_saveSettings(void)
{
	eem_writeBlock(aACCUM_SETUP, sizeof(accum_setup_st), (uint8_t*) &accum.setup);
}

/******************************************************************************
** accum_check
*******************************************************************************
* Description    : Check Accumulator tanks state
* Input          : None
* Return         : None
*******************************************************************************/
void accum_check(void)
{
    int16_t rT;
    uint32_t val32;

    /* is Full? */
    accum.temp = ain[SN_A].t;

    rT = (int16_t) accum.setup.rqTemp;

    if (accum.temp >= rT)
    {
        accum.status |= sACCUM_FULL;
    }
    if (accum.temp < (rT - accum.setup.hyst))
    {
        accum.status &= ~(sACCUM_FULL);
    }

    /* Level */
    if (accum.temp > 0)
    {
        val32 = ((uint32_t)accum.temp * 100) / accum.setup.rqTemp;
    	accum.level = val32 & 0xFFFF;
    }
    else
    {
        accum.level = 0;
    }

    if (accum.level >= 80)
    {
        accum.status |= sACCUM_LEVEL80;
    }
    if (accum.level <= 77)
    {
        accum.status &= ~(sACCUM_LEVEL80);
    }
}

/******************************************************************************
** accum_regProcess
*******************************************************************************
* Description    : Regulation process
* Input          : en: enable process
* Return         : None
*******************************************************************************/
void accum_regProcess(uint8_t en)
{
    int16_t dT;
    int16_t dTOn, dTOff, dTPwm;
    int32_t val32;

    if (sensorErr(SN_W) || (sensorErr(SN_A)))
    {
        accum.status &= ~(sACCUM_PUMP_ON);
        accum.pump_pwm = 0;
        return;
    }



    accum.temp = ain[SN_A].t;
    dT = ain[SN_W].t - ain[SN_A].t;
    dTOn = (int16_t)accum.setup.deltaOn;
    dTOff = (int16_t)accum.setup.deltaOff;

    if ((en != 0) && ((accum.status & sACCUM_FULL) == 0))
    {
        if (dT <= dTOff)
        {
            accum.status &= ~(sACCUM_PUMP_ON);
            accum.pump_pwm = 0;
        }
        if (dT >= dTOn)
        {
            accum.status |= sACCUM_PUMP_ON;
            accum.pump_pwm = 100;
        }
        if (accum.status & sACCUM_PUMP_ON)
        {
            dTPwm = dTOff + (dTOn - dTOff) / 2;
            if (dT <= dTPwm)
            {
                accum.pump_pwm = contPump.minVal;
            }
            else
            {
                val32 = dT - dTPwm;
                val32 *= contPump.maxVal - contPump.minVal;
                val32 /= (dTOn - dTPwm) / 2;
                val32 += contPump.minVal;
                if (val32 > contPump.maxVal)
                {
                    val32 = contPump.maxVal;
                }
                accum.pump_pwm = val32 & 0xFF;
            }
        }
    }
    else
    {
        accum.status &= ~(sACCUM_PUMP_ON);
        accum.pump_pwm = 0;
    }
}

/******************************************************************************
** boiler_install
*******************************************************************************
* Description    : Install boiler
* Input          : s_src: number a source sensor [SN_W..SN_B]
*                : pump_cnt: number a pump control [0, 1, 2]
* Return         : None
*******************************************************************************/
void boiler_install(uint8_t s_src, uint8_t pump_cnt)
{
    boiler_setDefault();
    boiler.setup.sen_src = s_src;
    boiler.setup.pump_cnt = pump_cnt;
    boiler_saveSettings();
}

/******************************************************************************
** boiler_setDefault
*******************************************************************************
* Description    : Setting default values
* Input          : None
* Return         : None
*******************************************************************************/
void boiler_setDefault(void)
{
	boiler.setup.sen_src = SN_A;
	boiler.setup.pump_cnt = 0;
	boiler.setup.deltaOn = 10;
	boiler.setup.deltaOff = 2;
	boiler.setup.rqTemp = 60;
	boiler.setup.hyst = 10;

	boiler.mode = 0;
    boiler.status = 0;
    boiler.temp = 0;
    boiler.pump_pwm = 0;
    boiler.level = 0;
}

/******************************************************************************
** boiler_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : None
* Return         : None
*******************************************************************************/
void boiler_loadSettings(void)
{
	eem_readBlock(aBOILER_SETUP, sizeof(boiler_setup_st), (uint8_t*) &boiler.setup);
}

/******************************************************************************
** boiler_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : None
* Return         : None
*******************************************************************************/
void boiler_saveSettings(void)
{
	eem_writeBlock(aBOILER_SETUP, sizeof(boiler_setup_st), (uint8_t*) &boiler.setup);
}
/******************************************************************************
** boiler_check
*******************************************************************************
* Description    : Check boiler state
* Input          : None
* Return         : None
*******************************************************************************/
void boiler_check(void)
{
    int16_t rT;
    uint32_t val32;

    /* is Full? */
    boiler.temp = ain[SN_B].t;
    rT = (int16_t) boiler.setup.rqTemp;

    if (boiler.temp >= rT)
    {
        boiler.status |= sACCUM_FULL;
    }
    if (boiler.temp < (rT - boiler.setup.hyst))
    {
        boiler.status &= ~(sACCUM_FULL);
    }

    /* Level */
    if (boiler.temp > 0)
    {
        val32 = ((uint32_t)boiler.temp * 100) / boiler.setup.rqTemp;
        boiler.level = val32 & 0xFFFF;
    }
    else
    {
        boiler.level = 0;
    }

    if (boiler.level >= 80)
    {
        boiler.status |= sACCUM_LEVEL80;
    }
    if (boiler.level <= 77)
    {
        boiler.status &= ~(sACCUM_LEVEL80);
    }
}

/******************************************************************************
** boiler_regProcess
*******************************************************************************
* Description    : Regulation proces
* Input          : en: enable process
* Return         : None
*******************************************************************************/
void boiler_regProcess(uint8_t en)
{
    int16_t dT;
    int16_t dTOn, dTOff, dTPwm;
    int32_t val32;

    if (sensorErr(boiler.setup.sen_src) || (sensorErr(SN_B)))
    {
        boiler.status &= ~(sBOILER_PUMP_ON);
        boiler.pump_pwm = 0;
        return;
    }

    boiler.temp = ain[SN_B].t;
    dT = ain[boiler.setup.sen_src].t - ain[SN_B].t;
    dTOn = (int16_t)boiler.setup.deltaOn;
    dTOff = (int16_t)boiler.setup.deltaOff;

    if ((en != 0) && ((boiler.status & sACCUM_FULL) == 0))
    {
        if (dT <= dTOff)
        {
            boiler.status &= ~(sBOILER_PUMP_ON);
            boiler.pump_pwm = 0;
        }
        if (dT >= dTOn)
        {
            boiler.status |= sBOILER_PUMP_ON;
            boiler.pump_pwm = 100;
        }
        if ((boiler.setup.pump_cnt > 0) && (boiler.status & sBOILER_PUMP_ON))
        {
            dTPwm = dTOff + (dTOn - dTOff) / 2;
            if (dT <= dTPwm)
            {
                boiler.pump_pwm = contPump.minVal;
            }
            else
            {
                val32 = dT - dTPwm;
                val32 *= contPump.maxVal - contPump.minVal;
                val32 /= (dTOn - dTPwm) / 2;
                val32 += contPump.minVal;
                if (val32 > contPump.maxVal)
                {
                    val32 = contPump.maxVal;
                }
                boiler.pump_pwm = val32 & 0xFF;
            }
        }
    }
    else
    {
        boiler.status &= ~(sBOILER_PUMP_ON);
        boiler.pump_pwm = 0;
    }
}


/******************************************************************************
** oTemp_install
*******************************************************************************
* Description    : Install oTemp
* Input          : None
* Return         : None
*******************************************************************************/
void oTemp_install(void)
{
	oTemp_setDefault();
	oTemp_saveSettings();
}

/******************************************************************************
** oTemp_setDefault
*******************************************************************************
* Description    : Setting default values
* Input          : None
* Return         : None
*******************************************************************************/
void oTemp_setDefault(void)
{
	outdoorTemp.view = 0;
}

/******************************************************************************
** oTemp_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : None
* Return         : None
*******************************************************************************/
void oTemp_loadSettings(void)
{
	eem_readBlock(aOUTDOOR_TEMP, sizeof(outdoorTemp_st), (uint8_t*)&outdoorTemp);
}

/******************************************************************************
** oTemp_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : None
* Return         : None
*******************************************************************************/
void oTemp_saveSettings(void)
{
	eem_writeBlock(aOUTDOOR_TEMP, sizeof(outdoorTemp_st), (uint8_t*)&outdoorTemp);
}



/******************************************************************************
** auxout_install
*******************************************************************************
* Description    : Install AuxOut (set default value and save to EEM )
* Input          : mode: set value
* Return         : None
*******************************************************************************/
void auxout_install(uint8_t mode)
{
    auxout_setDefault();
    auxOut.mode = mode;
    auxout_saveSettings();
}

/******************************************************************************
** auxout_setDefault
*******************************************************************************
* Description    : Setting default values
* Input          : None
* Return         : None
*******************************************************************************/
void auxout_setDefault(void)
{
    auxOut.mode = mAO_UNUSED;
    auxOut.on = 0;
}

/******************************************************************************
** auxout_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : None
* Return         : None
*******************************************************************************/
void auxout_loadSettings(void)
{
    eem_readInt8(aAUX_OUT, &auxOut.mode);
}

/******************************************************************************
** auxout_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : None
* Return         : None
*******************************************************************************/
void auxout_saveSettings(void)
{
    eem_writeInt8(aAUX_OUT, auxOut.mode);
}

/******************************************************************************
** io_service
*******************************************************************************
* Description    : IO Service
* Input          : None
			status |= sWEXCH_TS_ERR;
* Return         : None
*******************************************************************************/
void io_service(void)
{
	uint8_t i;

    for (i = 0; i < OUT_COUNT; i++)
    {
        if (out[i].mode & oMAN)
        {
            if (out[i].mode & oON)
            {
                if (i == 0) out[i].value = contPump.maxVal;
                  else out[i].value = 100;
            }
            else
            {
                out[i].value = 0;
            }
        }
        else
        {
        	if (i == 0) out[0].value = contPump.value;

        	if (out[i].value)
            {
                out[i].mode |= oON;
            }
            else
            {
                out[i].mode &= ~oON;
            }
        }
        out[i].out_value = out[i].value;

        if (out[i].mode & oINV)
        {
            if (out[i].out_value)
            {
                out[i].out_value = 0;
            }
            else
            {
                out[i].out_value = 100;
            }
        }
    }
    aout[0].value = out[0].out_value;
}

/******************************************************************************
** reg_setRegScheme
*******************************************************************************
* Description    : Set regulation scheme
* Input          : init: default init
* Return         : None
*******************************************************************************/
void reg_setRegScheme(uint8_t init)
{
	modus = 0;

	if (init)
	{
		fireplace_install();
		digital_install();
		lambda_init();
		contPump_install();

		airflap_install(PRIM_F);
		airflap_install(SEC_F);

		pid_install(&airflap[PRIM_F].pid);
		pid_install(&airflap[SEC_F].pid);

		flowmeter_install();

		oTemp_install();

	}
	_setSensorIsUsed(SN_E);
	_setSensorIsUsed(SN_W);
	_setSensorIsUsed(SN_X);
	_clrSensorIsUsed(SN_A);
	_clrSensorIsUsed(SN_H);
	_clrSensorIsUsed(SN_M);
	_clrSensorIsUsed(SN_R);
	_clrSensorIsUsed(SN_B);
	_clrSensorIsUsed(SN_O);

	switch (regSch)
	{
		case SCH_01:
			modus = mUSE_WATER_EXCH | mUSE_ENG_MEAS | mUSE_PUMP1 | mUSE_FLAP2 | mUSE_ACCUM;
			_setSensorIsUsed(SN_A);
			break;

		case SCH_02:
			modus = mUSE_WATER_EXCH | mUSE_ENG_MEAS | mUSE_PUMP1 | mUSE_FLAP2 | mUSE_ACCUM | mUSE_VAL_MIX | mUSE_PUMP2;
			_setSensorIsUsed(SN_A);
			_setSensorIsUsed(SN_H);
			_setSensorIsUsed(SN_M);
			_setSensorIsUsed(SN_O);
			break;

		case SCH_03:
			modus = mUSE_WATER_EXCH | mUSE_ENG_MEAS | mUSE_PUMP1 | mUSE_FLAP2 | mUSE_ACCUM  | mUSE_BOILER  | mUSE_2LOOPS | mUSE_VAL_AB;
			_setSensorIsUsed(SN_A);
			_setSensorIsUsed(SN_B);
			break;

		case SCH_04:
			modus = mUSE_WATER_EXCH | mUSE_ENG_MEAS | mUSE_PUMP1 | mUSE_FLAP2 | mUSE_ACCUM  | mUSE_BOILER  | mUSE_2LOOPS | mUSE_PUMP2;
			_setSensorIsUsed(SN_A);
			_setSensorIsUsed(SN_B);
			break;

		case SCH_05:
			modus = mUSE_WATER_EXCH | mUSE_ENG_MEAS | mUSE_PUMP1 | mUSE_FLAP2 | mUSE_BOILER  | mUSE_2LOOPS | mUSE_PUMP2;
			_setSensorIsUsed(SN_B);
			break;

		case SCH_06:
			modus = mUSE_WATER_EXCH | mUSE_ENG_MEAS | mUSE_PUMP1 | mUSE_FLAP2 | mUSE_BOILER  | mUSE_2LOOPS | mUSE_VAL_AB;
			_setSensorIsUsed(SN_B);
			break;

		case SCH_07:
			modus = mUSE_WATER_EXCH | mUSE_ENG_MEAS | mUSE_PUMP1 | mUSE_FLAP2 | mUSE_ACCUM | mUSE_BOILER  | mUSE_2LOOPS | mUSE_PUMP2;
			_setSensorIsUsed(SN_A);
			_setSensorIsUsed(SN_H);
			_setSensorIsUsed(SN_B);
			break;

		case SCH_08:
			modus = mUSE_WATER_EXCH | mUSE_ENG_MEAS | mUSE_PUMP1 | mUSE_FLAP2 | mUSE_ACCUM | mUSE_BOILER  | mUSE_2LOOPS | mUSE_PUMP2 | mUSE_VAL_MIX | mUSE_PUMP2;
			_setSensorIsUsed(SN_A);
			_setSensorIsUsed(SN_H);
			_setSensorIsUsed(SN_B);
			_setSensorIsUsed(SN_M);
			_setSensorIsUsed(SN_O);
			break;

		case SCH_09:
			modus = mUSE_FLAP2;
			_clrSensorIsUsed(SN_W);
			_clrSensorIsUsed(SN_X);
			break;
	}

	if (outdoorTemp.view) _setSensorIsUsed(SN_O);
	if ((modus & mUSE_ENG_MEAS) == 0)
	{
		energy.sett.view = 0;
		flowmeter.sett.view = 0;
	}

}

