#ifndef EXCHANSCREENPRESENTER_HPP
#define EXCHANSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

#include "reg.h"

using namespace touchgfx;

class exchanScreenView;

class exchanScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    exchanScreenPresenter(exchanScreenView& v);

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

    virtual ~exchanScreenPresenter() {}

    void setExchangerValues(waterExch_st ex);

private:
    exchanScreenPresenter();

    exchanScreenView& view;
};

#endif // EXCHANSCREENPRESENTER_HPP
