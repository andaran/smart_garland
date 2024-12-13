#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <vector>

#include "../Effects/Effect.h"
#include "../Effects/createEffect.h"
#include "../Strip/StripProcessor.h"
#include "settings.h"
#include "structs.h"

#include "../Effects/Setup/SetupAnimation.h"
#include "../Effects/Setup/SetupModel.h"

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
    Effect * getEffectPtr();

    void saveSettings();
    void slideshowOn(unsigned timeout = 0);
    void slideshowOff();

    void begin();
    void tick();

    void setupAnimation(String name);
    void setupModel();
    void endSetup();

private:
    StripProcessor & strip;
    unsigned long slideshowTimer = 0;

    EfectsSettings settings;
    Effect * currentEffect;

    // Effects
    std::vector<String> effects;
};