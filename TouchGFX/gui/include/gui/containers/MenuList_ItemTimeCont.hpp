#ifndef MENULIST_ITEMTIMECONT_HPP
#define MENULIST_ITEMTIMECONT_HPP

#include <gui_generated/containers/MenuList_ItemTimeContBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class MenuList_ItemTimeCont : public MenuList_ItemTimeContBase
{
public:
    MenuList_ItemTimeCont();
    virtual ~MenuList_ItemTimeCont() {}

    virtual void initialize();

    void setupListItem(int16_t ofs, TEXTS nameTextID, uint8_t valH, uint8_t valM);
    void setValue(uint8_t h, uint8_t m);

    uint16_t getHours()
	{
		return _valH;
	}
    uint16_t getMinutes()
	{
		return _valM;
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


private:


protected:

private:
    uint8_t _valH = 0;
    uint8_t _valM = 0;
};

#endif // MENULIST_ITEMTIMECONT_HPP
