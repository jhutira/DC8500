#include <gui/systemscreen_screen/systemScreenView.hpp>
#include <gui/containers/QuestionDlgCont.hpp>
#include <texts/TextKeysAndLanguages.hpp>

systemScreenView::systemScreenView() :
textAreaClickedCallback(this, &systemScreenView::onTextAreaClick),
toggleButtonCallback(this, &systemScreenView::onToggleButttonChanged)
{
	iSaver_en.getToogleButton()->setAction(toggleButtonCallback);
}

void systemScreenView::setupScreen()
{
    systemScreenViewBase::setupScreen();

    scrollCnt.setScrollbarWidth(7);
    list.setHeight(0);

    hDisplay.setupListItem(T_SH_DISPLAY);
    list.add(hDisplay);

    iDisp_backlight.setupListItem(20, T_S_BACKLIGHT, 0, "%");
    iDisp_backlight.setValueClickListener(textAreaClickedCallback);
    list.add(iDisp_backlight);

    iSaver_en.setupListItem(20, T_S_SCREEN_SAVER);
    list.add(iSaver_en);

    iSaver_time.setupListItem(40, T_S_SAVER_TIME, 0, "s");
    iSaver_time.setValueClickListener(textAreaClickedCallback);
    list.add(iSaver_time);

    iSaver_backlight.setupListItem(40, T_S_SAVER_BACKLIGHT, 0, "%");
    iSaver_backlight.setValueClickListener(textAreaClickedCallback);
    list.add(iSaver_backlight);

    hSound.setupListItem(T_SH_SOUND);
    list.add(hSound);

    iSound_QI_Start.setupListItem(20, T_S_SOUND_GUIET_START, 0, 0 );
    iSound_QI_Start.setValueClickListener(textAreaClickedCallback);
    list.add(iSound_QI_Start);

    iSound_QI_End.setupListItem(20, T_S_SOUND_GUIET_END, 0, 0 );
    iSound_QI_End.setValueClickListener(textAreaClickedCallback);
    list.add(iSound_QI_End);

    iSound_Alarm.setupListItem(20, T_S_SOUND_ALARM);
    list.add(iSound_Alarm);
    iSound_Warn.setupListItem(20, T_S_SOUND_WARN);
    list.add(iSound_Warn);
    iSound_Click.setupListItem(20, T_S_SOUND_CLICK);
    list.add(iSound_Click);

}

void systemScreenView::tearDownScreen()
{
    systemScreenViewBase::tearDownScreen();
}


void systemScreenView::initDispSett(disp_sett_st sett)
{
	iDisp_backlight.setValue(sett.backlight);

	iSaver_backlight.setValue(sett.saver_backlight);
	iSaver_time.setValue(sett.saver_time);
	iSaver_en.setState(sett.saver_en);
}

void systemScreenView::initSoundSett(sound_sett_st sett)
{
	iSound_Alarm.setState(sett.announ_msg & amALARM);
	iSound_Warn.setState(sett.announ_msg & amWARN);
	iSound_Click.setState(sett.announ_msg & amTOUCH);

	iSound_QI_Start.setValue(sett.mute_time_on.h, sett.mute_time_on.m);
	iSound_QI_End.setValue(sett.mute_time_off.h, sett.mute_time_off.m);
}

void systemScreenView::onTextAreaClick(const TextAreaWithOneWildcard& src, const ClickEvent& e)
{
	if (e.getType() == ClickEvent::PRESSED)
	{
		if (&src == &iSound_QI_Start.getValueTextArea())
		{
			editTimeDlgCont.showModal(&editTimeDlg, &iSound_QI_Start);
		}
		if (&src == &iSound_QI_End.getValueTextArea())
		{
			editTimeDlgCont.showModal(&editTimeDlg, &iSound_QI_End);
		}
		if (&src == &iDisp_backlight.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iDisp_backlight, 10, 100);
		}
		if (&src == &iSaver_backlight.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iSaver_backlight, 0, 100);
		}
		if (&src == &iSaver_time.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iSaver_time, 10, 240);
		}
	}
}

void systemScreenView::onToggleButttonChanged(const touchgfx::AbstractButton& src)
{
//	if (&src == iSaver_en.getToogleButton())
//	{
//		bool currentState = iSaver_en.getToogleButton()->getState();
//
//		if (currentState)
//		{
//			iSaver_time.setVisibleItem(true);
//			iSaver_backlight.setVisibleItem(true);
//		}
//		else
//		{
//			iSaver_time.setVisibleItem(false);
//			iSaver_backlight.setVisibleItem(false);
//		}
//		// Layout workaround (TouchGFX 4.25 nemá forceResize())
////		list.setHeight(list.getHeight() + 1);
////		list.setHeight(list.getHeight() - 1);
//		//list.remove(iSound_Alarm);
//
//		scrollCnt.invalidate();  // redraw UI
////		list.setHeight(list.getHeight() + 1); // donúti preusporiadanie
////		list.setHeight(list.getHeight() - 1);
////		scrollCnt.invalidate();
////		//list.invalidate();
//	}

}


void systemScreenView::defaultBtn_clicked()
{
	questionDlgCont.showModal(&questionDlg, T_MSG_Q_REALYDEFAULT);
	questionDlgCont.setOkButtonCallback([this]() {
		qd_okBtn_clicked();
	});
}

void systemScreenView::okBtn_clicked()
{
	sound_sett_st sett;
	disp_sett_st disp_sett;

	/* Display sett */
	disp_sett.backlight = iDisp_backlight.getValue();
	disp_sett.saver_backlight = iSaver_backlight.getValue();
	disp_sett.saver_time = iSaver_time.getValue();

	if (iSaver_en.getState()) disp_sett.saver_en = 1; else disp_sett.saver_en = 0;

	presenter->setDispSett(disp_sett);

	/* Sound sett */
	sett.announ_msg = 0;
	if (iSound_Alarm.getState()) sett.announ_msg |= amALARM;
	if (iSound_Warn.getState()) sett.announ_msg |= amWARN;
	if (iSound_Click.getState()) sett.announ_msg |= amTOUCH;

	sett.mute_time_on.h = iSound_QI_Start.getHours();
	sett.mute_time_on.m = iSound_QI_Start.getMinutes();

	sett.mute_time_off.h = iSound_QI_End.getHours();
	sett.mute_time_off.m = iSound_QI_End.getMinutes();

	presenter->setSoundSett(sett);




	application().gotoserviceScreenScreenNoTransition();
}

void systemScreenView::qd_okBtn_clicked()
{
	presenter->setDefaultSettings();
}

