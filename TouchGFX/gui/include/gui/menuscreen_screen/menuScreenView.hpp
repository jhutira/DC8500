#ifndef MENUSCREENVIEW_HPP
#define MENUSCREENVIEW_HPP

#include <gui_generated/menuscreen_screen/menuScreenViewBase.hpp>
#include <gui/menuscreen_screen/menuScreenPresenter.hpp>

class menuScreenView : public menuScreenViewBase
{
public:
    menuScreenView();
    virtual ~menuScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void enableButtons(uint8_t enDistribBtn, uint8_t enAccumBtn, uint8_t enBoilerBtn);

    void serviceBtnClicked();
protected:
};

#endif // MENUSCREENVIEW_HPP
