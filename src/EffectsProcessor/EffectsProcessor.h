#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <vector>

#include "../Effects/Effect.h"
#include "../Effects/createEffect.h"
#include "../Strip/StripProcessor.h"
#include "settings.h"
#include "structs.h"

#include "../Effects/Test/Test.h"
#include "../Effects/Rainbow/Rainbow.h"
#include "../Effects/Stripes/Stripes.h"
#include "../Effects/Rain/Rain.h"

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
    unsigned long slideshowTimer = 0;

    EfectsSettings settings;
    Effect * currentEffect;

    // Effects
    std::vector<String> effects;
};