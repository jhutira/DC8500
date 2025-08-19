#ifndef MODEL_HPP
#define MODEL_HPP

#include "main.h"
#include "system.h"
#include "reg.h"
#include "energy.h"
#include "fireplace.h"

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void GetClock(datetime_st *clock);
    void SetTime(uint8_t h, uint8_t m, uint8_t s);
    void SetDate(uint8_t d, uint8_t m, uint8_t y);

    uint8_t GetOutputValue(uint8_t n);
    uint8_t GetOutputMode(uint8_t n);
    void SetOutputMode(uint8_t n, uint8_t mode);
    void SetOutputInvMode(uint8_t n, uint8_t inv);

    uint8_t GetDInStatus(uint8_t n);
    uint8_t GetDInMode(uint8_t n);
    void SetDInMode(uint8_t n, uint8_t m);

    ain_st GetAIn(uint8_t n);
    lambda_st GetLS();
    flowmeter_st GetFlowMeter();

    contPump_st GetCModeP1();
    void SetCModeP1(contPump_st cm);

    uint8_t GetPumpContMode(void);
    uint8_t GetPumpContMinSpeed(void);
    uint8_t GetPumpContMaxSpeed(void);

    void HW_Get_PumpCont(uint8_t mode, uint8_t minS, uint8_t maxS);



    uint8_t GetFlapMode(uint8_t n);
    uint8_t GetFlapPos(uint8_t n);
    void SetFlapModeAndPos(uint8_t n, uint8_t man, uint8_t pos);

    void saveLanguageId(uint8_t id);
    uint8_t getDistrib();
    void setDistrib(uint8_t ds);

    burn_profile_st getBurnProfile();
    void setBurnProfile(burn_profile_st profile);
    void setBPrqFlueTemp(uint16_t t);


    waterExch_st getWaterExch();
    void setWaterExch(waterExch_st wex);

    burnPhases_st getBurnPhases();
    void setBurnPhases(burnPhases_st bph);

    pidConfig_st getFlapPidConfig(uint8_t nf);
    void setFlapPidConfig(uint8_t nf, pidConfig_st conf);

    void setDefaultSettings();

    uint8_t getRegScheme();
    void setRegScheme(uint8_t sch);

    door_st getFireplaceDoor();
    void setFireplaceDoor(door_st door);

    void setFireplaceDoorStatus(uint8_t st)
    {
    	fireplace.door.status = st;
    }

    void setDoorTimerM(uint16_t t)
	{
    	setDoorTimer(t);
	}

    uint16_t getModus()
    {
    	return modus;
    }

    void startBurning()
    {
    	fireplace_startBurning();
    }

    burning_st getFireplaceBurning()
    {
    	return fireplace.burning;
    }

    sound_st getSound()
	{
		return mSystem.sound;
	}

    void setSoundSett(sound_sett_st sett);
    void setSoundMute(uint8_t mute);

    disp_sett_st getDisplaySett()
	{
		return mSystem.display.sett;
	}

    void setDispSett(disp_sett_st sett);


    flowmeter_sett_st getFlowmeterSett()
    {
    	return flowmeter.sett;
    }

    void setFlowmeterSett(flowmeter_sett_st sett);

    void resetEnergyCnt();

    uint8_t getAccLevel()
	{
		return accum.level;
	}

    energy_st getEnergy()
	{
		return energy;
	}

protected:
    ModelListener* modelListener;

    uint8_t	tickFSB = 0;
    uint8_t	tickFSB2 = 0;
    uint8_t blink = 0;


};

#endif // MODEL_HPP
