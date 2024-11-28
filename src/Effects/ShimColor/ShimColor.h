#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../Effect.h"
#include "../../Strip/StripProcessor.h"

#include "settings.h"

class EffectShimColor : public Effect {
public:
    EffectShimColor(StripProcessor & strip, byte r, byte g, byte b);
    
private:
    byte r, g, b;

    void playFrame() override;
};