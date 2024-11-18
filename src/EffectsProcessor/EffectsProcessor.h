#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <vector>

#include "../Effects/Effect.h"
#include "../Effects/Test/Test.h"

#include "settings.h"

class EffectsProcessor {
public:
    EffectsProcessor(Adafruit_NeoPixel * strip);
    bool setEffect(String effect);
    void tick();

private:
    Adafruit_NeoPixel * strip;
    String const effects[1] = {
        "test",
    };
    unsigned currentEffect;

    // Effects
    std::vector<Effect *> effectsList;

    void clear();

    // Effects

    void test();
};