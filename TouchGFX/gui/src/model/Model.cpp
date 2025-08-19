#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <main_util.h>
#include <rtc.h>

#include "eeprom.h"
#include "mem_map.h"
#include "reg.h"
#include "buzzer.h"
#include "backlight.h"
#include "system.h"
#include <stdio.h>

#include <uart_log.h>


extern "C" {

	extern uint16_t tick_1s;
	extern datetime_st RTC_GetCalendar(void);
	extern void RTC_SetTime(uint8_t h, uint8_t m, uint8_t s);
	extern void RTC_SetDate(uint8_t d, uint8_t m, uint8_t y);

	extern void LED_G_Toggle(void);
}

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	if (fClock_change != 0)
	{
		fClock_change = 0;
		modelListener->updateClock();
	}

	tickFSB++;
	if (tickFSB > 10)
	{
		tickFSB = 0;
		modelListener->updateSensors();
		modelListener->updateOutputs();

		modelListener->updatePAirFlap();
		modelListener->updateSAirFlap();

		modelListener->updateRegStatus();

		modelListener->updateEnergy();
		energy_saveAccEng();

		modelListener->updateDebug();

	}

	tickFSB2++;
	if (tickFSB2 > 30)
	{
		tickFSB2 = 0;
		blink = !blink;
		modelListener->updateIcons(blink);
	}
}

void Model::GetClock(datetime_st *clock)
{
	//*datetime = RTC_GetCalendar();
	*clock = datetime;
}

void Model::SetTime(uint8_t h, uint8_t m, uint8_t s)
{
	RTC_SetTime( h, m, s);
}

void Model::SetDate(uint8_t d, uint8_t m, uint8_t y)
{
	RTC_SetDate( d, m, y);
}

uint8_t Model::GetOutputValue(uint8_t n)
{
	return out[n].out_value;
}

uint8_t Model::GetOutputMode(uint8_t n)
{
	return out[n].mode;
}

void Model::SetOutputMode(uint8_t n, uint8_t mode)
{
	if (mode == 2) out[n].mode &= ~(oMAN | oON);
	if (mode == 1) out[n].mode |= oMAN | oON;
	if (mode == 0)
	{
		out[n].mode |= oMAN;
		out[n].mode &= ~(oON);
	}
	digital_saveOneOutputMode(n);
}

void Model::SetOutputInvMode(uint8_t n, uint8_t inv)
{
	if (inv) out[n].mode |= oINV; else out[n].mode &= ~(oINV);

	digital_saveOneOutputMode(n);
}


/* Din */
uint8_t Model::GetDInStatus(uint8_t n)
{
	return din[n].status;
}

uint8_t Model::GetDInMode(uint8_t n)
{
	return din[n].mode;
}

void Model::SetDInMode(uint8_t n, uint8_t m)
{
	din[n].mode = m;
	digital_saveOneInputMode(n);
}

/* TempSensor */
ain_st Model::GetAIn(uint8_t n)
{
	return ain[n];
}

/* Lambda Sensor */
lambda_st Model::GetLS()
{
	return lambda;
}

/* FlowMeter */
flowmeter_st Model::GetFlowMeter()
{
	return flowmeter;
}

/* CMode P1 */
contPump_st Model::GetCModeP1()
{
	return contPump;
}

void Model::SetCModeP1(contPump_st cm)
{
	contPump.mode = cm.mode;
	contPump.minVal = cm.minVal;
	contPump.maxVal = cm.maxVal;
	contPump_saveSettings();
}



/* Flap */
uint8_t Model::GetFlapMode(uint8_t n)
{
	return airflap[n].mode;
}

uint8_t Model::GetFlapPos(uint8_t n)
{
	return airflap[n].pos;
}

void Model::SetFlapModeAndPos(uint8_t n, uint8_t man, uint8_t pos)
{
	if (man) airflap[n].mode |= mMAN;
	  else airflap[n].mode &= ~mMAN;
	airflap[n].pos = pos;
	airflap_saveMode(n);
}


