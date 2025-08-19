#ifndef MAINSCREENPRESENTER_HPP
#define MAINSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

#include <main_util.h>
#include <texts/TextKeysAndLanguages.hpp>

using namespace touchgfx;

class mainScreenView;

class mainScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    mainScreenPresenter(mainScreenView& v);

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

    virtual ~mainScreenPresenter() {};

    void updateClock();

    void updateIcons(uint8_t blink);
    void updateSensors(void);
    void updateOutputs(void);
    void updateAirFlaps(void);

    void updatePAirFlap(void);
    void updateSAirFlap(void);

    void updateRegStatus(void);

    void updateEnergy(void);


    void updateDebug(void);

    void doorBtnAction();
    void doorBtnInit();

    void soundBtnAction(uint8_t press);

    void setBPrqFlueTemp(uint16_t t);


private:
    mainScreenPresenter();

    mainScreenView& view;

    const TEXTS BPH_MESSAGE[7] = { T_S_BP0_ESTOP, T_S_BP0_STOP, T_S_BP1_STARTBURNING, T_S_BP2_BURNING, T_S_BP3_BURNINGOUT, T_S_BP4_GLOWEMBERS, T_S_BP5_VENTIL};


};

#endif // MAINSCREENPRESENTER_HPP
