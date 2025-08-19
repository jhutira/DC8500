#ifndef BURNSCREENVIEW_HPP
#define BURNSCREENVIEW_HPP

#include <gui_generated/burnscreen_screen/burnScreenViewBase.hpp>
#include <gui/burnscreen_screen/burnScreenPresenter.hpp>
#include <gui/containers/MenuList_HeaderCont.hpp>
#include <gui/containers/MenuList_ItemNumberCont.hpp>
#include <gui/containers/MenuList_ItemSwitchCont.hpp>


class burnScreenView : public burnScreenViewBase
{
public:
    burnScreenView();
    virtual ~burnScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e);

    void okBtn_clicked();

    void initProfile(burn_profile_st prof);


private:


protected:
    Callback<burnScreenView, const TextAreaWithOneWildcard&, const ClickEvent&> textAreaClickedCallback;

    MenuList_HeaderCont headerRegPower;
    MenuList_ItemNumberCont itemMinTF;
    MenuList_ItemNumberCont itemMaxTF;
};

#endif // BURNSCREENVIEW_HPP
