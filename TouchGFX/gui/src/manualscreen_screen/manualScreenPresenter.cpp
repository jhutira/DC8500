#include <gui/manualscreen_screen/manualScreenView.hpp>
#include <gui/manualscreen_screen/manualScreenPresenter.hpp>

manualScreenPresenter::manualScreenPresenter(manualScreenView& v)
    : view(v)
{

}

void manualScreenPresenter::activate()
{
	uint8_t mode;
	uint8_t pos;
	uint8_t m;

	for (uint8_t n = 0; n < 5; n++)
	{
		mode = model->GetOutputMode(OUT_P1 + n);

		if ((mode & oMAN) == 0) m = 2;
		else
		if ((mode & oMAN) && (mode & oON)) m = 1;
		else
		m = 0;

		view.initOutput(n, m);
	}

	if (model->GetFlapMode(PRIM_F) & mMAN) m = 1; else m = 0;
	pos = model->GetFlapPos(PRIM_F);
	view.initPFlap(m , pos);

	if (model->GetFlapMode(SEC_F) & mMAN) m = 1; else m = 0;
	pos = model->GetFlapPos(SEC_F);
	view.initSFlap(m , pos);
}

void manualScreenPresenter::deactivate()
{

}

void manualScreenPresenter::setOutputMode(uint8_t n, uint8_t mode)
{
	model->SetOutputMode(n, mode);
}

void manualScreenPresenter::setFlapModeAndPos(uint8_t n, uint8_t mode, uint8_t pos)
{
	model->SetFlapModeAndPos(n, mode, pos);
}

