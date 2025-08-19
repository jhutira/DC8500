#ifndef EDITTIMEDLGCONT_HPP
#define EDITTIMEDLGCONT_HPP

#include <gui_generated/containers/EditTimeDlgContBase.hpp>
#include <touchgfx/containers/ModalWindow.hpp>

#include <gui/containers/MenuList_ItemTimeCont.hpp>

class EditTimeDlgCont : public EditTimeDlgContBase
{
public:
    EditTimeDlgCont();
    virtual ~EditTimeDlgCont() {}

    virtual void initialize();

    void showModal(ModalWindow* pModal, MenuList_ItemTimeCont* pItem);

	void setOkBtnClickListener(touchgfx::GenericCallback<>* callback)
	{
		_okButtonCallback = callback;
	}
protected:

	uint8_t _valH = 0;
	uint8_t _valM = 0;

	ModalWindow* _pModal = nullptr;
	MenuList_ItemTimeCont* _pItem = nullptr;

	void okBtn_clicked();
	void closeBtn_clicked();
	void upBtnH_clicked();
	void downBtnH_clicked();
	void upBtnM_clicked();
	void downBtnM_clicked();

	void _update_value(uint8_t valH, uint8_t valM);

private:
	touchgfx::GenericCallback<>* _okButtonCallback = nullptr;
};

#endif // EDITTIMEDLGCONT_HPP
