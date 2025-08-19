#include <gui/containers/MenuList_ItemSwitchCont.hpp>

MenuList_ItemSwitchCont::MenuList_ItemSwitchCont()
{

}

void MenuList_ItemSwitchCont::initialize()
{
    MenuList_ItemSwitchContBase::initialize();
}

void MenuList_ItemSwitchCont::setupListItem(int16_t ofs, TEXTS nameTextID)
{
	ta_name.setX(10 + ofs);
	ta_name.setTypedText(TypedText(nameTextID));
    ta_name.resizeToCurrentText();

    invalidate();
}


