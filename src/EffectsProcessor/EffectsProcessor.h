#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <vector>

#include "../Effects/Effect.h"
#include "../Effects/Test/Test.h"
#include "../Strip/StripProcessor.h"

#include "settings.h"

class EffectsProcessor {
public:
    EffectsProcessor(StripProcessor * strip);
    bool setEffect(String effect);
    String getEffect();
    void tick();

private:
    StripProcessor * strip;
    String const effects[1] = {
        "test",
    };
    unsigned currentEffect;

    // Effects
    std::vector<Effect *> effectsList;
};