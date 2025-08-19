#include <gui/langscreen_screen/langScreenView.hpp>
#include <gui/langscreen_screen/langScreenPresenter.hpp>

langScreenPresenter::langScreenPresenter(langScreenView& v)
    : view(v)
{

}

void langScreenPresenter::activate()
{

}

void langScreenPresenter::deactivate()
{

}

void langScreenPresenter::setLanguageId(uint8_t id)
{
	model->saveLanguageId(id);
}
