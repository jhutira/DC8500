#ifndef TIMESCREENPRESENTER_HPP
#define TIMESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class timeScreenView;

class timeScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    timeScreenPresenter(timeScreenView& v);

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

    virtual ~timeScreenPresenter() {}

    void setTime(uint8_t h, uint8_t m, uint8_t s);

private:
    timeScreenPresenter();

    timeScreenView& view;
};

#endif // TIMESCREENPRESENTER_HPP
