#ifndef LANGSCREENPRESENTER_HPP
#define LANGSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class langScreenView;

class langScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    langScreenPresenter(langScreenView& v);

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

    virtual ~langScreenPresenter() {}

    void setLanguageId(uint8_t id);

private:
    langScreenPresenter();

    langScreenView& view;
};

#endif // LANGSCREENPRESENTER_HPP
