#include <gui/mainscreen_screen/mainScreenView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <stdio.h>

#include <gui/common/DefnGui.hpp>
#include <touchgfx/Color.hpp>

#include "system.h"
#include <images/BitmapDatabase.hpp>

#include <videos/VideoDatabase.hpp>

#include "variant.h"
#include "debug.h"

//extern "C" {
//	extern void LED_G_Toggle(void);
//}


mainScreenView::mainScreenView()
{

}

void mainScreenView::setupScreen()
{
	mainScreenViewBase::setupScreen();
    presenter->updateClock();

    if (initOK == 0)
    {
    	initOK = 1;
    	Texts::setLanguage(lang_id);
    }

    drawScheme(regSch);

    p_senO2.setBitmap(touchgfx::Bitmap(BITMAP_SENO2_LABEL_ID));
    p_flow.setBitmap(touchgfx::Bitmap(BITMAP_SENFLOW_LABEL_ID));
    showIcons(0, 0);
}

void mainScreenView::tearDownScreen()
{
    mainScreenViewBase::tearDownScreen();
}

void mainScreenView::handleTickEvent()
{
	p_pump1.handleTickEvent();  // ✅ manuálne volanie animácie
	p_pump2.handleTickEvent();  // ✅ manuálne volanie animácie
	p_pump3.handleTickEvent();  // ✅ manuálne volanie animácie

}

/******************************************************************************
** Show icon
******************************************************************************/
void mainScreenView::showIcons(uint8_t manIcon, uint8_t errIcon )
{
	i_man.setVisible(manIcon);
	i_man.invalidate();
	i_err.setVisible(errIcon);
	i_err.invalidate();
}

/******************************************************************************
** Sound Button set state
******************************************************************************/
void mainScreenView::soundBtn_setState(bool press)
{
	soundBtn.forceState(press);
}

/******************************************************************************
** Door Button set label
******************************************************************************/
void mainScreenView::doorBtn_setLabelDoor(bool doorL)
{
	if (doorL)
	{
		doorBtn.setLabelText(touchgfx::TypedText(T_S_BTN_DOOR));
		doorBtn.setBitmaps(touchgfx::Bitmap(BITMAP_DOOR_BTN_ID), touchgfx::Bitmap(BITMAP_DOOR_BTN_PRESSED_ID));
	}
	else
	{
		doorBtn.setLabelText(touchgfx::TypedText(T_S_BTN_START));
		doorBtn.setBitmaps(touchgfx::Bitmap(BITMAP_START_BTN_ID), touchgfx::Bitmap(BITMAP_START_BTN_PRESSED_ID));
	}
}


/******************************************************************************
** updateClock
******************************************************************************/
void mainScreenView::updateTimeTA(uint8_t h, uint8_t m, uint8_t wd)
{
	Unicode::UnicodeChar buf[3];

	Unicode::strncpy(buf, &TAB_WEEKDAY_S[0][wd-1][0], 3);

	touchgfx::Unicode::snprintf(t_timeClockBuffer,T_TIMECLOCK_SIZE,"%d:%.2d %s", h, m, buf);
	t_timeClock.setWildcard(t_timeClockBuffer);
	t_timeClock.invalidate();
}

void mainScreenView::updateDateTA(uint8_t d, uint8_t m, uint8_t y)
{
	touchgfx::Unicode::snprintf(t_dateClockBuffer,T_DATECLOCK_SIZE,"%d.%d.%d", d, m, 2000 + y);
	t_dateClock.setWildcard(t_dateClockBuffer);
	t_dateClock.invalidate();
}


/******************************************************************************
** print_atemp
******************************************************************************/
void mainScreenView::print_atemp(int16_t t, uint8_t status, touchgfx::Unicode::UnicodeChar *buf, uint16_t bufSize)
{
	if (status & SEN_SH)
	{
		touchgfx::Unicode::snprintf(buf, bufSize,"xxx%s", uDegCel);
		return;
	}
	if (status & SEN_OP)
	{
		touchgfx::Unicode::snprintf(buf, bufSize,"---%s", uDegCel);
		return;
	}
	if ((status & SEN_OK)== 0)
	{
		touchgfx::Unicode::snprintf(buf, bufSize,"???%s", uDegCel);
		return;
	}
	touchgfx::Unicode::snprintf(buf, bufSize, "%d.%d%s", t / 10, abs(t % 10), uDegCel);
}

