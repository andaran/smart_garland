#pragma once

#include "Effect.h"
#include <LittleFS.h>

struct Animation {
    String background;
    unsigned duration = 200;
    unsigned frames = 1;
};

class AnimEffect : public Effect {
public:
    AnimEffect(StripProcessor & strip, String name);
    ~AnimEffect();

protected:
    String name;
    Animation animation;
    unsigned frame = 0;

    uint8_t ledColors[NUM_LEDS * 3];
    uint8_t ledStates[(NUM_LEDS + 7) / 8];

    void saveAnimation();
    void loadAnimation();
    void setLed(unsigned index, bool isOn, 
                uint8_t r = 0, uint8_t g = 0, uint8_t b = 0);
    bool getLedState(unsigned index);
    void getLedColor(unsigned index, uint8_t & r, uint8_t & g, uint8_t & b);
    void saveFrame();
    void loadFrame();
};