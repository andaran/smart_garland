#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../Strip/StripProcessor.h"
#include "../Storage/Storage.h"
#include "settings.h"
 
class Effect {
public:
    Effect(StripProcessor & strip, unsigned long timeout);
    virtual ~Effect() = default;

    void tick();
    virtual void playFrame() = 0;
    
protected:
    StripProcessor & strip;
    unsigned long timeout = 0;
    unsigned long timer = 0;
    std::vector<int> turns;

    byte getTurnNumber(int index);
    int getAbsoluteIndex(byte turn, int index);
};