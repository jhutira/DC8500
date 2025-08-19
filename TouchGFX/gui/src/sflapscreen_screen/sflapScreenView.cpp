#include <gui/sflapscreen_screen/sflapScreenView.hpp>

#include "gui/common/DefnGui.hpp"


sflapScreenView::sflapScreenView() :
	textAreaClickedCallback(this, &sflapScreenView::textAreaClickHandler)
{

}

void sflapScreenView::setupScreen()
{
    sflapScreenViewBase::setupScreen();

    scrollCnt.setScrollbarWidth(7);
	list.setHeight(0);

	// Flap
	hFlap.setupListItem(T_SH_FLAP);
	list.add(hFlap);

	iFlap_rmin.setupListItem(20, T_S_RANGE_MIN, 0, "%");
	iFlap_rmin.setValueClickListener(textAreaClickedCallback);
	list.add(iFlap_rmin);

	iFlap_rmax.setupListItem(20, T_S_RANGE_MAX, 0, "%");
	iFlap_rmax.setValueClickListener(textAreaClickedCallback);
	list.add(iFlap_rmax);

	// PID
	hPID.setupListItem(T_SH_PID);
	list.add(hPID);

	iPID_sampPeriod.setupListItem(20, T_S_PID_SAMP_PERIOD, 0, "s", eTypeValue::tUInt_1Dec);
	iPID_sampPeriod.setValueClickListener(textAreaClickedCallback);
	list.add(iPID_sampPeriod);

	iPID_CP.setupListItem(20, T_S_PID_CP, 10, " ", eTypeValue::tUInt_1Dec);
	iPID_CP.setValueClickListener(textAreaClickedCallback);
	list.add(iPID_CP);

	iPID_CI.setupListItem(20, T_S_PID_CI, 0, " ", eTypeValue::tUInt_1Dec);
	iPID_CI.setValueClickListener(textAreaClickedCallback);
	list.add(iPID_CI);

	iPID_CD.setupListItem(20, T_S_PID_CD, 0, " ", eTypeValue::tUInt_1Dec);
	iPID_CD.setValueClickListener(textAreaClickedCallback);
	list.add(iPID_CD);
}

void sflapScreenView::tearDownScreen()
{
    sflapScreenViewBase::tearDownScreen();
}

void sflapScreenView::initPIDValues(pidConfig_st pid_conf)
{
	iFlap_rmin.setValue((uint32_t) (pid_conf.outputMin));
	iFlap_rmax.setValue((uint32_t) (pid_conf.outputMax));

	iPID_CP.setValue((uint32_t) (pid_conf.kp * FI_SCALE));
	iPID_CI.setValue((uint32_t) (pid_conf.ki * FI_SCALE));
	iPID_CD.setValue((uint32_t) (pid_conf.kd * FI_SCALE));
	iPID_sampPeriod.setValue((uint32_t) (pid_conf.dt * FI_SCALE));
}


void sflapScreenView::textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e)
{
	if (e.getType() == ClickEvent::PRESSED)
	{
		if (&src == &iFlap_rmin.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iFlap_rmin, 1, 100);
		}
		if (&src == &iFlap_rmax.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iFlap_rmax, 1, 100);
		}

		if (&src == &iPID_sampPeriod.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iPID_sampPeriod, 1, 1000);
		}
		if (&src == &iPID_CP.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iPID_CP, 0, 100);
		}
		if (&src == &iPID_CI.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iPID_CI, 0, 100);
		}
		if (&src == &iPID_CD.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iPID_CD, 0, 100);
		}
	}
}

void sflapScreenView::okBtn_clicked()
{
	pidConfig_st pid_conf;

	pid_conf.outputMin = (float) iFlap_rmin.getValue();
	pid_conf.outputMax = (float) iFlap_rmax.getValue();
	pid_conf.kp = (float) iPID_CP.getValue() / FI_SCALE;
	pid_conf.ki = (float) iPID_CI.getValue() / FI_SCALE;
	pid_conf.kd = (float) iPID_CD.getValue() / FI_SCALE;
	pid_conf.dt = (float) iPID_sampPeriod.getValue() / FI_SCALE;

	presenter->setPIDValues(pid_conf);

	application().gotoserviceScreenScreenNoTransition();
}

