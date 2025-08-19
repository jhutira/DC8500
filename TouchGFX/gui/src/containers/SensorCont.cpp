#include <gui/containers/SensorCont.hpp>
#include <gui/common/DefnGui.hpp>
#include <touchgfx/Color.hpp>

SensorCont::SensorCont()
{

}

void SensorCont::initialize()
{
    SensorContBase::initialize();
}



void SensorCont::updateTempValue(int16_t t, uint8_t status)
{
	if (status & SEN_OK)
	{
		t_value.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	}
	else
	{
		t_value.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	}

	if (status & SEN_SH)
	{
		touchgfx::Unicode::snprintf(t_valueBuffer, T_VALUE_SIZE,"xxx%s", uDegCel);
	}
	else
	if (status & SEN_OP)
	{
		touchgfx::Unicode::snprintf(t_valueBuffer, T_VALUE_SIZE,"---%s", uDegCel);
	}
	else
	if ((status & SEN_OK)== 0)
	{
		touchgfx::Unicode::snprintf(t_valueBuffer, T_VALUE_SIZE,"???%s", uDegCel);
	}
	else
	{
		touchgfx::Unicode::snprintf(t_valueBuffer, T_VALUE_SIZE, "%d.%d%s", t / 10, abs(t % 10), uDegCel);
	}
	t_value.setWildcard(t_valueBuffer);
	t_value.invalidate();
}

void SensorCont::updateO2Value(int16_t v, uint8_t status)
{
	if (status & SEN_OK)
	{
		t_value.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	}
	else
	{
		t_value.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	}

	if (status & SEN_SH)
	{
		touchgfx::Unicode::snprintf(t_valueBuffer, T_VALUE_SIZE,"xxx%");
	}
	else
	if (status & SEN_OP)
	{
		touchgfx::Unicode::snprintf(t_valueBuffer, T_VALUE_SIZE,"---%");
	}
	else
	if ((status & SEN_OK)== 0)
	{
		touchgfx::Unicode::snprintf(t_valueBuffer, T_VALUE_SIZE,"???%");
	}
	else
	{
		touchgfx::Unicode::snprintf(t_valueBuffer, T_VALUE_SIZE, "%d.%d%", v / 10, abs(v % 10));
	}
	t_value.setWildcard(t_valueBuffer);
	t_value.invalidate();

}

void SensorCont::updateFlowValue(uint16_t v)
{
	t_value.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

	touchgfx::Unicode::snprintf(t_valueBuffer, T_VALUE_SIZE, "%d.%dl/m", v / 10, abs(v % 10));

	t_value.setWildcard(t_valueBuffer);
	t_value.invalidate();

}

void SensorCont::setBitmap(const Bitmap& bmp)
{
	i_panel.setBitmap(bmp);
}


