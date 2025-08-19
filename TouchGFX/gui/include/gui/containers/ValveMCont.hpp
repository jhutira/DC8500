#ifndef VALVEMCONT_HPP
#define VALVEMCONT_HPP

#include <gui_generated/containers/ValveMContBase.hpp>

class ValveMCont : public ValveMContBase
{
public:
    ValveMCont();
    virtual ~ValveMCont() {}

    virtual void initialize();

    void setStatus(uint8_t val, uint8_t run,  uint8_t mode, uint8_t mixV);

protected:
    //output mode
    static const uint8_t OUT_ON = 0x01;
    static const uint8_t OUT_MAN = 0x40;
};

#endif // VALVEMCONT_HPP
