#include <gui/burnscreen_screen/burnScreenView.hpp>
#include <gui/burnscreen_screen/burnScreenPresenter.hpp>

burnScreenPresenter::burnScreenPresenter(burnScreenView& v)
    : view(v)
{

}

void burnScreenPresenter::activate()
{
	view.initProfile(model->getBurnProfile());
}

void burnScreenPresenter::deactivate()
{

}

void burnScreenPresenter::setProfile(burn_profile_st prof)
{
	model->setBurnProfile(prof);
}
