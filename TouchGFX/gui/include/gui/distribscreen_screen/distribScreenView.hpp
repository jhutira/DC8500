#ifndef DISTRIBSCREENVIEW_HPP
#define DISTRIBSCREENVIEW_HPP

#include <gui_generated/distribscreen_screen/distribScreenViewBase.hpp>
#include <gui/distribscreen_screen/distribScreenPresenter.hpp>

class distribScreenView : public distribScreenViewBase
{
public:
    distribScreenView();
    virtual ~distribScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void okBtnClicked();

    void initDistribBtn(uint8_t ds);
protected:
};

#endif // DISTRIBSCREENVIEW_HPP
