#ifndef SYSTEMSCREENPRESENTER_HPP
#define SYSTEMSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class systemScreenView;

class systemScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    systemScreenPresenter(systemScreenView& v);

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

    virtual ~systemScreenPresenter() {}

    void setDispSett(disp_sett_st sett);

    void setSoundSett(sound_sett_st sett);

    void setDefaultSettings();

private:
    systemScreenPresenter();

    systemScreenView& view;
};

#endif // SYSTEMSCREENPRESENTER_HPP
