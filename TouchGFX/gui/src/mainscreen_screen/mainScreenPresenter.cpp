#include <gui/mainscreen_screen/mainScreenView.hpp>
#include <gui/mainscreen_screen/mainScreenPresenter.hpp>
#include <gui/common/FrontendApplication.hpp>

mainScreenPresenter::mainScreenPresenter(mainScreenView& v)
    : view(v)
{

}

void mainScreenPresenter::activate()
{
	burn_profile_st prof;
	sound_st sound;

	prof = model->getBurnProfile();
	view.updateProfileSld(prof.minFlueTemp/10, prof.maxFlueTemp/10, prof.rqFlueTemp/10);

	sound = model->getSound();
	if (sound.mute) view.soundBtn_setState(1);
	  else view.soundBtn_setState(0);
}

void mainScreenPresenter::deactivate()
{

}

void mainScreenPresenter::updateClock()
{
	datetime_st datetime;

	model->GetClock(&datetime);
	view.updateTimeTA(datetime.Hours, datetime.Minutes, datetime.WeekDay);
	view.updateDateTA(datetime.Date, datetime.Month, datetime.Year);
}

void mainScreenPresenter::updateIcons(uint8_t blink)
{
	uint8_t man, err;
	if (mSystem.err_state & eMAN) man = blink; else man = 0;
	if (mSystem.err_state & eSEN) err = blink; else err = 0;

	view.showIcons(man, err);
}

void mainScreenPresenter::updateSensors(void)
{
	ain_st ai;
	lambda_st ls;
	flowmeter_st fm;

	ai = model->GetAIn(TS1);
	view.updateTS1(ai.t, ai.status);
	ai = model->GetAIn(TS2);
	view.updateTS2(ai.t, ai.status);
	ai = model->GetAIn(TS3);
	view.updateTS3(ai.t, ai.status);
	ai = model->GetAIn(TS4);
	view.updateTS4(ai.t, ai.status);
	ai = model->GetAIn(TS5);
	view.updateTS5(ai.t, ai.status);
	ai = model->GetAIn(TS6);
	view.updateTS6(ai.t, ai.status);
	ai = model->GetAIn(TS7);
	view.updateTS7(ai.t, ai.status);
	ai = model->GetAIn(TS8);
	view.updateTS8(ai.t, ai.status);
	ai = model->GetAIn(TS9);
	view.updateTS9(ai.t, ai.status);

	ls = model->GetLS();
	view.updateLS(ls.value, ls.status);

	fm = model->GetFlowMeter();
	view.updateFlowMeter(fm.flow, fm.sett.view);
}

void mainScreenPresenter::updateOutputs(void)
{

	for (uint8_t n = 0; n < OUT_COUNT; n++)
	{
		view.updateOutput(n, model->GetOutputValue(n), model->GetOutputMode(n));
	}
}


void mainScreenPresenter::updatePAirFlap(void)
{
	uint8_t m;

	if (model->GetFlapMode(PRIM_F) & mMAN) m = 1; else m = 0;
	view.updatePAirFlap(model->GetFlapPos(PRIM_F), m);
}

void mainScreenPresenter::updateSAirFlap(void)
{
	uint8_t m;

	if (model->GetFlapMode(SEC_F) & mMAN) m = 1; else m = 0;
	view.updateSAirFlap(model->GetFlapPos(SEC_F), m);
}

void mainScreenPresenter::updateRegStatus(void)
{
	uint8_t v;

	door_st door = model->getFireplaceDoor();
	burning_st burn = model->getFireplaceBurning();

	if (door.status == DOOR_OPENED)
	{
		view.updateInfoMsg(T_S_DOOR_OPENED);
	}
	else
	{
		view.updateInfoMsg(BPH_MESSAGE[burn.phase]);
	}

	v = model->getAccLevel();
	view.updateAccLevel(v);
}

void mainScreenPresenter::updateEnergy(void)
{
	energy_st eng = model->getEnergy();
	view.updateEnergy(eng.accEng, eng.aPower);
}

void mainScreenPresenter::updateDebug(void)
{
	view.updateDebug();
}

void mainScreenPresenter::doorBtnAction()
{
	door_st door = model->getFireplaceDoor();

	if (door.usedSwitch)
	{
		model->startBurning();
	}
	else
	{
		if (door.status == DOOR_OPENED)
		{
			model->setFireplaceDoorStatus(DOOR_CLOSED);
			model->startBurning();
			view.doorBtn_setLabelDoor(true);
		}
		else
		{
			model->setFireplaceDoorStatus(DOOR_OPENED);
			model->setDoorTimerM(door.timeout * 60);
			view.doorBtn_setLabelDoor(false);
		}
	}
}

void mainScreenPresenter::doorBtnInit()
{
	door_st door = model->getFireplaceDoor();

	if (door.usedSwitch)
	{
		view.doorBtn_setLabelDoor(false);
	}
	else
	{
		if (door.status == DOOR_OPENED)
		{
			view.doorBtn_setLabelDoor(false);
		}
		else
		{
			view.doorBtn_setLabelDoor(true);
		}
	}
}

void mainScreenPresenter::soundBtnAction(uint8_t press)
{
	model->setSoundMute(press);
}

void mainScreenPresenter::setBPrqFlueTemp(uint16_t t)
{
	model->setBPrqFlueTemp(t);
}
