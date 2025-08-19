#include <gui/systemscreen_screen/systemScreenView.hpp>
#include <gui/systemscreen_screen/systemScreenPresenter.hpp>

systemScreenPresenter::systemScreenPresenter(systemScreenView& v)
    : view(v)
{

}

void systemScreenPresenter::activate()
{
	disp_sett_st disp_sett = model->getDisplaySett();
	view.initDispSett(disp_sett);

	sound_st sett = model->getSound();
	view.initSoundSett(sett.sett);
}

void systemScreenPresenter::deactivate()
{

}

void systemScreenPresenter::setDispSett(disp_sett_st sett)
{
	model->setDispSett(sett);
}

void systemScreenPresenter::setSoundSett(sound_sett_st sett)
{
	model->setSoundSett(sett);
}

void systemScreenPresenter::setDefaultSettings()
{
	model->setDefaultSettings();
	activate();	// reload new data
}

