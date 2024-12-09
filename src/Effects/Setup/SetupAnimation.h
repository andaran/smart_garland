#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../AnimEffect.h"
#include "../../Strip/StripProcessor.h"
#include "../createEffect.h"
#include "../../Storage/Storage.h"

#include "settings.h"
#include "structs.h"

class SetupAnimation : public AnimEffect {
public:
    SetupAnimation(StripProcessor & strip, String name);
    ~SetupAnimation();

    void addLed(int i, byte r, byte g, byte b);
    void removeLed(int i);
    void addBackground(String name);
    void removeBackground();
    void save();
    void nextFrame();
    void prevFrame();
    void deleteFrame();
    String getFrame();
    
private:
    void playFrame() override;
};