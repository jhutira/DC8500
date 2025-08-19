#include <gui/manualscreen_screen/manualScreenView.hpp>

manualScreenView::manualScreenView()
{

}

void manualScreenView::setupScreen()
{
    manualScreenViewBase::setupScreen();

    touchgfx::Unicode::snprintf(&t_panel_p1Buffer[0], T_PANEL_P1_SIZE,"P1");
    touchgfx::Unicode::snprintf(&t_panel_p2Buffer[0], T_PANEL_P2_SIZE,"P2");
    touchgfx::Unicode::snprintf(&t_panel_y1Buffer[0], T_PANEL_Y1_SIZE,"Y1");
    touchgfx::Unicode::snprintf(&t_panel_y2Buffer[0], T_PANEL_Y2_SIZE,"Y2");
    touchgfx::Unicode::snprintf(&t_panel_y3Buffer[0], T_PANEL_Y3_SIZE,"Y3");
}

void manualScreenView::tearDownScreen()
{
    manualScreenViewBase::tearDownScreen();
}

void manualScreenView::initOutput(uint8_t n, uint8_t mode)
{
	if (n == OUT_P1)
	{
		p1_mode = mode;
		if (mode == 0) rbOff_p1.setSelected(true);
		if (mode == 1) rbOn_p1.setSelected(true);
		if (mode == 2) rbAuto_p1.setSelected(true);
	}
	if (n == OUT_P2)
	{
		p2_mode = mode;
		if (mode == 0) rbOff_p2.setSelected(true);
		if (mode == 1) rbOn_p2.setSelected(true);
		if (mode == 2) rbAuto_p2.setSelected(true);
	}
	if (n == OUT_Y1)
	{
		y1_mode = mode;
		if (mode == 0) rbOff_y1.setSelected(true);
		if (mode == 1) rbOn_y1.setSelected(true);
		if (mode == 2) rbAuto_y1.setSelected(true);
	}
	if (n == OUT_Y2)
	{
		y2_mode = mode;
		if (mode == 0) rbOff_y2.setSelected(true);
		if (mode == 1) rbOn_y2.setSelected(true);
		if (mode == 2) rbAuto_y2.setSelected(true);
	}
	if (n == OUT_Y3)
	{
		y3_mode = mode;
		if (mode == 0) rbOff_y3.setSelected(true);
		if (mode == 1) rbOn_y3.setSelected(true);
		if (mode == 2) rbAuto_y3.setSelected(true);
	}
}


void manualScreenView::initPFlap(uint8_t man, uint8_t pos)
{
	pf_man = man;
	pf_pos = pos;
	if (man) pfAutoBtn.forceState(false);
	  else pfAutoBtn.forceState(true);
	pfAutoBtn.invalidate();

	touchgfx::Unicode::snprintf(&t_pfBuffer[0], T_PF_SIZE,"%u%", pos);
	t_pf.setWildcard(t_pfBuffer);
	t_pf.invalidate();
}

void manualScreenView::initSFlap(uint8_t man, uint8_t pos)
{
	sf_man = man;
	sf_pos = pos;
	if (man) sfAutoBtn.forceState(false);
	  else sfAutoBtn.forceState(true);

	sfAutoBtn.invalidate();

	touchgfx::Unicode::snprintf(&t_sfBuffer[0], T_SF_SIZE,"%u%", pos);
	t_sf.setWildcard(t_sfBuffer);
	t_sf.invalidate();
}

/******************************************************************************
** pflap
******************************************************************************/
void manualScreenView::pfUpBtn_clicked()
{
	if (pf_pos < 100) pf_pos++;
	pf_man = 1;
	presenter->setFlapModeAndPos(PRIM_F, pf_man, pf_pos);
	initPFlap(pf_man, pf_pos);
}

void manualScreenView::pfDownBtn_clicked()
{
	if (pf_pos > 0) pf_pos--;
	pf_man = 1;
	presenter->setFlapModeAndPos(PRIM_F, pf_man, pf_pos);
	initPFlap(pf_man, pf_pos);
}

void manualScreenView::pfAutoBtn_clicked()
{
	pf_man = 0;
	presenter->setFlapModeAndPos(PRIM_F, pf_man, pf_pos);
	initPFlap(pf_man, pf_pos);
}

