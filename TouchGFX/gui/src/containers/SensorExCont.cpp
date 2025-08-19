#include <gui/containers/SensorExCont.hpp>
#include <gui/common/DefnGui.hpp>
#include <touchgfx/Color.hpp>

SensorExCont::SensorExCont()
{

}

void SensorExCont::initialize()
{
    SensorExContBase::initialize();
}

void SensorExCont::updateTempValue(int16_t t, uint8_t status)
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
