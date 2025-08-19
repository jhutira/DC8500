#include <gui/energyscreen_screen/energyScreenView.hpp>

energyScreenView::energyScreenView() :
textAreaClickedCallback(this, &energyScreenView::onTextAreaClick),
itemSelectedCallback(this, &energyScreenView::onComboChanged)
{

}

void energyScreenView::setupScreen()
{
    energyScreenViewBase::setupScreen();

    scrollCnt.setScrollbarWidth(7);
    list.setHeight(0);

    // FlowMeter
    hFlowmeter.setupListItem(T_SH_FLOWMETER);
    list.add(hFlowmeter);

    iFlowType.setupListItem(20, T_S_TYPE);
    iFlowType.getComboBox().addItem(T_S_NONE_FM);
    iFlowType.getComboBox().addItem(T_S_PULSE_FM);
    iFlowType.getComboBox().addItem(T_S_YFB3_FM);
    iFlowType.getComboBox().setSelectedItem(0);
    iFlowType.getComboBox().setTopLayerContainer(&scrollCnt);
    iFlowType.getComboBox().setItemChangedCallback(itemSelectedCallback);
    list.add(iFlowType);

    iQFactor.setupListItem(20, T_S_Q_FACTOR, 0, " ", eTypeValue::tUInt_1Dec);
    iQFactor.setValueClickListener(textAreaClickedCallback);
    list.add(iQFactor);

    iViewFlow.setupListItem(20, T_S_VIEW);
    list.add(iViewFlow);

}

void energyScreenView::tearDownScreen()
{
    energyScreenViewBase::tearDownScreen();
}


void energyScreenView::initFlowmeterSett(flowmeter_sett_st sett)
{
	iFlowType.getComboBox().setSelectedItem(sett.meter_type);
	iQFactor.setValue(sett.qFactor);
	iViewFlow.setState(sett.view);
}

void energyScreenView::onTextAreaClick(const TextAreaWithOneWildcard& src, const ClickEvent& e)
{
	if (e.getType() == ClickEvent::PRESSED)
	{
		if (&src == &iQFactor.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iQFactor, 1, 500);
		}
	}
}

void energyScreenView::onComboChanged(const ComboBoxCont& src, uint16_t index)
{
	if (&src == &iFlowType.getComboBox())
	{
		//editNumDlgCont.showModal(&editNumDlg, &iQFactor, 1, 500);
		if (index == FM_TYPE_NONE)
		{
			iQFactor.setVisible(false);
			iViewFlow.setVisible(false);
			iViewFlow.setState(false);
		}
		else
		{
			iQFactor.setVisible(true);
			iViewFlow.setVisible(true);
			iViewFlow.setState(true);
		}
		if (index == FM_TYPE_PULSE)
		{
			iQFactor.setValue(FM_PULSE_DEF_QFACTOR);
		}
		if (index == FM_TYPE_YFB3)
		{
			iQFactor.setValue(FM_YFB3_DEF_QFACTOR);
		}
		iQFactor.invalidate();
		iViewFlow.invalidate();
	}
}


void energyScreenView::clearEngBtn_clicked()
{
	questionDlgCont.showModal(&questionDlg, T_MSG_Q_REALYCLEAR_EN);
	questionDlgCont.setOkButtonCallback([this]() {
		qd_okBtn_clicked();
	});
}

void energyScreenView::okBtn_clicked()
{

	flowmeter_sett_st sett;

	sett.meter_type = iFlowType.getComboBox().getSelectedIndex();
	sett.qFactor = iQFactor.getValue();

	if (sett.meter_type == FM_TYPE_YFB3) sett.qFactor = FM_YFB3_DEF_QFACTOR;

	if (iViewFlow.getState()) sett.view = 1; else sett.view = 0;

	presenter->setFlowmeterSett(sett);


	application().gotoserviceScreenScreenNoTransition();
}

void energyScreenView::qd_okBtn_clicked()
{
	presenter->resetEnergyCnt();
}