void Model::saveLanguageId(uint8_t id)
{
	lang_id = id;
	eem_writeInt8(aLANG_ID, lang_id);
}

uint8_t Model::getDistrib()
{
	return distrib;
}

void Model::setDistrib(uint8_t ds)
{
	distrib = ds;
	eem_writeInt8(aDISTRIB, distrib);
}

burn_profile_st Model::getBurnProfile()
{
	return fireplace.burnProfile;
}

void Model::setBurnProfile(burn_profile_st profile)
{
	fireplace.burnProfile.minFlueTemp = profile.minFlueTemp;
	fireplace.burnProfile.maxFlueTemp = profile.maxFlueTemp;
	fireplace.burnProfile.rqFlueTemp = fireplace.burnProfile.minFlueTemp;
	burnProf_saveSettings();
}

void Model::setBPrqFlueTemp(uint16_t t)
{
	fireplace.burnProfile.rqFlueTemp = t;
	eem_writeInt16(aBPROF_RQT, fireplace.burnProfile.rqFlueTemp);
}


waterExch_st Model::getWaterExch()
{
	return fireplace.waterExch;
}

void Model::setWaterExch(waterExch_st wex)
{
	fireplace.waterExch = wex;
	waterExch_saveSettings();
}


burnPhases_st Model::getBurnPhases()
{
	return fireplace.burnPhases;
}

void Model::setBurnPhases(burnPhases_st bph)
{
	fireplace.burnPhases = bph;
	burnPhases_saveSettings();
}


pidConfig_st Model::getFlapPidConfig(uint8_t nf)
{
	return airflap[nf].pid.config;
}

void Model::setFlapPidConfig(uint8_t nf, pidConfig_st conf)
{
	if (nf == PRIM_F)
	{
		airflap[PRIM_F].pid.config = conf;
		pid_saveSettings(&airflap[PRIM_F].pid, aPFLAP_PID);
	}
	if (nf == SEC_F)
	{
		airflap[SEC_F].pid.config = conf;
		pid_saveSettings(&airflap[SEC_F].pid, aSFLAP_PID);
	}
}

void Model::setDefaultSettings()
{
	system_setDefault();
	system_saveData();
}

uint8_t Model::getRegScheme()
{
	return regSch;
}

void Model::setRegScheme(uint8_t sch)
{
	regSch = sch;
	eem_writeInt8(aREG_SCH, regSch);
	reg_setRegScheme(1);
}

door_st Model::getFireplaceDoor()
{
	return fireplace.door;
}

void Model::setFireplaceDoor(door_st door)
{
	fireplace.door.usedSwitch = door.usedSwitch;
	fireplace.door.timeout = door.timeout;

	eem_writeInt8(aDOOR_SW, fireplace.door.usedSwitch);
	eem_writeInt16(aDOOR_TIMEOUT, fireplace.door.timeout);
}

void Model::setSoundMute(uint8_t mute)
{
	mSystem.sound.mute = mute;
	eem_writeInt8(aSOUND_MUTE, mSystem.sound.mute);
}

void Model::setSoundSett(sound_sett_st sett)
{
	mSystem.sound.sett = sett;
	eem_writeBlock(aSOUND_SETT, sizeof(sound_sett_st), (uint8_t*)&mSystem.sound.sett);
}

void Model::setDispSett(disp_sett_st sett)
{
	mSystem.display.sett = sett;
	eem_writeBlock(aDISP_SETT, sizeof(disp_sett_st), (uint8_t*)&mSystem.display.sett);

	backlight_pwm(mSystem.display.sett.backlight);
	mSystem.display.timer = 0;
}


void Model::setFlowmeterSett(flowmeter_sett_st sett)
{
	flowmeter.sett = sett;
	eem_writeBlock(aFLOWM_SETT, sizeof(flowmeter_sett_st), (uint8_t*)&flowmeter.sett);
}

void Model::resetEnergyCnt()
{
	energy.accEng = 0;
	energy_saveAccEng();
}



