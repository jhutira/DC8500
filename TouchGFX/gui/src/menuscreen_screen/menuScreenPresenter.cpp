#include <gui/menuscreen_screen/menuScreenView.hpp>
#include <gui/menuscreen_screen/menuScreenPresenter.hpp>

menuScreenPresenter::menuScreenPresenter(menuScreenView& v)
    : view(v)
{

}

void menuScreenPresenter::activate()
{
	uint8_t d, a, b;

	if (modus & mUSE_2LOOPS) d = 1; else d = 0;
	if (modus & mUSE_ACCUM) a = 1; else a = 0;
	if (modus & mUSE_BOILER) b = 1; else b = 0;

	view.enableButtons(d, a, b);
}

void menuScreenPresenter::deactivate()
{

}
