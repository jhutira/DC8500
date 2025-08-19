#include <gui/exchanscreen_screen/exchanScreenView.hpp>
#include <gui/exchanscreen_screen/exchanScreenPresenter.hpp>

exchanScreenPresenter::exchanScreenPresenter(exchanScreenView& v)
    : view(v)
{

}

void exchanScreenPresenter::activate()
{
	waterExch_st ex;

	ex = model->getWaterExch();
	view.initExchangerValues(ex);
}

void exchanScreenPresenter::deactivate()
{

}


void exchanScreenPresenter::setExchangerValues(waterExch_st ex)
{
	model->setWaterExch(ex);
}
