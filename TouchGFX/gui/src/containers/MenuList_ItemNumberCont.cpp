#include <gui/containers/MenuList_ItemNumberCont.hpp>
#include <touchgfx/Callback.hpp>



MenuList_ItemNumberCont::MenuList_ItemNumberCont()
{

}

void MenuList_ItemNumberCont::initialize()
{
    MenuList_ItemNumberContBase::initialize();
}


void MenuList_ItemNumberCont::setupListItem(int16_t ofs, TEXTS nameTextID, uint16_t value, const char* unitText, eTypeValue typeValue)
{
	ta_name.setX(10 + ofs);
	ta_name.setTypedText(TypedText(nameTextID));
    ta_name.resizeToCurrentText();

    _typeValue = typeValue;
    setValue(value);

    touchgfx::Unicode::strncpy(ta_unitBuffer, unitText, TA_UNIT_SIZE - 1);
    ta_unitBuffer[TA_UNIT_SIZE - 1] = 0; // Null-terminácia
    ta_unit.setWildcard(ta_unitBuffer);

    invalidate();
}

void MenuList_ItemNumberCont::setupListItem(int16_t ofs, TEXTS nameTextID, uint16_t value, const Unicode::UnicodeChar* unitText, eTypeValue typeValue)
{
	ta_name.setX(10 + ofs);
	ta_name.setTypedText(TypedText(nameTextID));
    ta_name.resizeToCurrentText();

    _typeValue = typeValue;
    setValue(value);

    touchgfx::Unicode::snprintf(ta_unitBuffer, TA_UNIT_SIZE, "%u", unitText);
    ta_unit.setWildcard(ta_unitBuffer);
    invalidate();
}

void MenuList_ItemNumberCont::setValue(uint16_t value)
{
	_value = value;

	switch (_typeValue)
	{
		case eTypeValue::tUInt:
			touchgfx::Unicode::snprintf(ta_valueBuffer, TA_VALUE_SIZE, "%u", _value);
			break;

		case eTypeValue::tUInt_1Dec:
			touchgfx::Unicode::snprintf(ta_valueBuffer, TA_VALUE_SIZE, "%u.%u", _value / 10, abs(_value % 10));
			break;
	}
	ta_value.setWildcard(ta_valueBuffer);
	ta_value.invalidate();
}


