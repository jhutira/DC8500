#ifndef MENULIST_ITEMNUMBERCONT_HPP
#define MENULIST_ITEMNUMBERCONT_HPP

#include <gui_generated/containers/MenuList_ItemNumberContBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

#include "gui/common/DefnGui.hpp"


class MenuList_ItemNumberCont : public MenuList_ItemNumberContBase
{
public:
    MenuList_ItemNumberCont();
    virtual ~MenuList_ItemNumberCont() {}

    virtual void initialize();

    void setupListItem(int16_t ofs, TEXTS nameTextID, uint16_t value, const char* unitText, eTypeValue typeValue = eTypeValue::tUInt);
    void setupListItem(int16_t ofs, TEXTS nameTextID, uint16_t value, const Unicode::UnicodeChar* unitText, eTypeValue typeValue = eTypeValue::tUInt);

    void setValue(uint16_t value);

    uint16_t getValue()
    {
    	return _value;
    }

    eTypeValue getTypeValue()
	{
		return _typeValue;
	}

    void setValueClickListener(touchgfx::GenericCallback<const touchgfx::TextAreaWithOneWildcard&, const touchgfx::ClickEvent&>& callback)
    {
    	ta_value.setClickAction(callback);
    }

    touchgfx::TextAreaWithOneWildcard& getValueTextArea()
    {
    	return ta_value;
    }

    touchgfx::TypedText getTypedTextFromName()
    {
      	return ta_name.getTypedText();
    }

    touchgfx::TypedText getTypedTextFromUnit()
    {
       	return ta_unit.getTypedText();
    }

    void setVisibleItem(bool vis)
	{
		if (vis)
		{
			setHeight(originalHeight);
			setVisible(true);
		}
		else
		{
			originalHeight = getHeight();
			setHeight(0);
			setVisible(false);
		}
		invalidate();
	}


private:
    uint16_t _value = 0;
    int originalHeight = 50;
    eTypeValue _typeValue = eTypeValue::tUInt;
};

#endif // MENULIST_ITEMNUMBERCONT_HPP
