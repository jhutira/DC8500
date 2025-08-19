#ifndef SFLAPSCREENPRESENTER_HPP
#define SFLAPSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class sflapScreenView;

class sflapScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    sflapScreenPresenter(sflapScreenView& v);

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

    virtual ~sflapScreenPresenter() {}

    void setPIDValues(pidConfig_st conf);

private:
    sflapScreenPresenter();

    sflapScreenView& view;
};

#endif // SFLAPSCREENPRESENTER_HPP
