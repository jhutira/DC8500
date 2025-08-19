#include <gui/containers/ValveMCont.hpp>
#include <images/BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>

ValveMCont::ValveMCont()
{

}

void ValveMCont::initialize()
{
    ValveMContBase::initialize();
}

void ValveMCont::setStatus(uint8_t val, uint8_t run, uint8_t mode, uint8_t mixV)
{
	if (mixV)
	{
		if (mode & OUT_MAN)
		{
			Unicode::snprintf(v_valveBuffer, V_VALVE_SIZE, "M%d%", val);
		}
		else
		{
			Unicode::snprintf(v_valveBuffer, V_VALVE_SIZE, "%d%", val);
		}

		if (run)
		{
			i_valve.startAnimation(0, 0, 0);
		}
		else
		{
			i_valve.stopAnimation();
		}
	}
	else
	{
		if (mode & OUT_MAN)
		{
			Unicode::snprintf(v_valveBuffer, V_VALVE_SIZE, "M", val);
		}
		else
		{
			Unicode::snprintf(v_valveBuffer, V_VALVE_SIZE, " ", val);
		}

		if (mode & OUT_ON)
		{
			i_valve.setBitmap(touchgfx::Bitmap(BITMAP_VALVE_B_ID));
		}
		else
		{
			i_valve.setBitmap(touchgfx::Bitmap(BITMAP_VALVE_A_ID));
		}
	}

	if (mode & OUT_MAN)
	{
		v_valve.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	}
	else
	{
		v_valve.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	}

	v_valve.invalidate();
}
