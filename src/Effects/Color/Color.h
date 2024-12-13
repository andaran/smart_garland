#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../Effect.h"
#include "../../Strip/StripProcessor.h"

#include "settings.h"
#include "structs.h"

struct PixelState {
    byte offset;
    bool direction;
};

class EffectColor : public Effect {
public:
    EffectColor(StripProcessor & strip, Color color);
    ~EffectColor();
    
private:
    void playFrame() override;

    Color color;
    double brightnessKoef;
    byte brightness;
    PixelState pixels[NUM_LEDS];
};