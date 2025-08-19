#ifndef MENULIST_ITEMSWITCHCONT_HPP
#define MENULIST_ITEMSWITCHCONT_HPP

#include <gui_generated/containers/MenuList_ItemSwitchContBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Callback.hpp>

class MenuList_ItemSwitchCont : public MenuList_ItemSwitchContBase
{
public:
    MenuList_ItemSwitchCont();
    virtual ~MenuList_ItemSwitchCont() {}

    virtual void initialize();

    /**
       * Initialize this containers widgets
       */
    void setupListItem(int16_t ofs, TEXTS nameTextID);


    void setState(bool on)
    {
    	toggleBtn.forceState(on);
    }

    bool getState()
    {
    	return toggleBtn.getState();
    }

    touchgfx::ToggleButton* getToogleButton()
	{
    	return &toggleBtn;
	}

protected:

};

#endif // MENULIST_ITEMSWITCHCONT_HPP
