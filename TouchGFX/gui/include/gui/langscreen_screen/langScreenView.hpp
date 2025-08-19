#ifndef LANGSCREENVIEW_HPP
#define LANGSCREENVIEW_HPP

#include <gui_generated/langscreen_screen/langScreenViewBase.hpp>
#include <gui/langscreen_screen/langScreenPresenter.hpp>

class langScreenView : public langScreenViewBase
{
public:
    langScreenView();
    virtual ~langScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void svkBtnClicked();
    void engBtnClicked();
protected:
};

#endif // LANGSCREENVIEW_HPP
