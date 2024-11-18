#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "settings.h"
 
class Effect {
public:
    Effect(Adafruit_NeoPixel * strip, unsigned long timeout);

    void tick();
    virtual void playFrame() = 0;
    
protected:
    Adafruit_NeoPixel * strip;
    unsigned long timeout = 0;
    unsigned long timer = 0;

    void clear();
};