/******************************************************************************
** print_atemp_short
******************************************************************************/
void mainScreenView::print_atemp_short(int16_t t, uint8_t status, touchgfx::Unicode::UnicodeChar *buf, uint16_t bufSize)
{
	if (status & SEN_SH)
	{
		touchgfx::Unicode::snprintf(buf, bufSize,"xxx%s", uDegCel);
		return;
	}
	if (status & SEN_SH)
	{
		touchgfx::Unicode::snprintf(buf, bufSize,"---%s", uDegCel);
		return;
	}
	if ((status & SEN_OK) == 0)
	{
		touchgfx::Unicode::snprintf(buf, bufSize,"???%s", uDegCel);
		return;
	}
	touchgfx::Unicode::snprintf(buf, bufSize, "%d%s", t / 10, uDegCel);
}

/******************************************************************************
** updateSensors
******************************************************************************/
void mainScreenView::updateTS1(int16_t t, uint8_t status)
{
	p_sen1.updateTempValue(t, status);
}

void mainScreenView::updateTS2(int16_t t, uint8_t status)
{
	p_sen2.updateTempValue(t, status);
}

void mainScreenView::updateTS3(int16_t t, uint8_t status)
{
	p_sen3.updateTempValue(t, status);
}

void mainScreenView::updateTS4(int16_t t, uint8_t status)
{
	p_sen4.updateTempValue(t, status);
}

void mainScreenView::updateTS5(int16_t t, uint8_t status)
{
	p_sen5.updateTempValue(t, status);
}

void mainScreenView::updateTS6(int16_t t, uint8_t status)
{
	p_sen6.updateTempValue(t, status);
}

void mainScreenView::updateTS7(int16_t t, uint8_t status)
{
	p_sen7.updateTempValue(t, status);
}

void mainScreenView::updateTS8(int16_t t, uint8_t status)
{
	p_sen8.updateTempValue(t, status);
}

void mainScreenView::updateTS9(int16_t t, uint8_t status)
{
	p_sen9.updateTempValue(t, status);
}

void mainScreenView::updateLS(int16_t v, uint8_t status)
{
	p_senO2.updateO2Value(v, status);
	p_senO2.setVisible(status & sLS_ST_HEAT);
	p_senO2.invalidate();
}

void mainScreenView::updateFlowMeter(uint16_t flow, uint8_t vis)
{
	p_flow.updateFlowValue(flow);
	p_flow.setVisible(vis);
	p_flow.invalidate();
}

void mainScreenView::updateAccLevel(uint8_t v)
{
	touchgfx::Unicode::snprintf(&t_accLevelBuffer[0], T_ACCLEVEL_SIZE,"%u", v);
	t_accLevel.setWildcard(t_accLevelBuffer);
	t_accLevel.invalidate();
}

void mainScreenView::updateEnergy(float accEng, float aPwr)
{
	uint32_t val32 = accEng * 100;

	touchgfx::Unicode::snprintf(&t_accEngBuffer[0], T_ACCENG_SIZE, "%d.%.2dkWh", val32 / 100, abs(val32 % 100));
	t_accEng.setWildcard(t_accEngBuffer);
	t_accEng.invalidate();

	val32 = aPwr * 100;
	touchgfx::Unicode::snprintf(&t_apowerBuffer[0], T_APOWER_SIZE, "%d.%.2dkW", val32 / 100, abs(val32 % 100));
	t_apower.setWildcard(t_apowerBuffer);
	t_apower.invalidate();

}
/******************************************************************************
** updateOutputs
******************************************************************************/
void mainScreenView::updateOutput(uint8_t n, uint8_t value, uint8_t mode)
{
	if (n == 0)
	{
		p_pump1.setStatus(value, mode, 0);
	}

	if (n == 1)
	{
		if (TAB_OBJ_OUT[regSch][1].oType == OT_PUMP)
		{
			p_pump2.setStatus(value, mode, 1);
		}
		if (TAB_OBJ_OUT[regSch][1].oType == OT_VALVE_AB)
		{
			p_valve1.setStatus(value, 1, mode, 1);
		}
	}

	if (n == 4)
	{
		if (TAB_OBJ_OUT[regSch][4].oType == OT_PUMP)
		{
			p_pump3.setStatus(value, mode, 1);
		}
	}
}


