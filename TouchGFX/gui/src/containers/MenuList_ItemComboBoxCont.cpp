#include <gui/containers/MenuList_ItemComboBoxCont.hpp>

MenuList_ItemComboBoxCont::MenuList_ItemComboBoxCont()
{

}

void MenuList_ItemComboBoxCont::initialize()
{
    MenuList_ItemComboBoxContBase::initialize();
    setHeight(100);
}

void MenuList_ItemComboBoxCont::setupListItem(int16_t ofs, TEXTS nameTextID)
{
	ta_name.setX(10 + ofs);
	ta_name.setTypedText(TypedText(nameTextID));
    ta_name.resizeToCurrentText();

    invalidate();
}
