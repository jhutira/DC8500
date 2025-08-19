#include <gui/containers/MenuList_HeaderCont.hpp>

MenuList_HeaderCont::MenuList_HeaderCont()
{

}

void MenuList_HeaderCont::initialize()
{
    MenuList_HeaderContBase::initialize();
}

void MenuList_HeaderCont::setupListItem(TEXTS nameTextID)
{
	ta_name.setTypedText(TypedText(nameTextID));
    ta_name.resizeToCurrentText();
    invalidate();
}

