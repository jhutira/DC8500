#ifndef PFLAPSCREENVIEW_HPP
#define PFLAPSCREENVIEW_HPP

#include <gui_generated/pflapscreen_screen/pflapScreenViewBase.hpp>
#include <gui/pflapscreen_screen/pflapScreenPresenter.hpp>
#include <gui/containers/MenuList_HeaderCont.hpp>
#include <gui/containers/MenuList_ItemNumberCont.hpp>

class pflapScreenView : public pflapScreenViewBase
{
public:
    pflapScreenView();
    virtual ~pflapScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void initPIDValues(pidConfig_st pid_conf);

    void textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e);

    void okBtn_clicked();
protected:
    Callback<pflapScreenView, const TextAreaWithOneWildcard&, const ClickEvent&> textAreaClickedCallback;

    MenuList_HeaderCont hFlap;
    MenuList_ItemNumberCont iFlap_rmin;
    MenuList_ItemNumberCont iFlap_rmax;

    MenuList_HeaderCont hPID;
    MenuList_ItemNumberCont iPID_sampPeriod;
    MenuList_ItemNumberCont iPID_CP;
    MenuList_ItemNumberCont iPID_CI;
    MenuList_ItemNumberCont iPID_CD;

};

#endif // PFLAPSCREENVIEW_HPP
