#include <gui/modescreen_screen/modeScreenView.hpp>

modeScreenView::modeScreenView() :
	textAreaClickedCallback(this, &modeScreenView::textAreaClickHandler)
{

}

void modeScreenView::setupScreen()
{
    modeScreenViewBase::setupScreen();

    hDoorSw.setupListItem(T_SH_DOOR_SW);
    list.add(hDoorSw);

    iDoorSw.setupListItem(20, T_S_DOOR_SW);
    list.add(iDoorSw);

    iDoorSw_timeout.setupListItem(20, T_S_DOOR_TIMEOUT, 0, "min");
    iDoorSw_timeout.setValueClickListener(textAreaClickedCallback);
    list.add(iDoorSw_timeout);
}

void modeScreenView::tearDownScreen()
{
    modeScreenViewBase::tearDownScreen();
}

void modeScreenView::initRegSch(uint8_t sch)
{
	mRegSch = sch;
	if (mRegSch < SCH_COUNT)
	{
		i_scheme.setBitmap(touchgfx::Bitmap( TAB_IMG_SCH[mRegSch] ));
		i_scheme.invalidate();

		touchgfx::Unicode::snprintf(ta_schBuffer, TA_SCH_SIZE, "%02u", mRegSch+1);
		ta_sch.setWildcard(ta_schBuffer);
		ta_sch.invalidate();
	}
}

void modeScreenView::initDoor(door_st door)
{
	iDoorSw.setState(door.usedSwitch == 1);
	iDoorSw_timeout.setValue(door.timeout);
}


void modeScreenView::textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e)
{
	if (e.getType() == ClickEvent::PRESSED)
	{
		if (&src == &iDoorSw_timeout.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iDoorSw_timeout, 1, 30);
		}

	}
}

void modeScreenView::okBtn_clicked()
{
	door_st door;

	presenter->setRegSch(mRegSch);

	if (iDoorSw.getState())	door.usedSwitch = true;
	   else door.usedSwitch = false;
	door.timeout = iDoorSw_timeout.getValue();
	presenter->setDoor(door);

	application().gotoserviceScreenScreenNoTransition();
}

void modeScreenView::leftBtn_clicked()
{
	if (mRegSch > SCH_01)
	{
		mRegSch--;
		initRegSch(mRegSch);
	}
}

void modeScreenView::rightBtn_clicked()
{
	if (mRegSch < SCH_COUNT-1)
	{
		mRegSch++;
		initRegSch(mRegSch);
	}
}


