#include <gui/burnscreen_screen/burnScreenView.hpp>

#include <gui/common/DefnGui.hpp>

// in constuctor, bind this view object to function which handles the event:
burnScreenView::burnScreenView() :
    textAreaClickedCallback(this, &burnScreenView::textAreaClickHandler)
{
}



void burnScreenView::setupScreen()
{
	burnScreenViewBase::setupScreen();

    scrollCnt.setScrollbarWidth(5);
    list.setHeight(0);

    headerRegPower.setupListItem(T_SH_REGPOWER);
    list.add(headerRegPower);

    itemMaxTF.setupListItem(20, T_S_MAXFLUETEMP, 0, DegCel);
    itemMaxTF.setValueClickListener(textAreaClickedCallback);
    list.add(itemMaxTF);

    itemMinTF.setupListItem(20, T_S_MINFLUETEMP, 0, DegCel);
    itemMinTF.setValueClickListener(textAreaClickedCallback);
    list.add(itemMinTF);
}

void burnScreenView::tearDownScreen()
{
    burnScreenViewBase::tearDownScreen();
}

void burnScreenView::textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e)
{
	if (e.getType() == ClickEvent::PRESSED)
	{
		if (&src == &itemMaxTF.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &itemMaxTF, 80, 400);
		}

		if (&src == &itemMinTF.getValueTextArea())
		{
			editNumDlgCont.showModal(&editNumDlg, &itemMinTF, 80, 400);
		}
	}
}

void burnScreenView::initProfile(burn_profile_st prof)
{
	itemMinTF.setValue(prof.minFlueTemp / 10);
	itemMaxTF.setValue(prof.maxFlueTemp / 10);
}

void burnScreenView::okBtn_clicked()
{
	burn_profile_st prof;

	prof.minFlueTemp = 10 * itemMinTF.getValue();
	prof.maxFlueTemp = 10 * itemMaxTF.getValue();

	presenter->setProfile(prof);
	application().gotomenuScreenScreenNoTransition();
}