/******************************************************************************
** updateAirFlaps
******************************************************************************/
void mainScreenView::updatePAirFlap(uint8_t pos, uint8_t m)
{
	touchgfx::Unicode::UnicodeChar unit[] = {'%', 0};

	if (m == 1)
	{
		t_pflap.setColor(touchgfx::Color::getColorFromRGB(0, 0, 255));
		unit[0] = 'M';
	}
	else
	{
		t_pflap.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	}
	touchgfx::Unicode::snprintf(&t_pflapBuffer[0], T_PFLAP_SIZE,"%u%s", pos, unit);
	t_pflap.setWildcard(t_pflapBuffer);
	t_pflap.invalidate();
}

void mainScreenView::updateSAirFlap(uint8_t pos, uint8_t m)
{
	touchgfx::Unicode::UnicodeChar unit[] = {'%', 0};

	if (m == 1)
	{
		t_sflap.setColor(touchgfx::Color::getColorFromRGB(0, 0, 255));
		unit[0] = 'M';
	}
	else
	{
		t_sflap.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	}
	touchgfx::Unicode::snprintf(&t_sflapBuffer[0], T_SFLAP_SIZE,"%u%s", airflap[SEC_F].pos, unit);
	t_sflap.setWildcard(t_sflapBuffer);
	t_sflap.invalidate();
}

/******************************************************************************
** updateInfMsg
******************************************************************************/
void mainScreenView::updateInfoMsg(TEXTS id_msg)
{
	t_info.setTypedText(TypedText(id_msg));
	t_info.invalidate();
}

/******************************************************************************
** updateProfileSld
******************************************************************************/
void mainScreenView::updateProfileSld(uint16_t minV, uint16_t maxV, uint16_t pos)
{
    profileSld.setValueRange(minV, maxV, pos);
}

/******************************************************************************
** updateDebug
******************************************************************************/
void mainScreenView::updateDebug(void)
{
	t_debug.setVisible(false);
	touchgfx::Unicode::snprintf(t_debugBuffer, T_DEBUG_SIZE,"%u", debug32);
	t_debug.setWildcard(t_debugBuffer);
	t_debug.invalidate();


}

/******************************************************************************
** Door Button clicked
******************************************************************************/
void mainScreenView::doorBtn_clicked()
{
	presenter->doorBtnAction();

}

/******************************************************************************
** Sound Button clicked
******************************************************************************/
void mainScreenView::soundBtn_clicked()
{
	if (soundBtn.getState())
	{
		presenter->soundBtnAction(1);
	}
	else
	{
		presenter->soundBtnAction(0);
	}
}

/******************************************************************************
** Slider change value
******************************************************************************/
void mainScreenView::profileSldChangeVal(int value)
{
	touchgfx::Unicode::snprintf(t_rTFBuffer, T_RTF_SIZE,"%u", value);
	t_rTF.setWildcard(t_rTFBuffer);
	t_rTF.invalidate();
}

/******************************************************************************
** Slider new value confirm
******************************************************************************/
void mainScreenView::profileSldChangeConf(int value)
{
	touchgfx::Unicode::snprintf(t_rTFBuffer, T_RTF_SIZE,"%u", value);
	t_rTF.setWildcard(t_rTFBuffer);
	t_rTF.invalidate();
	presenter->setBPrqFlueTemp(10 * value);
}

