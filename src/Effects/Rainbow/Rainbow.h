#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../Effect.h"
#include "../../Strip/StripProcessor.h"

#include "settings.h"

struct Rgb {
    int r;
    int g;
    int b;
};

class EffectRainbow : public Effect {
public:
    EffectRainbow(StripProcessor & strip);
    
private:
    void playFrame() override;

    Rgb wheel(byte wheelPos);
    uint16_t step;
};