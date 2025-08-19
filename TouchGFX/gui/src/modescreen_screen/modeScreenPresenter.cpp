#include <gui/modescreen_screen/modeScreenView.hpp>
#include <gui/modescreen_screen/modeScreenPresenter.hpp>


modeScreenPresenter::modeScreenPresenter(modeScreenView& v)
    : view(v)
{

}

void modeScreenPresenter::activate()
{
	view.initRegSch(model->getRegScheme());
	view.initDoor(model->getFireplaceDoor());
}

void modeScreenPresenter::deactivate()
{

}

void modeScreenPresenter::setRegSch(uint8_t sch)
{
	model->setRegScheme(sch);
}

void modeScreenPresenter::setDoor(door_st door)
{
	model->setFireplaceDoor(door);
}

