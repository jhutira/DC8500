#ifndef PASSWORDSCREENVIEW_HPP
#define PASSWORDSCREENVIEW_HPP

#include <gui_generated/passwordscreen_screen/passwordScreenViewBase.hpp>
#include <gui/passwordscreen_screen/passwordScreenPresenter.hpp>

class passwordScreenView : public passwordScreenViewBase
{
public:
    passwordScreenView();
    virtual ~passwordScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void enterBtnClicked();
protected:
};

#endif // PASSWORDSCREENVIEW_HPP
