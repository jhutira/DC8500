#include <gui/menuscreen_screen/menuScreenView.hpp>
#include "system.h"

menuScreenView::menuScreenView()
{

}

void menuScreenView::setupScreen()
{
    menuScreenViewBase::setupScreen();
}

void menuScreenView::tearDownScreen()
{
    menuScreenViewBase::tearDownScreen();
}

void menuScreenView::enableButtons(uint8_t enDistribBtn, uint8_t enAccumBtn, uint8_t enBoilerBtn)
{
	distribBtn.setVisible(enDistribBtn);
	accumBtn.setVisible(enAccumBtn);
	boilerBtn.setVisible(enBoilerBtn);
}

void menuScreenView::serviceBtnClicked()
{
	if (mSystem.service_mode)
	{
		application().gotoserviceScreenScreenNoTransition();
	}
	else
	{
		application().gotopasswordScreenScreenNoTransition();
	}
}
