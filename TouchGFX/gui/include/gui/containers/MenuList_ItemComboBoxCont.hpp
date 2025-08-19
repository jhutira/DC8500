#ifndef MENULIST_ITEMCOMBOBOXCONT_HPP
#define MENULIST_ITEMCOMBOBOXCONT_HPP

#include <gui_generated/containers/MenuList_ItemComboBoxContBase.hpp>
#include <gui/containers/ComboBoxCont.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class MenuList_ItemComboBoxCont : public MenuList_ItemComboBoxContBase
{
public:
    MenuList_ItemComboBoxCont();
    virtual ~MenuList_ItemComboBoxCont() {}

    virtual void initialize();

    /**
     * Initialize this containers widgets
     */
    void setupListItem(int16_t ofs, TEXTS nameTextID);

    ComboBoxCont& getComboBox()
    {
    	return comboBox;
    }


protected:
};

#endif // MENULIST_ITEMCOMBOBOXCONT_HPP
