#include <gui/boilerscreen_screen/boilerScreenView.hpp>

boilerScreenView::boilerScreenView() :
textAreaClickedCallback(this, &boilerScreenView::textAreaClickHandler)
{

}

void boilerScreenView::setupScreen()
{
    boilerScreenViewBase::setupScreen();

    scrollCnt.setScrollbarWidth(7);
	list.setHeight(0);

	iRqT.setupListItem(20, T_S_RQTEMP, 60, DegCel);
	iRqT.setValueClickListener(textAreaClickedCallback);
	list.add(iRqT);

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

void boilerScreenView::tearDownScreen()
{
    boilerScreenViewBase::tearDownScreen();
}

void boilerScreenView::textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e)
{
	if (e.getType() == ClickEvent::PRESSED)
	{
		if (&src == &iRqT.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &iRqT, 0, 100);
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

void boilerScreenView::okBtn_clicked()
{

}