/******************************************************************************
** Draw scheme
******************************************************************************/
void mainScreenView::drawScheme(uint8_t sch)
{
	i_sch.setBitmap(touchgfx::Bitmap(imgSchemes[sch]));
	i_sch.invalidate();

	/* Inputs */
	p_sen1.moveTo(TAB_OBJ_IN[sch][0].x, TAB_OBJ_IN[sch][0].y);
	p_sen1.setVisible(TAB_OBJ_IN[sch][0].v);
	p_sen1.invalidate();

	p_sen2.moveTo(TAB_OBJ_IN[sch][1].x, TAB_OBJ_IN[sch][1].y);
	p_sen2.setVisible(TAB_OBJ_IN[sch][1].v);
	p_sen2.invalidate();

	p_sen3.moveTo(TAB_OBJ_IN[sch][2].x, TAB_OBJ_IN[sch][2].y);
	p_sen3.setVisible(TAB_OBJ_IN[sch][2].v);
	p_sen3.invalidate();

	p_sen4.moveTo(TAB_OBJ_IN[sch][3].x, TAB_OBJ_IN[sch][3].y);
	p_sen4.setVisible(TAB_OBJ_IN[sch][3].v);
	p_sen4.invalidate();

	p_sen5.moveTo(TAB_OBJ_IN[sch][4].x, TAB_OBJ_IN[sch][4].y);
	p_sen5.setVisible(TAB_OBJ_IN[sch][4].v);
	p_sen5.invalidate();

	p_sen6.moveTo(TAB_OBJ_IN[sch][5].x, TAB_OBJ_IN[sch][5].y);
	p_sen6.setVisible(TAB_OBJ_IN[sch][5].v);
	p_sen6.invalidate();

	p_sen7.moveTo(TAB_OBJ_IN[sch][6].x, TAB_OBJ_IN[sch][6].y);
	p_sen7.setVisible(TAB_OBJ_IN[sch][6].v);
	p_sen7.invalidate();

	p_sen8.moveTo(TAB_OBJ_IN[sch][7].x, TAB_OBJ_IN[sch][7].y);
	p_sen8.setVisible(TAB_OBJ_IN[sch][7].v);
	p_sen8.invalidate();

	p_sen9.moveTo(TAB_OBJ_IN[sch][8].x, TAB_OBJ_IN[sch][8].y);
	p_sen9.setVisible(TAB_OBJ_IN[sch][8].v);
	p_sen9.invalidate();

	p_flow.moveTo(TAB_OBJ_IN[sch][2].x, TAB_OBJ_IN[sch][2].y+30);
	p_flow.setVisible(1);
	p_flow.invalidate();

	/* Acc level */
	t_accLevel.moveTo(TAB_OBJ_IN[sch][1].x, TAB_OBJ_IN[sch][1].y - 50);		// SA
	t_accLevel.invalidate();

	/* Outputs */
	p_pump2.setVisible(0);
	p_pump2.invalidate();
	p_pump3.setVisible(0);
	p_pump3.invalidate();
	p_valve1.setVisible(0);
	p_valve1.invalidate();

	p_pump1.moveTo(TAB_OBJ_OUT[sch][0].x, TAB_OBJ_OUT[sch][0].y);
	p_pump1.setVisible(TAB_OBJ_OUT[sch][0].v);
	p_pump1.invalidate();

	if (TAB_OBJ_OUT[sch][1].oType == OT_PUMP)
	{
		p_pump2.moveTo(TAB_OBJ_OUT[sch][1].x, TAB_OBJ_OUT[sch][1].y);
		p_pump2.setVisible(TAB_OBJ_OUT[sch][1].v);
		p_pump2.invalidate();
	}

	if (TAB_OBJ_OUT[sch][1].oType == OT_VALVE_AB)
	{
		p_valve1.moveTo(TAB_OBJ_OUT[sch][1].x, TAB_OBJ_OUT[sch][1].y);
		p_valve1.setVisible(TAB_OBJ_OUT[sch][1].v);
		p_valve1.invalidate();
	}

	if (TAB_OBJ_OUT[sch][2].oType == OT_VALVE_MIX)
	{
		p_valve1.moveTo(TAB_OBJ_OUT[sch][2].x, TAB_OBJ_OUT[sch][2].y);
		p_valve1.setVisible(TAB_OBJ_OUT[sch][2].v);
		p_valve1.invalidate();
	}

	if (TAB_OBJ_OUT[sch][4].oType == OT_PUMP)
	{
		p_pump3.moveTo(TAB_OBJ_OUT[sch][4].x, TAB_OBJ_OUT[sch][4].y);
		p_pump3.setVisible(TAB_OBJ_OUT[sch][4].v);
		p_pump3.invalidate();
	}

	/* Door/START Button */
	presenter->doorBtnInit();
}
