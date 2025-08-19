#include <gui/containers/EditNumDlgCont.hpp>

EditNumDlgCont::EditNumDlgCont()
{

}

void EditNumDlgCont::initialize()
{
    EditNumDlgContBase::initialize();
}

/******************************************************************************
** showModal
******************************************************************************/
void EditNumDlgCont::showModal(ModalWindow* pModal, MenuList_ItemNumberCont* pItem, uint16_t minVal, uint16_t maxVal)
{
	_pModal = pModal;
	_pItem = pItem;
	_minVal = minVal;
	_maxVal = maxVal;
	_value = _pItem->getValue();
	_typeVal = _pItem->getTypeValue();
	fBtnChangeVal = true;

	slider.setValueRange(_minVal, _maxVal, _value);
	slider.invalidate();

	_print_value(v_minValBuffer, V_MINVAL_SIZE, _typeVal, _minVal);
	v_minVal.setWildcard(v_minValBuffer);
	v_minVal.invalidate();

	_print_value(v_maxValBuffer, V_MAXVAL_SIZE, _typeVal, _maxVal);
	v_maxVal.setWildcard(v_maxValBuffer);
	v_maxVal.invalidate();

	touchgfx::Unicode::snprintf(v_nameBuffer, V_NAME_SIZE,"%s [%s]",
		_pItem->getTypedTextFromName().getText(),
		_pItem->getTypedTextFromUnit(). getText()

	); // u"°C"

	v_name.setWildcard(v_nameBuffer);
	v_name.invalidate();

	pModal->setVisible(true);
	pModal->invalidate();
}

/******************************************************************************
** _print_value
******************************************************************************/
void EditNumDlgCont::_print_value(touchgfx::Unicode::UnicodeChar* dst, uint16_t dstSize, eTypeValue tv, uint16_t val)
{
	switch (tv)
	{
		case eTypeValue::tUInt:
			touchgfx::Unicode::snprintf(dst, dstSize,"%u", val);
			break;

		case eTypeValue::tUInt_1Dec:
			touchgfx::Unicode::snprintf(dst, dstSize,"%u.%u", val / 10, abs(val % 10));
			break;

	}
}

/******************************************************************************
** okBtn_clicked
******************************************************************************/
void EditNumDlgCont::okBtn_clicked()
{
	if (_pModal != nullptr)
	{
		_pModal->setVisible(false);
		_pModal->invalidate();
	}

	if (_pItem != nullptr)
	{
		_pItem->setValue(_value);
	}

	if (_okButtonCallback != nullptr)
	{
		_okButtonCallback->execute();
	}
}

/******************************************************************************
** closeBtn_clicked
******************************************************************************/
void EditNumDlgCont::closeBtn_clicked()
{
	if (_pModal != nullptr)
	{
		_pModal->setVisible(false);
		_pModal->invalidate();
	}
}

/******************************************************************************
** upBtn_clicked
******************************************************************************/
void EditNumDlgCont::upBtn_clicked()
{
	if (_value < _maxVal)
	{
		_value++;
		fBtnChangeVal = true;
		slider.setValue(_value);
		slider.invalidate();
	}
}

/******************************************************************************
** downBtn_clicked
******************************************************************************/
void EditNumDlgCont::downBtn_clicked()
{
	if (_value > _minVal)
	{
		_value--;
		fBtnChangeVal = true;
		slider.setValue(_value);
		slider.invalidate();
	}
}

/******************************************************************************
** slider change value
******************************************************************************/
void EditNumDlgCont::sliderChangeVal(int value)
{
	if (fBtnChangeVal == true) fBtnChangeVal = false;
	  else _value = value;

	_print_value(v_valueBuffer, V_VALUE_SIZE, _typeVal, _value);
	v_value.setWildcard(v_valueBuffer);
	v_value.invalidate();
}
