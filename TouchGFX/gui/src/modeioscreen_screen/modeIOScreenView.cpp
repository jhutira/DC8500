#include <gui/modeioscreen_screen/modeIOScreenView.hpp>

modeIOScreenView::modeIOScreenView() :
	textAreaClickedCallback(this, &modeIOScreenView::textAreaClickHandler)
{

}

void modeIOScreenView::setupScreen()
{
    modeIOScreenViewBase::setupScreen();

    scrollCnt.setScrollbarWidth(7);
	list.setHeight(0);

	// Pump P1
	hPumpP1.setupListItem(T_SH_PUMP_P1);
	list.add(hPumpP1);

	iCModeP1.setupListItem(20, T_S_CONTROL_SIGNAL);
	iCModeP1.getComboBox().addItem(T_S_CS_0_10V);
	iCModeP1.getComboBox().addItem(T_S_CS_PWM);
	iCModeP1.getComboBox().addItem(T_S_CS_IPWM);
	iCModeP1.getComboBox().setSelectedItem(0);
	iCModeP1.getComboBox().setTopLayerContainer(&scrollCnt);
	list.add(iCModeP1);

	iMinP1.setupListItem(20, T_S_MIN_SPEED, 0, " %");
	iMinP1.setValueClickListener(textAreaClickedCallback);
	list.add(iMinP1);
	iMaxP1.setupListItem(20, T_S_MAX_SPEED, 0, " %");
	iMaxP1.setValueClickListener(textAreaClickedCallback);
	list.add(iMaxP1);

	// Outputs
	hOutputs.setupListItem(T_SH_MODE_OUT);
	list.add(hOutputs);

	// P1
	iOut[0].setupListItem(20, T_S_OUT_P1);
	iOut[0].getComboBox().addItem(T_S_NORMAL);
	iOut[0].getComboBox().addItem(T_S_INVERT);
	iOut[0].getComboBox().setSelectedItem(0);
	iOut[0].getComboBox().setTopLayerContainer(&scrollCnt);
	list.add(iOut[0]);
	// P2
	iOut[1].setupListItem(20, T_S_OUT_P2);
	iOut[1].getComboBox().addItem(T_S_NORMAL);
	iOut[1].getComboBox().addItem(T_S_INVERT);
	iOut[1].getComboBox().setSelectedItem(0);
	iOut[1].getComboBox().setTopLayerContainer(&scrollCnt);
	list.add(iOut[1]);
	// Y1
	iOut[2].setupListItem(20, T_S_OUT_Y1);
	iOut[2].getComboBox().addItem(T_S_NORMAL);
	iOut[2].getComboBox().addItem(T_S_INVERT);
	iOut[2].getComboBox().setSelectedItem(0);
	iOut[2].getComboBox().setTopLayerContainer(&scrollCnt);
	list.add(iOut[2]);
	// Y2
	iOut[3].setupListItem(20, T_S_OUT_Y2);
	iOut[3].getComboBox().addItem(T_S_NORMAL);
	iOut[3].getComboBox().addItem(T_S_INVERT);
	iOut[3].getComboBox().setSelectedItem(0);
	iOut[3].getComboBox().setTopLayerContainer(&scrollCnt);
	list.add(iOut[3]);
	// Y3
	iOut[4].setupListItem(20, T_S_OUT_Y3);
	iOut[4].getComboBox().addItem(T_S_NORMAL);
	iOut[4].getComboBox().addItem(T_S_INVERT);
	iOut[4].getComboBox().setSelectedItem(0);
	iOut[4].getComboBox().setTopLayerContainer(&scrollCnt);
	list.add(iOut[4]);

	// Digital Inputs
	hDin.setupListItem(T_SH_MODE_DI);
	list.add(hDin);
	// DI1
	iDIn[0].setupListItem(20, T_S_IN_DI1);
	iDIn[0].getComboBox().addItem(T_S_NORMAL);
	iDIn[0].getComboBox().addItem(T_S_INVERT);
	iDIn[0].getComboBox().setSelectedItem(0);
	iDIn[0].getComboBox().setTopLayerContainer(&scrollCnt);
	list.add(iDIn[0]);
	// DI1
	iDIn[1].setupListItem(20, T_S_IN_DI2);
	iDIn[1].getComboBox().addItem(T_S_NORMAL);
	iDIn[1].getComboBox().addItem(T_S_INVERT);
	iDIn[1].getComboBox().setSelectedItem(0);
	iDIn[1].getComboBox().setTopLayerContainer(&scrollCnt);
	list.add(iDIn[1]);
}

void modeIOScreenView::tearDownScreen()
{
    modeIOScreenViewBase::tearDownScreen();
}

void modeIOScreenView::textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e)
{
	if (e.getType() == ClickEvent::PRESSED)
	{
		if (&src == &iMinP1.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iMinP1, 0, 100);
		}

		if (&src == &iMaxP1.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iMaxP1, 0, 100);
		}
	}
}

void modeIOScreenView::initOutputComboBox(uint8_t n, uint8_t index)
{
	iOut[n].getComboBox().setSelectedItem(index);
}

void modeIOScreenView::initDInComboBox(uint8_t n, uint8_t index)
{
	iDIn[n].getComboBox().setSelectedItem(index);
}

void modeIOScreenView::initCModeP1Box(uint8_t index, uint8_t minV, uint8_t maxV)
{
	iCModeP1.getComboBox().setSelectedItem(index);
	iMinP1.setValue(minV);
	iMaxP1.setValue(maxV);
}

void modeIOScreenView::okBtn_clicked()
{
	for (uint8_t i = 0; i < 5; i++)
	{
	    presenter->saveOutputComboBox(i, iOut[i].getComboBox().getSelectedIndex());
	}

	for (uint8_t i = 0; i < 2; i++)
	{
	    presenter->saveDInComboBox(i, iDIn[i].getComboBox().getSelectedIndex());
	}

	presenter->saveCModeP1Box(iCModeP1.getComboBox().getSelectedIndex(), iMinP1.getValue(), iMaxP1.getValue());

	application().gotoserviceScreenScreenNoTransition();
}
