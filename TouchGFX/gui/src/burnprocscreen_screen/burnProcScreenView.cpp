#include <gui/burnprocscreen_screen/burnProcScreenView.hpp>

#include <gui/common/DefnGui.hpp>

burnProcScreenView::burnProcScreenView() :
	textAreaClickedCallback(this, &burnProcScreenView::textAreaClickHandler)
{

}

void burnProcScreenView::setupScreen()
{
    burnProcScreenViewBase::setupScreen();

    scrollCnt.setScrollbarWidth(7);
    list.setHeight(0);

	// Bruning Start
    hPhStartBurning.setupListItem(T_SH_START_BURNING);
	list.add(hPhStartBurning);

	iSB_Timeout.setupListItem(20, T_S_TIMEOUT, 0, "min");
	iSB_Timeout.setValueClickListener(textAreaClickedCallback);
	list.add(iSB_Timeout);

	iSB_MinTempToBurn.setupListItem(20, T_S_MIN_TEMP_TO_BURN, 0, DegCel);
	iSB_MinTempToBurn.setValueClickListener(textAreaClickedCallback);
	list.add(iSB_MinTempToBurn);

	// Bruning
	hPhBurning.setupListItem(T_SH_BURNING);
	list.add(hPhBurning);

	iBN_O2.setupListItem(20, T_S_VALUE_O2, 0, "%", eTypeValue::tUInt_1Dec);
	iBN_O2.setValueClickListener(textAreaClickedCallback);
	list.add(iBN_O2);

	iBN_TempToBurnOut.setupListItem(20, T_S_TEMP_TO_BURNOUT, 0, DegCel);
	iBN_TempToBurnOut.setValueClickListener(textAreaClickedCallback);
	list.add(iBN_TempToBurnOut);

	iBN_TimeToBurnOut.setupListItem(20, T_S_TIME_TO_BURNOUT, 0, "min");
	iBN_TimeToBurnOut.setValueClickListener(textAreaClickedCallback);
	list.add(iBN_TimeToBurnOut);


	// Bruning Out
	hPhBurningOut.setupListItem(T_SH_BURNING_OUT);
	list.add(hPhBurningOut);

	iBO_TempToGlowEmb.setupListItem(20, T_S_TEMP_TO_GLOWEMB, 0, DegCel);
	iBO_TempToGlowEmb.setValueClickListener(textAreaClickedCallback);
	list.add(iBO_TempToGlowEmb);

	iBO_TimeToGlowEmb.setupListItem(20, T_S_TIME_TO_GLOWEMB, 0, "min");
	iBO_TimeToGlowEmb.setValueClickListener(textAreaClickedCallback);
	list.add(iBO_TimeToGlowEmb);

	iBO_PFlap.setupListItem(20, T_S_PRIM_FLAP, 0, "%");
	iBO_PFlap.setValueClickListener(textAreaClickedCallback);
	list.add(iBO_PFlap);


	// Glowing Embers
	hPhGlowingEmbers.setupListItem(T_SH_GLOWING_EMBERS);
	list.add(hPhGlowingEmbers);

	iGE_Timeout.setupListItem(20, T_S_TIMEOUT, 0, "h");
	iGE_Timeout.setValueClickListener(textAreaClickedCallback);
	list.add(iGE_Timeout);

	iGE_PFlap.setupListItem(20, T_S_PRIM_FLAP, 0, "%");
	iGE_PFlap.setValueClickListener(textAreaClickedCallback);
	list.add(iGE_PFlap);

	iGE_SFlap.setupListItem(20, T_S_SEC_FLAP, 0, "%");
	iGE_SFlap.setValueClickListener(textAreaClickedCallback);
	list.add(iGE_SFlap);

	// Ventilation
	hPhVetilation.setupListItem(T_SH_VENTILATION);
	list.add(hPhVetilation);

	iVN_Time.setupListItem(20, T_S_TIME, 0, "min");
	iVN_Time.setValueClickListener(textAreaClickedCallback);
	list.add(iVN_Time);

	iVN_PFlap.setupListItem(20, T_S_PRIM_FLAP, 0, "%");
	iVN_PFlap.setValueClickListener(textAreaClickedCallback);
	list.add(iVN_PFlap);

	iVN_SFlap.setupListItem(20, T_S_SEC_FLAP, 0, "%");
	iVN_SFlap.setValueClickListener(textAreaClickedCallback);
	list.add(iVN_SFlap);
}

