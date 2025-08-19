#ifndef EDITNUMDLGCONT_HPP
#define EDITNUMDLGCONT_HPP

#include <gui_generated/containers/EditNumDlgContBase.hpp>
#include <touchgfx/containers/ModalWindow.hpp>

#include <touchgfx/Unicode.hpp>
#include <gui/containers/MenuList_ItemNumberCont.hpp>


class EditNumDlgCont : public EditNumDlgContBase
{
public:
    EditNumDlgCont();
    virtual ~EditNumDlgCont() {}

    virtual void initialize();

    void showModal(ModalWindow* pModal, MenuList_ItemNumberCont* pItem, uint16_t minVal, uint16_t maxVal);

	void setOkBtnClickListener(touchgfx::GenericCallback<>* callback)
	{
		_okButtonCallback = callback;
	}

protected:

	uint16_t _minVal = 0;
	uint16_t _maxVal = 99;
	uint16_t _value = 0;
	eTypeValue _typeVal = eTypeValue::tUInt;
	bool fBtnChangeVal = true;

	ModalWindow* _pModal = nullptr;
	MenuList_ItemNumberCont* _pItem = nullptr;

	void okBtn_clicked();
	void closeBtn_clicked();
	void upBtn_clicked();
	void downBtn_clicked();

	void sliderChangeVal(int value);

	void _print_value(touchgfx::Unicode::UnicodeChar* dst, uint16_t dstSize, eTypeValue tv, uint16_t val);

private:

	touchgfx::GenericCallback<>* _okButtonCallback = nullptr;
};

#endif // EDITNUMDLGCONT_HPP
