#include <gui/burnprocscreen_screen/burnProcScreenView.hpp>
#include <gui/burnprocscreen_screen/burnProcScreenPresenter.hpp>
#include "reg.h"

burnProcScreenPresenter::burnProcScreenPresenter(burnProcScreenView& v)
    : view(v)
{

}

void burnProcScreenPresenter::activate()
{
	burnPhases_st phb;

	phb = model->getBurnPhases();
	view.initBurnPhasesValues(phb);
}

void burnProcScreenPresenter::deactivate()
{

}


void burnProcScreenPresenter::setBurnPhasesValues(burnPhases_st burnPh)
{
	model->setBurnPhases(burnPh);
}

