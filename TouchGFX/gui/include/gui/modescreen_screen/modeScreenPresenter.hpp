#ifndef MODESCREENPRESENTER_HPP
#define MODESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class modeScreenView;

class modeScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    modeScreenPresenter(modeScreenView& v);

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

    virtual ~modeScreenPresenter() {}

    void setRegSch(uint8_t sch);
    void setDoor(door_st door);

private:
    modeScreenPresenter();

    modeScreenView& view;
};

#endif // MODESCREENPRESENTER_HPP
