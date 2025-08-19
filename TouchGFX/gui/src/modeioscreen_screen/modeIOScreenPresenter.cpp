#include <gui/modeioscreen_screen/modeIOScreenView.hpp>
#include <gui/modeioscreen_screen/modeIOScreenPresenter.hpp>

modeIOScreenPresenter::modeIOScreenPresenter(modeIOScreenView& v)
    : view(v)
{

}

void modeIOScreenPresenter::activate()
{
	uint8_t val;

	for (uint8_t i = 0; i < 5; i++)
	{
		if (model->GetOutputMode(i) & oINV) val = 1; else val = 0;
		view.initOutputComboBox(i, val);
	}

	for (uint8_t i = 0; i < 2; i++)
	{
		if (model->GetDInMode(i) & iINV) val = 1; else val = 0;
		view.initDInComboBox(i, val);
	}

	contPump_st cp = model->GetCModeP1();
	view.initCModeP1Box(cp.mode, cp.minVal, cp.maxVal);
}

void modeIOScreenPresenter::deactivate()
{

}

void modeIOScreenPresenter::saveOutputComboBox(uint8_t n, uint8_t inv)
{
	model->SetOutputInvMode(n, inv);
}

void modeIOScreenPresenter::saveDInComboBox(uint8_t n, uint8_t inv)
{
	uint8_t m = model->GetDInMode(n);

	if (inv) m |= iINV; else m &= ~(iINV);
	model->SetDInMode(n, m);
}

void modeIOScreenPresenter::saveCModeP1Box(uint8_t index, uint8_t minV, uint8_t maxV)
{
	contPump_st cm;
	cm.mode = index;
	cm.minVal = minV;
	cm.maxVal = maxV;
	model->SetCModeP1(cm);
}


