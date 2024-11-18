#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../Effect.h"

#include "settings.h"

class EffectTest : public Effect {
public:
    EffectTest(Adafruit_NeoPixel * strip);
    
private:
    void playFrame() override;

    int shift = 0;
};