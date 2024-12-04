#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../Effect.h"
#include "../../Strip/StripProcessor.h"
#include "../createEffect.h"

#include "settings.h"
#include "structs.h"

struct Drop {
    byte turn;
    unsigned turnPos;
};

class EffectRain : public Effect {
public:
    EffectRain(StripProcessor & strip, Color color);
    ~EffectRain();
    
private:
    void playFrame() override;

    std::vector<Drop *> drops;
    Color color;
};