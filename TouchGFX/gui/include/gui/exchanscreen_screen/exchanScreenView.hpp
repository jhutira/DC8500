#ifndef EXCHANSCREENVIEW_HPP
#define EXCHANSCREENVIEW_HPP

#include <gui_generated/exchanscreen_screen/exchanScreenViewBase.hpp>
#include <gui/exchanscreen_screen/exchanScreenPresenter.hpp>
#include <gui/containers/MenuList_HeaderCont.hpp>
#include <gui/containers/MenuList_ItemNumberCont.hpp>
#include <gui/containers/MenuList_ItemSwitchCont.hpp>

class exchanScreenView : public exchanScreenViewBase
{
public:
    exchanScreenView();
    virtual ~exchanScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void initExchangerValues(waterExch_st ex);

    void textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e);

    void okBtn_clicked();

protected:
    Callback<exchanScreenView, const TextAreaWithOneWildcard&, const ClickEvent&> textAreaClickedCallback;

    MenuList_HeaderCont hPmWater;
    MenuList_HeaderCont hMinTemp;
    MenuList_HeaderCont hCritTemp;
    MenuList_ItemNumberCont iPSWper;
    MenuList_ItemNumberCont iPSWtime;
    MenuList_ItemSwitchCont iPSWphBurn;
    MenuList_ItemSwitchCont iPSWphStBurn;
    MenuList_ItemSwitchCont iPSWphBurnOut;
    MenuList_ItemNumberCont iMTtemp;
    MenuList_ItemNumberCont iMThyst;
    MenuList_ItemNumberCont iCTtemp;
    MenuList_ItemNumberCont iCThyst;
    MenuList_ItemNumberCont iCTflap;
};

#endif // EXCHANSCREENVIEW_HPP
