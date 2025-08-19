#ifndef PUMPCONT_HPP
#define PUMPCONT_HPP

#include <gui_generated/containers/PumpContBase.hpp>

class PumpCont : public PumpContBase
{
public:
    PumpCont();
    virtual ~PumpCont() {}

    virtual void initialize();

    void setValue(uint8_t v);

    void setStatus(uint8_t val, uint8_t mode, uint8_t disV);

    void startAnim();
    void stopAnim();

    virtual void handleTickEvent();

protected:
    static const int FRAME_COUNT = 4;
    static const int FRAME_DURATION = 12; // ~200ms @60Hz tick

    //output mode
    static const uint8_t OUT_ON = 0x01;
    static const uint8_t OUT_MAN = 0x40;

private:
    touchgfx::BitmapId pumpFrames[FRAME_COUNT];
    int currentFrame;
    int frameTickCounter;

    bool isAnimating;
};

#endif // PUMPCONT_HPP
