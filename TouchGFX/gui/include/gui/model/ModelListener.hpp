#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include "main_util.h"
#include "system.h"

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void updateIcons(uint8_t blink) {}
    virtual void updateClock(void) {}
    virtual void updateSensors(void) {}
    virtual void updateOutputs(void) {}
    virtual void updatePAirFlap(void) {}
    virtual void updateSAirFlap(void) {}
    virtual void updateEnergy(void) {}
    virtual void updateDebug(void) {}

    virtual void updateRegStatus(void) {}

    //virtual void updateOutput(datetime_st datetime) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
