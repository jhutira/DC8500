#ifndef ACCUMSCREENVIEW_HPP
#define ACCUMSCREENVIEW_HPP

#include <gui_generated/accumscreen_screen/accumScreenViewBase.hpp>
#include <gui/accumscreen_screen/accumScreenPresenter.hpp>
#include <gui/containers/MenuList_ItemNumberCont.hpp>

class accumScreenView : public accumScreenViewBase
{
public:
    accumScreenView();
    virtual ~accumScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e);

    void okBtn_clicked();
protected:
    Callback<accumScreenView, const TextAreaWithOneWildcard&, const ClickEvent&> textAreaClickedCallback;

    MenuList_ItemNumberCont iMaxT;
    MenuList_ItemNumberCont iHyst;
    MenuList_ItemNumberCont iDTOn;
    MenuList_ItemNumberCont iDTOff;
};

#endif // ACCUMSCREENVIEW_HPP
