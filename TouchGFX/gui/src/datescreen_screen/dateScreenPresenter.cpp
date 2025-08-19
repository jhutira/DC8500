#include <gui/datescreen_screen/dateScreenView.hpp>
#include <gui/datescreen_screen/dateScreenPresenter.hpp>

dateScreenPresenter::dateScreenPresenter(dateScreenView& v)
    : view(v)
{

}

void dateScreenPresenter::activate()
{
	datetime_st datetime;

	model->GetClock(&datetime);
	view.initDateTA(datetime.Date, datetime.Month, datetime.Year);
}

void dateScreenPresenter::deactivate()
{

}


void dateScreenPresenter::setDate(uint8_t d, uint8_t m, uint8_t y)
{
	model->SetDate(d, m, y);
}
