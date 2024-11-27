#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <vector>

#include "../Effects/Effect.h"
#include "../Effects/PaletteEffect.h"
#include "../Strip/StripProcessor.h"
#include "settings.h"

#include "../Effects/Test/Test.h"
#include "../Effects/Rainbow/Rainbow.h"

#include "../Storage/Storage.h"

struct EfectsSettings {
    String name;
    bool slideshow;
    unsigned int timeout;
};

class EffectsProcessor {
public:
    EffectsProcessor(StripProcessor & strip);
    bool setEffect(String effect);
    void setRandomEffect();
    String getEffect();

    void saveSettings();
    void slideshowOn(unsigned timeout = 0);
    void slideshowOff();

    void begin();
    void tick();

private:
    StripProcessor & strip;
    unsigned currentEffect;
    unsigned long slideshowTimer = 0;

    EfectsSettings settings;

    // Effects
    std::vector<std::pair<String, Effect*>> effects;
};