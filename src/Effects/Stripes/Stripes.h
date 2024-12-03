#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../Effect.h"
#include "../../Strip/StripProcessor.h"

#include "settings.h"
#include "structs.h"


class EffectStripes : public Effect {
public:
    EffectStripes(StripProcessor & strip, Color color1, Color color2);
    
private:
    void playFrame() override;

    Color color1;
    Color color2;
    int iter = 0;
    std::vector<int> steps;
};