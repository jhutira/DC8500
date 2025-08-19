#include <gui/passwordscreen_screen/passwordScreenView.hpp>
#include <gui/common/DefnGui.hpp>
#include "string.h"
#include "system.h"

passwordScreenView::passwordScreenView()
{

}

void passwordScreenView::setupScreen()
{
    passwordScreenViewBase::setupScreen();

    mSystem.exservice_mode = 0;
    numPadCont.setEnterCallback([this]() { this->enterBtnClicked(); });
}

void passwordScreenView::tearDownScreen()
{
    passwordScreenViewBase::tearDownScreen();
}

void passwordScreenView::enterBtnClicked()
{
	if (Unicode::strncmp(numPadCont.keyboard.getBuffer(), SERVICE_PASSWORD, 4) == 0)
	{
		mSystem.service_mode = 1;
		application().gotoserviceScreenScreenNoTransition();
	}

	if (Unicode::strncmp(numPadCont.keyboard.getBuffer(), EXSERVICE_PASSWORD, 4) == 0)
	{
		mSystem.exservice_mode = 1;
		application().gotoexserviceScreenScreenNoTransition();
	}
}
