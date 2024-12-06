#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../Effect.h"
#include "../../Strip/StripProcessor.h"
#include "../createEffect.h"
#include "../../Storage/Storage.h"

#include "settings.h"
#include "structs.h"

struct Animation {
    String name;
    unsigned duration;
    String background;
    std::vector<
        std::vector<
            std::array<unsigned, 4>>> frames;
};

class SetupAnimation : public Effect {
public:
    SetupAnimation(StripProcessor & strip, String name);
    ~SetupAnimation();

    void addLed(int i, byte r, byte g, byte b);
    void removeLed(int i);
    
private:
    void playFrame() override;
    void loadAnimation(String name);
    void saveAnimation();

    Animation animation;
    byte frame = 0;
};