#ifndef BOILERSCREENVIEW_HPP
#define BOILERSCREENVIEW_HPP

#include <gui_generated/boilerscreen_screen/boilerScreenViewBase.hpp>
#include <gui/boilerscreen_screen/boilerScreenPresenter.hpp>
#include <gui/containers/MenuList_ItemNumberCont.hpp>

class boilerScreenView : public boilerScreenViewBase
{
public:
    boilerScreenView();
    virtual ~boilerScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e);

    void okBtn_clicked();
protected:
    Callback<boilerScreenView, const TextAreaWithOneWildcard&, const ClickEvent&> textAreaClickedCallback;

	MenuList_ItemNumberCont iRqT;
	MenuList_ItemNumberCont iHyst;
	MenuList_ItemNumberCont iDTOn;
	MenuList_ItemNumberCont iDTOff;
};

#endif // BOILERSCREENVIEW_HPP
