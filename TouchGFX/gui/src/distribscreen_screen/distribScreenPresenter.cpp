#include <gui/distribscreen_screen/distribScreenView.hpp>
#include <gui/distribscreen_screen/distribScreenPresenter.hpp>

distribScreenPresenter::distribScreenPresenter(distribScreenView& v)
    : view(v)
{

}

void distribScreenPresenter::activate()
{
	view.initDistribBtn(model->getDistrib());
}

void distribScreenPresenter::deactivate()
{

}

uint8_t distribScreenPresenter::getDistrib()
{
	return model->getDistrib();
}

void distribScreenPresenter::setDistrib(uint8_t ds)
{
	model->setDistrib(ds);
}
