#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <vector>

#include "../Effects/Effect.h"
#include "../Strip/StripProcessor.h"
#include "settings.h"

#include "../Effects/Test/Test.h"
#include "../Effects/Rainbow/Rainbow.h"

class EffectsProcessor {
public:
    EffectsProcessor(StripProcessor * strip);
    bool setEffect(String effect);
    String getEffect();
    void tick();

private:
    StripProcessor * strip;
    String const effects[2] = {
        "test",
        "rainbow"
    };
    unsigned currentEffect;

    // Effects
    std::vector<Effect *> effectsList;
};