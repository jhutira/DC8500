#include <gui/exchanscreen_screen/exchanScreenView.hpp>

#include <gui/common/DefnGui.hpp>

exchanScreenView::exchanScreenView() :
	textAreaClickedCallback(this, &exchanScreenView::textAreaClickHandler)
{

}

void exchanScreenView::setupScreen()
{
    exchanScreenViewBase::setupScreen();

    scrollCnt.setScrollbarWidth(7);
	list.setHeight(0);

	// Periodic stirring of water
	hPmWater.setupListItem(T_SH_PM_WATER);
	list.add(hPmWater);

	iPSWper.setupListItem(20, T_S_PERIOD, 0, "min");
	iPSWper.setValueClickListener(textAreaClickedCallback);
	list.add(iPSWper);

	iPSWtime.setupListItem(20, T_S_RUN_TIME, 0, "s");
	iPSWtime.setValueClickListener(textAreaClickedCallback);
	list.add(iPSWtime);

	iPSWphStBurn.setupListItem(20, T_S_PH_START_BURNING);
	list.add(iPSWphStBurn);
	iPSWphBurn.setupListItem(20, T_S_PH_BURNING);
	list.add(iPSWphBurn);
	iPSWphBurnOut.setupListItem(20, T_S_PH_BURNING_OUT);
	list.add(iPSWphBurnOut);

	// Minimal temperature
	hMinTemp.setupListItem(T_SH_MIN_TEMP);
	list.add(hMinTemp);

	iMTtemp.setupListItem(20, T_S_TEMP, 0, DegCel);
	iMTtemp.setValueClickListener(textAreaClickedCallback);
	list.add(iMTtemp);

	iMThyst.setupListItem(20, T_S_HYST, 0, DegCel);
	iMThyst.setValueClickListener(textAreaClickedCallback);
	list.add(iMThyst);

	// Critical temperature
	hCritTemp.setupListItem(T_SH_CRITIC_TEMP);
	list.add(hCritTemp);

	iCTtemp.setupListItem(20, T_S_TEMP, 0, DegCel);
	iCTtemp.setValueClickListener(textAreaClickedCallback);
	list.add(iCTtemp);

	iCThyst.setupListItem(20, T_S_HYST, 0, DegCel);
	iCThyst.setValueClickListener(textAreaClickedCallback);
	list.add(iCThyst);

	iCTflap.setupListItem(20, T_S_PRIM_FLAP, 0, " %");
	iCTflap.setValueClickListener(textAreaClickedCallback);
	list.add(iCTflap);
}

void exchanScreenView::tearDownScreen()
{
    exchanScreenViewBase::tearDownScreen();
}

void exchanScreenView::initExchangerValues(waterExch_st ex)
{
	iPSWper.setValue(ex.perStirr.period);
	iPSWtime.setValue(ex.perStirr.runTime);
	iPSWphStBurn.setState((ex.perStirr.phaseEn & 0x01) != 0);
	iPSWphBurn.setState((ex.perStirr.phaseEn & 0x02) != 0);
	iPSWphBurnOut. setState((ex.perStirr.phaseEn & 0x04) != 0);

	iMTtemp.setValue(ex.minTemp.temp / 10);
	iMThyst.setValue(ex.minTemp.hyst / 10);

	iCTtemp.setValue(ex.critTemp.temp / 10);
	iCThyst.setValue(ex.critTemp.hyst / 10);
	iCTflap.setValue(ex.critTemp.flap);
}


void exchanScreenView::textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e)
{
	if (e.getType() == ClickEvent::PRESSED)
	{
		if (&src == &iPSWper.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iPSWper, 1, 99);
		}
		if (&src == &iPSWtime.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iPSWtime, 3, 200);
		}
		if (&src == &iMTtemp.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iMTtemp, 0, 99);
		}
		if (&src == &iMThyst.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iMThyst, 0, 25);
		}

		if (&src == &iCTtemp.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iCTtemp, 0, 99);
		}
		if (&src == &iCThyst.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iCThyst, 0, 25);
		}
		if (&src == &iCTflap.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iCTflap, 0, 100);
		}
	}
}

void exchanScreenView::okBtn_clicked()
{
    waterExch_st ex;
	uint8_t ph = 0;

	if (iPSWphStBurn.getState()) ph |= 0x01;
	if (iPSWphBurn.getState()) ph |= 0x02;
	if (iPSWphBurnOut.getState()) ph |= 0x04;

	ex.perStirr.period = iPSWper.getValue();
	ex.perStirr.runTime = iPSWtime.getValue();
	ex.perStirr.phaseEn = ph;
	ex.minTemp.temp = 10 * iMTtemp.getValue();
	ex.minTemp.hyst = 10 * iMThyst.getValue();
	ex.critTemp.temp = 10 * iCTtemp.getValue();
	ex.critTemp.hyst = 10 * iCThyst.getValue();
	ex.critTemp.flap = iCTflap.getValue();

	presenter->setExchangerValues(ex);
	application().gotoserviceScreenScreenNoTransition();
}
