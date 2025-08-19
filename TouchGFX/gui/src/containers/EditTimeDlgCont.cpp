#include <gui/containers/EditTimeDlgCont.hpp>

EditTimeDlgCont::EditTimeDlgCont()
{

}

void EditTimeDlgCont::initialize()
{
    EditTimeDlgContBase::initialize();
}

/******************************************************************************
** showModal
******************************************************************************/
void EditTimeDlgCont::showModal(ModalWindow* pModal, MenuList_ItemTimeCont* pItem)
{
	_pModal = pModal;
	_pItem = pItem;
	_valH = _pItem->getHours();
	_valM = _pItem->getMinutes();

	touchgfx::Unicode::snprintf(v_nameBuffer, V_NAME_SIZE,"%s",
		_pItem->getTypedTextFromName().getText()
	);

	v_name.setWildcard(v_nameBuffer);
	v_name.invalidate();

	_update_value(_valH, _valM );

	pModal->setVisible(true);
	pModal->invalidate();
}

/******************************************************************************
** _print_value
******************************************************************************/
void EditTimeDlgCont::_update_value(uint8_t valH, uint8_t valM)
{
	touchgfx::Unicode::snprintf(v_valueBuffer, V_VALUE_SIZE, "%d:%.2d", valH, valM);
	v_value.setWildcard(v_valueBuffer);
	v_value.invalidate();
}

/******************************************************************************
** okBtn_clicked
******************************************************************************/
void EditTimeDlgCont::okBtn_clicked()
{
	if (_pModal != nullptr)
	{
		_pModal->setVisible(false);
		_pModal->invalidate();
	}

	if (_pItem != nullptr)
	{
		_pItem->setValue(_valH, _valM);
	}

	if (_okButtonCallback != nullptr)
	{
		_okButtonCallback->execute();
	}
}

/******************************************************************************
** closeBtn_clicked
******************************************************************************/
void EditTimeDlgCont::closeBtn_clicked()
{
	if (_pModal != nullptr)
	{
		_pModal->setVisible(false);
		_pModal->invalidate();
	}
}

/******************************************************************************
** upBtnH_clicked
******************************************************************************/
void EditTimeDlgCont::upBtnH_clicked()
{
	if (_valH < 23)
	{
		_valH++;
		_update_value(_valH, _valM );
	}
}

/******************************************************************************
** downBtnH_clicked
******************************************************************************/
void EditTimeDlgCont::downBtnH_clicked()
{
	if (_valH > 0)
	{
		_valH--;
		_update_value(_valH, _valM );
	}
}

/******************************************************************************
** upBtnM_clicked
******************************************************************************/
void EditTimeDlgCont::upBtnM_clicked()
{
	if (_valM < 59)
	{
		_valM++;
		_update_value(_valH, _valM );
	}
}

/******************************************************************************
** downBtnM_clicked
******************************************************************************/
void EditTimeDlgCont::downBtnM_clicked()
{
	if (_valM > 0)
	{
		_valM--;
		_update_value(_valH, _valM );
	}
}
