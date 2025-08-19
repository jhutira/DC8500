#ifndef SERVICESCREENPRESENTER_HPP
#define SERVICESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class serviceScreenView;

class serviceScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    serviceScreenPresenter(serviceScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~serviceScreenPresenter() {}

private:
    serviceScreenPresenter();

    serviceScreenView& view;
};

#endif // SERVICESCREENPRESENTER_HPP
