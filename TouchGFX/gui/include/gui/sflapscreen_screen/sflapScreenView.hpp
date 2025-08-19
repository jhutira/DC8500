#ifndef SFLAPSCREENVIEW_HPP
#define SFLAPSCREENVIEW_HPP

#include <gui_generated/sflapscreen_screen/sflapScreenViewBase.hpp>
#include <gui/sflapscreen_screen/sflapScreenPresenter.hpp>
#include <gui/containers/MenuList_HeaderCont.hpp>
#include <gui/containers/MenuList_ItemNumberCont.hpp>

class sflapScreenView : public sflapScreenViewBase
{
public:
    sflapScreenView();
    virtual ~sflapScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void initPIDValues(pidConfig_st pid_conf);

    void textAreaClickHandler(const TextAreaWithOneWildcard& src, const ClickEvent& e);

    void okBtn_clicked();
protected:

    Callback<sflapScreenView, const TextAreaWithOneWildcard&, const ClickEvent&> textAreaClickedCallback;

    MenuList_HeaderCont hFlap;
    MenuList_ItemNumberCont iFlap_rmin;
    MenuList_ItemNumberCont iFlap_rmax;

	MenuList_HeaderCont hPID;
	MenuList_ItemNumberCont iPID_sampPeriod;
	MenuList_ItemNumberCont iPID_CP;
	MenuList_ItemNumberCont iPID_CI;
	MenuList_ItemNumberCont iPID_CD;

};

#endif // SFLAPSCREENVIEW_HPP
