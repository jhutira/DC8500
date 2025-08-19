#include <gui/energyscreen_screen/energyScreenView.hpp>
#include <gui/energyscreen_screen/energyScreenPresenter.hpp>

energyScreenPresenter::energyScreenPresenter(energyScreenView& v)
    : view(v)
{

}

void energyScreenPresenter::activate()
{
	flowmeter_sett_st sett = model->getFlowmeterSett();
	view.initFlowmeterSett(sett);
}

void energyScreenPresenter::deactivate()
{

}

void energyScreenPresenter::setFlowmeterSett(flowmeter_sett_st sett)
{
	model->setFlowmeterSett(sett);
}

void energyScreenPresenter::resetEnergyCnt()
{
	model->resetEnergyCnt();
}

