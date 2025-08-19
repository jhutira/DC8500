#ifndef DATESCREENPRESENTER_HPP
#define DATESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class dateScreenView;

class dateScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    dateScreenPresenter(dateScreenView& v);

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

    virtual ~dateScreenPresenter() {}

    void setDate(uint8_t d, uint8_t m, uint8_t y);

private:
    dateScreenPresenter();

    dateScreenView& view;
};

#endif // DATESCREENPRESENTER_HPP