/******************************************************************************
** sflap
******************************************************************************/
void manualScreenView::sfUpBtn_clicked()
{
	if (sf_pos < 100) sf_pos++;
	sf_man = 1;
	presenter->setFlapModeAndPos(SEC_F, sf_man, sf_pos);
	initSFlap(sf_man, sf_pos);
}

void manualScreenView::sfDownBtn_clicked()
{
	if (sf_pos > 0) sf_pos--;
	sf_man = 1;
	presenter->setFlapModeAndPos(SEC_F, sf_man, sf_pos);
	initSFlap(sf_man, sf_pos);
}

void manualScreenView::sfAutoBtn_clicked()
{
	sf_man = 0;
	presenter->setFlapModeAndPos(SEC_F, sf_man, sf_pos);
	initSFlap(sf_man, sf_pos);
}

/******************************************************************************
** Out P1
******************************************************************************/
void manualScreenView::rbOnP1_clicked()
{
	p1_mode = 1;
	presenter->setOutputMode(OUT_P1, p1_mode);
	initOutput(OUT_P1, p1_mode);
}

void manualScreenView::rbOffP1_clicked()
{
	p1_mode = 0;
	presenter->setOutputMode(OUT_P1, p1_mode);
	initOutput(OUT_P1, p1_mode);
}

void manualScreenView::rbAutoP1_clicked()
{
	p1_mode = 2;
	presenter->setOutputMode(OUT_P1, p1_mode);
	initOutput(OUT_P1, p1_mode);
}

/******************************************************************************
** Out P2
******************************************************************************/
void manualScreenView::rbOnP2_clicked()
{
	p2_mode = 1;
	presenter->setOutputMode(OUT_P2, p2_mode);
	initOutput(OUT_P2, p2_mode);
}

void manualScreenView::rbOffP2_clicked()
{
	p2_mode = 0;
	presenter->setOutputMode(OUT_P2, p2_mode);
	initOutput(OUT_P2, p2_mode);
}

void manualScreenView::rbAutoP2_clicked()
{
	p2_mode = 2;
	presenter->setOutputMode(OUT_P2, p2_mode);
	initOutput(OUT_P2, p2_mode);
}

/******************************************************************************
** Out Y1
******************************************************************************/
void manualScreenView::rbOnY1_clicked()
{
	y1_mode = 1;
	presenter->setOutputMode(OUT_Y1, y1_mode);
	initOutput(OUT_Y1, y1_mode);
}

void manualScreenView::rbOffY1_clicked()
{
	y1_mode = 0;
	presenter->setOutputMode(OUT_Y1, y1_mode);
	initOutput(OUT_Y1, y1_mode);
}

void manualScreenView::rbAutoY1_clicked()
{
	y1_mode = 2;
	presenter->setOutputMode(OUT_Y1, y1_mode);
	initOutput(OUT_Y1, y1_mode);
}

/******************************************************************************
** Out Y2
******************************************************************************/
void manualScreenView::rbOnY2_clicked()
{
	y2_mode = 1;
	presenter->setOutputMode(OUT_Y2, y2_mode);
	initOutput(OUT_Y2, y2_mode);
}

void manualScreenView::rbOffY2_clicked()
{
	y2_mode = 0;
	presenter->setOutputMode(OUT_Y2, y2_mode);
	initOutput(OUT_Y2, y2_mode);
}

void manualScreenView::rbAutoY2_clicked()
{
	y2_mode = 2;
	presenter->setOutputMode(OUT_Y2, y2_mode);
	initOutput(OUT_Y2, y2_mode);
}

/******************************************************************************
** Out Y3
******************************************************************************/
void manualScreenView::rbOnY3_clicked()
{
	y3_mode = 1;
	presenter->setOutputMode(OUT_Y3, y3_mode);
	initOutput(OUT_Y3, y3_mode);
}

void manualScreenView::rbOffY3_clicked()
{
	y3_mode = 0;
	presenter->setOutputMode(OUT_Y3, y3_mode);
	initOutput(OUT_Y3, y3_mode);
}

void manualScreenView::rbAutoY3_clicked()
{
	y3_mode = 2;
	presenter->setOutputMode(OUT_Y3, y3_mode);
	initOutput(OUT_Y3, y3_mode);
}
