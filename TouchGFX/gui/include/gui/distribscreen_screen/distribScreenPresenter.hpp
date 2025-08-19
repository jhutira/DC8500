#ifndef DISTRIBSCREENPRESENTER_HPP
#define DISTRIBSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class distribScreenView;

class distribScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    distribScreenPresenter(distribScreenView& v);

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

    virtual ~distribScreenPresenter() {}

    uint8_t getDistrib();
    void setDistrib(uint8_t ds);

private:
    distribScreenPresenter();

    distribScreenView& view;
};

#endif // DISTRIBSCREENPRESENTER_HPP
