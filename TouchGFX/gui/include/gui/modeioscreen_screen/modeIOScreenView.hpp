#ifndef MODEIOSCREENVIEW_HPP
#define MODEIOSCREENVIEW_HPP

#include <gui_generated/modeioscreen_screen/modeIOScreenViewBase.hpp>
#include <gui/modeioscreen_screen/modeIOScreenPresenter.hpp>
#include <gui/containers/MenuList_HeaderCont.hpp>
#include <gui/containers/MenuList_ItemNumberCont.hpp>
#include <gui/containers/MenuList_ItemComboBoxCont.hpp>

class modeIOScreenView : public modeIOScreenViewBase
{
public:
    modeIOScreenView();
    virtual ~modeIOScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e);

    void okBtn_clicked();

    void initOutputComboBox(uint8_t n, uint8_t inv);
    void initDInComboBox(uint8_t n, uint8_t inv);
    void initCModeP1Box(uint8_t index, uint8_t minV, uint8_t maxV);

protected:
    Callback<modeIOScreenView, const TextAreaWithOneWildcard&, const ClickEvent&> textAreaClickedCallback;

    MenuList_HeaderCont hPumpP1;
    MenuList_HeaderCont hOutputs;
    MenuList_HeaderCont hDin;
    MenuList_ItemComboBoxCont iCModeP1;
    MenuList_ItemComboBoxCont iOut[5];
    MenuList_ItemNumberCont iMinP1;
    MenuList_ItemNumberCont iMaxP1;
    MenuList_ItemComboBoxCont iDIn[2];
};

#endif // MODEIOSCREENVIEW_HPP
