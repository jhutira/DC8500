#include <gui/containers/QuestionDlgCont.hpp>

QuestionDlgCont::QuestionDlgCont()
{

}

void QuestionDlgCont::initialize()
{
    QuestionDlgContBase::initialize();
}

/******************************************************************************
** showModal
******************************************************************************/
void QuestionDlgCont::showModal(ModalWindow* modal, const touchgfx::TypedText& msg)
{
	pModal = modal;

	v_qd_msg.setTypedText(msg);
	v_qd_msg.invalidate();

	if (pModal)
	{
		pModal->setVisible(true);
		pModal->invalidate();
	}
}

/******************************************************************************
** setOkButtonCallback
******************************************************************************/
void QuestionDlgCont::setOkButtonCallback(std::function<void()> callback)
{
    okButtonCallback = std::move(callback);
}

/******************************************************************************
** okBtn_clicked
******************************************************************************/
void QuestionDlgCont::okBtn_clicked()
{
	if (pModal != nullptr)
	{
		pModal->setVisible(false);
		pModal->invalidate();
	}

	if (okButtonCallback)
	{
		okButtonCallback();
	}
}

/******************************************************************************
** closeBtn_clicked
******************************************************************************/
void QuestionDlgCont::closeBtn_clicked()
{
	if (pModal != nullptr)
	{
		pModal->setVisible(false);
		pModal->invalidate();
	}
}
