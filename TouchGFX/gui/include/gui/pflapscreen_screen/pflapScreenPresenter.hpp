#ifndef PFLAPSCREENPRESENTER_HPP
#define PFLAPSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class pflapScreenView;

class pflapScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    pflapScreenPresenter(pflapScreenView& v);

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

    virtual ~pflapScreenPresenter() {}

    void setPIDValues(pidConfig_st conf);

private:
    pflapScreenPresenter();

    pflapScreenView& view;
};

#endif // PFLAPSCREENPRESENTER_HPP
