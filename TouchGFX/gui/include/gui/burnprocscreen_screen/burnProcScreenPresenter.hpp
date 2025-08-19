#ifndef BURNPROCSCREENPRESENTER_HPP
#define BURNPROCSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class burnProcScreenView;

class burnProcScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    burnProcScreenPresenter(burnProcScreenView& v);

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

    virtual ~burnProcScreenPresenter() {}

    void setBurnPhasesValues(burnPhases_st burnPh);

    void setBurningValues(uint16_t temp, uint16_t o2);
    void setBurningOutValues(uint16_t temp, uint16_t pflap, uint16_t sflap);
    void setGlowingEmbersValues(uint16_t timeout, uint16_t pflap, uint16_t sflap);
    void setVentilationValues(uint16_t time, uint16_t pflap, uint16_t sflap);


private:
    burnProcScreenPresenter();

    burnProcScreenView& view;

    burnPhases_st burnPh;
};

#endif // BURNPROCSCREENPRESENTER_HPP
