#include <gui/distribscreen_screen/distribScreenView.hpp>

distribScreenView::distribScreenView()
{

}

void distribScreenView::setupScreen()
{
    distribScreenViewBase::setupScreen();
}

void distribScreenView::tearDownScreen()
{
    distribScreenViewBase::tearDownScreen();
}

void distribScreenView::initDistribBtn(uint8_t ds)
{
    if (ds == 2) whBtn.setSelected(true);
    else
    if (ds == 1) hBtn.setSelected(true);
    else
    if (ds == 0) wBtn.setSelected(true);
}

void distribScreenView::okBtnClicked()
{
	uint8_t ds = 0;

	if (whBtn.getSelected()) ds = 2;
	else
	if (hBtn.getSelected()) ds = 1;
	else
	if (wBtn.getSelected()) ds = 0;

	presenter->setDistrib(ds);
	application().gotomenuScreenScreenNoTransition();
}
