#include <gui/containers/MenuList_ItemTimeCont.hpp>

MenuList_ItemTimeCont::MenuList_ItemTimeCont()
{

}

void MenuList_ItemTimeCont::initialize()
{
    MenuList_ItemTimeContBase::initialize();
}

void MenuList_ItemTimeCont::setupListItem(int16_t ofs, TEXTS nameTextID, uint8_t valH, uint8_t valM)
{
	ta_name.setX(10 + ofs);
	ta_name.setTypedText(TypedText(nameTextID));
    ta_name.resizeToCurrentText();

    setValue(valH, valM);

    invalidate();
}



void MenuList_ItemTimeCont::setValue(uint8_t h, uint8_t m)
{
	_valH = h;
	_valM = m;

	touchgfx::Unicode::snprintf(ta_valueBuffer, TA_VALUE_SIZE, "%d:%.2d", _valH, _valM);
	ta_value.setWildcard(ta_valueBuffer);
	ta_value.invalidate();
}
