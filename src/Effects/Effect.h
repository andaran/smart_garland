#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../Strip/StripProcessor.h"
#include "settings.h"
 
class Effect {
public:
    Effect(StripProcessor * strip, unsigned long timeout);

    void tick();
    virtual void playFrame() = 0;
    
protected:
    StripProcessor * strip;
    unsigned long timeout = 0;
    unsigned long timer = 0;
};