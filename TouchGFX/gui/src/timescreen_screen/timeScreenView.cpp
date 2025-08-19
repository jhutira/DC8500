#include <gui/timescreen_screen/timeScreenView.hpp>

timeScreenView::timeScreenView()
{

}

void timeScreenView::setupScreen()
{
    timeScreenViewBase::setupScreen();

}

void timeScreenView::tearDownScreen()
{
    timeScreenViewBase::tearDownScreen();
}

void timeScreenView::initTimeTA(uint8_t h, uint8_t m)
{
	hour = h;
	minute = m;
	updateTimeTA();
}

void timeScreenView::updateTimeTA()
{
	touchgfx::Unicode::snprintf(timeValueBuffer,TIMEVALUE_SIZE,"%d:%.2d", hour, minute);
	timeValue.setWildcard(timeValueBuffer);
	timeValue.invalidate();
}


void timeScreenView::hUpBtn_clicked()
{
	if (hour < 23) hour++;
	updateTimeTA();
}

void timeScreenView::hDownBtn_clicked()
{
	if (hour > 0) hour--;
	updateTimeTA();
}

void timeScreenView::mUpBtn_clicked()
{
	if (minute < 59) minute++;
	updateTimeTA();
}

void timeScreenView::mDownBtn_clicked()
{
	if (minute > 0) minute--;
	updateTimeTA();
}

void timeScreenView::okBtn_clicked()
{
	presenter->setTime(hour, minute, 0);
	application().gotomenuScreenScreenNoTransition();
}

