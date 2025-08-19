#ifndef INFOSCREENVIEW_HPP
#define INFOSCREENVIEW_HPP

#include <gui_generated/infoscreen_screen/infoScreenViewBase.hpp>
#include <gui/infoscreen_screen/infoScreenPresenter.hpp>

#include <gui/containers/ComboBoxCont.hpp>

class infoScreenView : public infoScreenViewBase
{
public:
    infoScreenView();
    virtual ~infoScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    Unicode::UnicodeChar textBuffer[20];

};

#endif // INFOSCREENVIEW_HPP
