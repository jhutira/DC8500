#ifndef SENSORCONT_HPP
#define SENSORCONT_HPP

#include <gui_generated/containers/SensorContBase.hpp>

class SensorCont : public SensorContBase
{
public:
    SensorCont();
    virtual ~SensorCont() {}

    virtual void initialize();

    void updateTempValue(int16_t t, uint8_t status);
    void updateO2Value(int16_t v, uint8_t status);
    void updateFlowValue(uint16_t v);
    void setBitmap(const Bitmap& bmp);

protected:

    const uint8_t SEN_OK = 0x01;
    const uint8_t SEN_SH = 0x02;
    const uint8_t SEN_OP = 0x04;
    const uint8_t LSEN_HEAT = 0x80;

};

#endif // SENSORCONT_HPP
