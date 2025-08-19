#include <gui/containers/PumpCont.hpp>

#include <images/BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>

#include <main_util.h>

PumpCont::PumpCont()
	: currentFrame(0), frameTickCounter(0), isAnimating(false)
{
	pumpFrames[0] = BITMAP_PUMP_ON1_ID;
	pumpFrames[1] = BITMAP_PUMP_ON2_ID;
	pumpFrames[2] = BITMAP_PUMP_ON3_ID;
	pumpFrames[3] = BITMAP_PUMP_ON4_ID;
}

void PumpCont::initialize()
{
    PumpContBase::initialize();
}

void PumpCont::setValue(uint8_t v)
{
    Unicode::snprintf(v_pumpBuffer, V_PUMP_SIZE, "%d%%", v);
    v_pump.invalidate();
}

void PumpCont::setStatus(uint8_t val, uint8_t mode, uint8_t disV)
{
	if (disV)
	{
		if (mode & OUT_MAN)
		{
			Unicode::snprintf(v_pumpBuffer, V_PUMP_SIZE, "M");
		}
		else
		{
			Unicode::snprintf(v_pumpBuffer, V_PUMP_SIZE, " ");
		}
	}
	else
	{
		if (mode & OUT_MAN)
		{
			Unicode::snprintf(v_pumpBuffer, V_PUMP_SIZE, "M%d%", val);
		}
		else
		{
			Unicode::snprintf(v_pumpBuffer, V_PUMP_SIZE, "%d%", val);
		}
	}

	if (mode & OUT_MAN)
	{
		v_pump.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	}
	else
	{
		v_pump.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	}
	v_pump.invalidate();

	if (mode & OUT_ON)
	{
		startAnim();
	}
	else
	{
		stopAnim();
	}
}


void PumpCont::startAnim()
{
    isAnimating = true;
}

void PumpCont::stopAnim()
{
    isAnimating = false;
}

void PumpCont::handleTickEvent()
{
	if (!isAnimating)
        return;

    frameTickCounter++;
    if (frameTickCounter >= FRAME_DURATION)
    {
        frameTickCounter = 0;
        currentFrame = (currentFrame + 1) % FRAME_COUNT;
        i_pump.setBitmap(touchgfx::Bitmap(pumpFrames[currentFrame]));
        i_pump.invalidate();
    }
}
