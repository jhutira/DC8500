#include <gui/timescreen_screen/timeScreenView.hpp>
#include <gui/timescreen_screen/timeScreenPresenter.hpp>

timeScreenPresenter::timeScreenPresenter(timeScreenView& v)
    : view(v)
{

}

void timeScreenPresenter::activate()
{
	datetime_st datetime;

	model->GetClock(&datetime);
	view.initTimeTA(datetime.Hours, datetime.Minutes);
}

void timeScreenPresenter::deactivate()
{

}

void timeScreenPresenter::setTime(uint8_t h, uint8_t m, uint8_t s)
{
	model->SetTime(h, m, s);
}
