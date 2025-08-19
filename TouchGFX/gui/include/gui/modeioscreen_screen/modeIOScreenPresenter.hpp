#ifndef MODEIOSCREENPRESENTER_HPP
#define MODEIOSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class modeIOScreenView;

class modeIOScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    modeIOScreenPresenter(modeIOScreenView& v);

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

    virtual ~modeIOScreenPresenter() {}

    void saveOutputComboBox(uint8_t n, uint8_t index);
    void saveDInComboBox(uint8_t n, uint8_t index);
    void saveCModeP1Box(uint8_t index, uint8_t minV, uint8_t maxV);


private:
    modeIOScreenPresenter();

    modeIOScreenView& view;
};

#endif // MODEIOSCREENPRESENTER_HPP
