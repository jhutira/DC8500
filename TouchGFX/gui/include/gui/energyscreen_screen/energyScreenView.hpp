#ifndef ENERGYSCREENVIEW_HPP
#define ENERGYSCREENVIEW_HPP

#include <gui_generated/energyscreen_screen/energyScreenViewBase.hpp>
#include <gui/energyscreen_screen/energyScreenPresenter.hpp>
#include <gui/containers/MenuList_HeaderCont.hpp>
#include <gui/containers/MenuList_ItemNumberCont.hpp>
#include <gui/containers/MenuList_ItemSwitchCont.hpp>
#include <gui/containers/MenuList_ItemComboBoxCont.hpp>

class energyScreenView : public energyScreenViewBase
{
public:
    energyScreenView();
    virtual ~energyScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void initFlowmeterSett(flowmeter_sett_st sett);

	void okBtn_clicked();
	void clearEngBtn_clicked();

	void qd_okBtn_clicked();

	void onTextAreaClick(const TextAreaWithOneWildcard& src, const ClickEvent& e);

	void onComboChanged(const ComboBoxCont& src, uint16_t index);

	void onToggleButttonChanged(const touchgfx::AbstractButton& src);

protected:
	touchgfx::Callback<energyScreenView, const TextAreaWithOneWildcard&, const ClickEvent&> textAreaClickedCallback;

	touchgfx::Callback<energyScreenView, const touchgfx::AbstractButton&> toggleButtonCallback;

	touchgfx::Callback<energyScreenView, const ComboBoxCont&, uint16_t> itemSelectedCallback;

	MenuList_HeaderCont hFlowmeter;
	MenuList_ItemComboBoxCont iFlowType;
	MenuList_ItemNumberCont iQFactor;
	MenuList_ItemSwitchCont iViewFlow;
};

#endif // ENERGYSCREENVIEW_HPP
