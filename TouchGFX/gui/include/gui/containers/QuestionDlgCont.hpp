#ifndef QUESTIONDLGCONT_HPP
#define QUESTIONDLGCONT_HPP

#include <gui_generated/containers/QuestionDlgContBase.hpp>
#include <touchgfx/containers/ModalWindow.hpp>
#include <functional>

#include <touchgfx/Unicode.hpp>

class QuestionDlgCont : public QuestionDlgContBase
{
public:
    QuestionDlgCont();
    virtual ~QuestionDlgCont() {}

    virtual void initialize();

    void showModal(ModalWindow* modal, const touchgfx::TypedText& msg);

    void setOkButtonCallback(std::function<void()> callback);

protected:

	void okBtn_clicked();
	void closeBtn_clicked();

private:
	ModalWindow* pModal = nullptr;
	std::function<void()> okButtonCallback;
};

#endif // QUESTIONDLGCONT_HPP
