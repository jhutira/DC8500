#ifndef EXSERVICESCREENPRESENTER_HPP
#define EXSERVICESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class exserviceScreenView;

class exserviceScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    exserviceScreenPresenter(exserviceScreenView& v);

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

    virtual ~exserviceScreenPresenter() {}

private:
    exserviceScreenPresenter();

    exserviceScreenView& view;
};

#endif // EXSERVICESCREENPRESENTER_HPP
