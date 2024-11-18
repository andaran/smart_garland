#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../Effect.h"
#include "../../Strip/StripProcessor.h"

#include "settings.h"

class EffectTest : public Effect {
public:
    EffectTest(StripProcessor * strip);
    
private:
    void playFrame() override;

    int shift = 0;
};