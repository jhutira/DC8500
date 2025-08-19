#include <gui/datescreen_screen/dateScreenView.hpp>

dateScreenView::dateScreenView()
{
	updateDateTA();
}

void dateScreenView::setupScreen()
{
    dateScreenViewBase::setupScreen();

}

void dateScreenView::tearDownScreen()
{
    dateScreenViewBase::tearDownScreen();
}

void dateScreenView::initDateTA(uint8_t d, uint8_t m, uint8_t y)
{
	date = d;
	month = m;
	year = y;
	updateDateTA();
}

void dateScreenView::updateDateTA()
{
	uint8_t days = daysInMonth(year, month);

	if (date > days) date = days;

	touchgfx::Unicode::snprintf(dateValueBuffer,DATEVALUE_SIZE,"%d.%d.%d", date, month, 2000 + year);
	dateValue.setWildcard(dateValueBuffer);
	dateValue.invalidateContent();
}


void dateScreenView::dUpBtn_clicked()
{
	uint8_t days = daysInMonth(year, month);

	if (date < days) date++;

	updateDateTA();
}

void dateScreenView::dDownBtn_clicked()
{
	if (date > 1) date--;

	updateDateTA();
}

void dateScreenView::mUpBtn_clicked()
{
	if (month < 12) month++;

	updateDateTA();
}

void dateScreenView::mDownBtn_clicked()
{
	if (month > 1) month--;

	updateDateTA();
}

void dateScreenView::yUpBtn_clicked()
{
	if (year < 99) year++;

	updateDateTA();
}

void dateScreenView::yDownBtn_()
{
	if (year > 0) year--;

	updateDateTA();
}

void dateScreenView::okBtn_clicked()
{
	presenter->setDate(date, month, year);

	application().gotomenuScreenScreenNoTransition();
}
