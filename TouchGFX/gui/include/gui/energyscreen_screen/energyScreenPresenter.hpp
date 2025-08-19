#ifndef ENERGYSCREENPRESENTER_HPP
#define ENERGYSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class energyScreenView;

class energyScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    energyScreenPresenter(energyScreenView& v);

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

    virtual ~energyScreenPresenter() {}

    void setFlowmeterSett(flowmeter_sett_st sett);

    void resetEnergyCnt();

private:
    energyScreenPresenter();

    energyScreenView& view;
};

#endif // ENERGYSCREENPRESENTER_HPP
