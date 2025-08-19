#ifndef MODESCREENVIEW_HPP
#define MODESCREENVIEW_HPP

#include <gui_generated/modescreen_screen/modeScreenViewBase.hpp>
#include <gui/modescreen_screen/modeScreenPresenter.hpp>
#include <gui/containers/MenuList_HeaderCont.hpp>
#include <gui/containers/MenuList_ItemNumberCont.hpp>
#include <gui/containers/MenuList_ItemSwitchCont.hpp>

#include <images/BitmapDatabase.hpp>


class modeScreenView : public modeScreenViewBase
{
public:
    modeScreenView();
    virtual ~modeScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void initRegSch(uint8_t sch);
    void initDoor(door_st door);

    void textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e);

    void okBtn_clicked();
    void leftBtn_clicked();
    void rightBtn_clicked();


protected:
    Callback<modeScreenView, const TextAreaWithOneWildcard&, const ClickEvent&> textAreaClickedCallback;

    uint8_t mRegSch = SCH_01;


    MenuList_HeaderCont hDoorSw;
    MenuList_ItemSwitchCont iDoorSw;
    MenuList_ItemNumberCont iDoorSw_timeout;

    const uint16_t TAB_IMG_SCH[SCH_COUNT] = { BITMAP_SCH1_ID, BITMAP_SCH2_ID, BITMAP_SCH3_ID, BITMAP_SCH4_ID, BITMAP_SCH5_ID,
    										  BITMAP_SCH6_ID, BITMAP_SCH7_ID, BITMAP_SCH8_ID };
};

#endif // MODESCREENVIEW_HPP
