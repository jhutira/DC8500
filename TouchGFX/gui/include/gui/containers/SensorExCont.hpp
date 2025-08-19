#ifndef SENSOREXCONT_HPP
#define SENSOREXCONT_HPP

#include <gui_generated/containers/SensorExContBase.hpp>

class SensorExCont : public SensorExContBase
{
public:
    SensorExCont();
    virtual ~SensorExCont() {}

    virtual void initialize();

    void updateTempValue(int16_t t, uint8_t status);

protected:
    const uint8_t SEN_OK = 0x01;
    const uint8_t SEN_SH = 0x02;
    const uint8_t SEN_OP = 0x04;
};

#endif // SENSOREXCONT_HPP
