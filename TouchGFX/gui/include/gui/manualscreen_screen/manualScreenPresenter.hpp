#ifndef MANUALSCREENPRESENTER_HPP
#define MANUALSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class manualScreenView;

class manualScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    manualScreenPresenter(manualScreenView& v);

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

    virtual ~manualScreenPresenter() {}

    void setOutputMode(uint8_t n, uint8_t mode);
    void setFlapModeAndPos(uint8_t n, uint8_t mode, uint8_t pos);

    void saveOutputModes();

private:
    manualScreenPresenter();

    manualScreenView& view;
};

#endif // MANUALSCREENPRESENTER_HPP
