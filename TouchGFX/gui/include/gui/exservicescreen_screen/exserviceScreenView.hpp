#ifndef EXSERVICESCREENVIEW_HPP
#define EXSERVICESCREENVIEW_HPP

#include <gui_generated/exservicescreen_screen/exserviceScreenViewBase.hpp>
#include <gui/exservicescreen_screen/exserviceScreenPresenter.hpp>

class exserviceScreenView : public exserviceScreenViewBase
{
public:
    exserviceScreenView();
    virtual ~exserviceScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // EXSERVICESCREENVIEW_HPP
