#include <gui/accumscreen_screen/accumScreenView.hpp>

accumScreenView::accumScreenView() :
textAreaClickedCallback(this, &accumScreenView::textAreaClickHandler)
{

}

void accumScreenView::setupScreen()
{
    accumScreenViewBase::setupScreen();

    scrollCnt.setScrollbarWidth(7);
    list.setHeight(0);

    iMaxT.setupListItem(20, T_S_MAXTEMP, 95, DegCel);
    iMaxT.setValueClickListener(textAreaClickedCallback);
    list.add(iMaxT);

    iHyst.setupListItem(20, T_S_HYST, 5, DegCel);
    iHyst.setValueClickListener(textAreaClickedCallback);
    list.add(iHyst);

    iDTOn.setupListItem(20, T_S_DELTAT_ON, 5, DegCel);
    iDTOn.setValueClickListener(textAreaClickedCallback);
    list.add(iDTOn);

    iDTOff.setupListItem(20, T_S_DELTAT_OFF, 2, DegCel);
    iDTOff.setValueClickListener(textAreaClickedCallback);
    list.add(iDTOff);

}

void accumScreenView::tearDownScreen()
{
    accumScreenViewBase::tearDownScreen();
}

void accumScreenView::textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e)
{
	if (e.getType() == ClickEvent::PRESSED)
	{
		if (&src == &iMaxT.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iMaxT, 0, 100);
		}

		if (&src == &iHyst.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iHyst, 1, 50);
		}

		if (&src == &iDTOn.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iDTOn, 1, 50);
		}

		if (&src == &iDTOff.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iDTOff, 1, 50);
		}
	}
}

void accumScreenView::okBtn_clicked()
{

}

