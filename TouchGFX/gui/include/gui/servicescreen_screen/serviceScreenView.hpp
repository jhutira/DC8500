#ifndef SERVICESCREENVIEW_HPP
#define SERVICESCREENVIEW_HPP

#include <gui_generated/servicescreen_screen/serviceScreenViewBase.hpp>
#include <gui/servicescreen_screen/serviceScreenPresenter.hpp>

class serviceScreenView : public serviceScreenViewBase
{
public:
    serviceScreenView();
    virtual ~serviceScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SERVICESCREENVIEW_HPP
