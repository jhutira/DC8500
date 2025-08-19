#ifndef SYSTEMSCREENVIEW_HPP
#define SYSTEMSCREENVIEW_HPP

#include <gui_generated/systemscreen_screen/systemScreenViewBase.hpp>
#include <gui/systemscreen_screen/systemScreenPresenter.hpp>
#include <gui/containers/MenuList_HeaderCont.hpp>
#include <gui/containers/MenuList_ItemNumberCont.hpp>
#include <gui/containers/MenuList_ItemTimeCont.hpp>
#include <gui/containers/MenuList_ItemSwitchCont.hpp>

class systemScreenView : public systemScreenViewBase
{
public:
    systemScreenView();
    virtual ~systemScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void initDispSett(disp_sett_st sett);

    void initSoundSett(sound_sett_st sett);

    void okBtn_clicked();
    void defaultBtn_clicked();

    void qd_okBtn_clicked();


    void onTextAreaClick(const TextAreaWithOneWildcard& src, const ClickEvent& e);

    void onToggleButttonChanged(const touchgfx::AbstractButton& src);


protected:
    touchgfx::Callback<systemScreenView, const TextAreaWithOneWildcard&, const ClickEvent&> textAreaClickedCallback;

    touchgfx::Callback<systemScreenView, const touchgfx::AbstractButton&> toggleButtonCallback;

    MenuList_HeaderCont hSound;
    MenuList_ItemSwitchCont iSound_Alarm;
    MenuList_ItemSwitchCont iSound_Warn;
    MenuList_ItemSwitchCont iSound_Click;
    MenuList_ItemTimeCont iSound_QI_Start;
    MenuList_ItemTimeCont iSound_QI_End;

    MenuList_HeaderCont hDisplay;
    MenuList_ItemNumberCont iDisp_backlight;
    MenuList_ItemSwitchCont iSaver_en;
    MenuList_ItemNumberCont iSaver_time;
    MenuList_ItemNumberCont iSaver_backlight;

};

#endif // SYSTEMSCREENVIEW_HPP
