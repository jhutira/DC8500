#ifndef BURNPROCSCREENVIEW_HPP
#define BURNPROCSCREENVIEW_HPP

#include <gui_generated/burnprocscreen_screen/burnProcScreenViewBase.hpp>
#include <gui/burnprocscreen_screen/burnProcScreenPresenter.hpp>
#include <gui/containers/MenuList_HeaderCont.hpp>
#include <gui/containers/MenuList_ItemNumberCont.hpp>

class burnProcScreenView : public burnProcScreenViewBase
{
public:
    burnProcScreenView();
    virtual ~burnProcScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void initBurnPhasesValues(burnPhases_st burnPh);

    void textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e);

    void okBtn_clicked();
protected:
    Callback<burnProcScreenView, const TextAreaWithOneWildcard&, const ClickEvent&> textAreaClickedCallback;

    MenuList_HeaderCont hPhStartBurning;
    MenuList_HeaderCont hPhBurning;
    MenuList_HeaderCont hPhBurningOut;
    MenuList_HeaderCont hPhGlowingEmbers;
    MenuList_HeaderCont hPhVetilation;

    MenuList_ItemNumberCont iSB_Timeout;
    MenuList_ItemNumberCont iSB_MinTempToBurn;

    MenuList_ItemNumberCont iBN_TempToBurnOut;
    MenuList_ItemNumberCont iBN_TimeToBurnOut;
    MenuList_ItemNumberCont iBN_O2;

    MenuList_ItemNumberCont iBO_TempToGlowEmb;
    MenuList_ItemNumberCont iBO_TimeToGlowEmb;
    MenuList_ItemNumberCont iBO_PFlap;

    MenuList_ItemNumberCont iGE_Timeout;
    MenuList_ItemNumberCont iGE_PFlap;
    MenuList_ItemNumberCont iGE_SFlap;

    MenuList_ItemNumberCont iVN_Time;
    MenuList_ItemNumberCont iVN_PFlap;
    MenuList_ItemNumberCont iVN_SFlap;
};

#endif // BURNPROCSCREENVIEW_HPP