void burnProcScreenView::tearDownScreen()
{
    burnProcScreenViewBase::tearDownScreen();
}

void burnProcScreenView::initBurnPhasesValues(burnPhases_st burnPh)
{
	iSB_Timeout.setValue(burnPh.phStartBurning.timeout);
	iSB_MinTempToBurn.setValue(burnPh.phStartBurning.minTempForBurn / 10);

	iBN_O2.setValue(burnPh.phBurning.o2);
	iBN_TempToBurnOut.setValue(burnPh.phBurning.tempForBurnOut / 10);
	iBN_TimeToBurnOut.setValue(burnPh.phBurning.timeoutForBurnOut);

	iBO_TempToGlowEmb.setValue(burnPh.phBurningOut.tempForGlowEmb / 10);
	iBO_TimeToGlowEmb.setValue(burnPh.phBurningOut.timeoutForGlowEmb);
	iBO_PFlap.setValue(burnPh.phBurningOut.pflap);

	iGE_Timeout.setValue(burnPh.phGlowingEmbers.timeout);
	iGE_PFlap.setValue(burnPh.phGlowingEmbers.pflap);
	iGE_SFlap.setValue(burnPh.phGlowingEmbers.sflap);

	iVN_Time.setValue(burnPh.phVentilation.timeout);
	iVN_PFlap.setValue(burnPh.phVentilation.pflap);
	iVN_SFlap.setValue(burnPh.phVentilation.sflap);
}


void burnProcScreenView::textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e)
{
	if (e.getType() == ClickEvent::PRESSED)
	{
		if (&src == &iSB_Timeout.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iSB_Timeout, 1, 90);
		}
		if (&src == &iSB_MinTempToBurn.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iSB_MinTempToBurn, 30, 400);
		}

		if (&src == &iBN_O2.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iBN_O2, 10, 150);
		}
		if (&src == &iBN_TempToBurnOut.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iBN_TempToBurnOut, 30, 400);
		}
		if (&src == &iBN_TimeToBurnOut.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iBN_TimeToBurnOut, 1, 90);
		}

		if (&src == &iBO_TempToGlowEmb.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iBO_TempToGlowEmb, 30, 400);
		}
		if (&src == &iBO_TimeToGlowEmb.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iBO_TimeToGlowEmb, 1, 90);
		}
		if (&src == &iBO_PFlap.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iBO_PFlap, 0, 100);
		}

		if (&src == &iGE_Timeout.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iGE_Timeout, 1, 12);
		}
		if (&src == &iGE_PFlap.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iGE_PFlap, 0, 100);
		}
		if (&src == &iGE_SFlap.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iGE_SFlap, 0, 100);
		}

		if (&src == &iVN_Time.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iVN_Time, 1, 90);
		}
		if (&src == &iVN_PFlap.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iVN_PFlap, 0, 100);
		}
		if (&src == &iVN_SFlap.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iVN_SFlap, 0, 100);
		}
	}
}

void burnProcScreenView::okBtn_clicked()
{
	burnPhases_st burnPh;

	burnPh.phStartBurning.timeout = iSB_Timeout.getValue();
	burnPh.phStartBurning.minTempForBurn = 10 * iSB_MinTempToBurn.getValue();

	burnPh.phBurning.o2 = iBN_O2.getValue();
	burnPh.phBurning.tempForBurnOut = 10 * iBN_TempToBurnOut.getValue();
	burnPh.phBurning.timeoutForBurnOut = iBN_TimeToBurnOut.getValue();

	burnPh.phBurningOut.tempForGlowEmb = 10 * iBO_TempToGlowEmb.getValue();
	burnPh.phBurningOut.timeoutForGlowEmb = iBO_TimeToGlowEmb.getValue();
	burnPh.phBurningOut.pflap = iBO_PFlap.getValue();

	burnPh.phGlowingEmbers.timeout = iGE_Timeout.getValue();
	burnPh.phGlowingEmbers.pflap = iGE_PFlap.getValue();
	burnPh.phGlowingEmbers.sflap = iGE_PFlap.getValue();

	burnPh.phVentilation.timeout = iVN_Time.getValue();
	burnPh.phVentilation.pflap = iVN_PFlap.getValue();
	burnPh.phVentilation.sflap = iVN_SFlap.getValue();

	presenter->setBurnPhasesValues(burnPh);

	application().gotoserviceScreenScreenNoTransition();
}
