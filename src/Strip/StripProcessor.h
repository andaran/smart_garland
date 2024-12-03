#pragma once

#include "settings.h"
#include <Adafruit_NeoPixel.h>
#include <string>
#include <Base64.h>
#include "../Storage/Storage.h"

struct StripSettings {
    bool power;
    byte brightness;
};

class StripProcessor {
public:
    StripProcessor(Adafruit_NeoPixel & strip, byte & streamState,
          std::function<void(char*)> callback);
    void setPixelColor(int i, byte r, byte g, byte b);
    void show();
    void setBrightness(byte brightness);
    byte getBrightness();
    void clear();
    Adafruit_NeoPixel & getStrip();
    void begin();
    void setStripState(bool state);
    void switchStripState();
    bool getStripState();

    // Для плавного перехода цветов
    void initSmoothColorChange(float * stepsR, float * stepsG, float * stepsB);
    void stepSmoothColorChange();
private:
    Adafruit_NeoPixel & strip;
    byte & streamState;
    StripSettings settings;
    std::function<void(char*)> callback;
    char* compressLEDs();

    // Для плавного перехода цветов
    float curR[NUM_LEDS];
    float curG[NUM_LEDS];
    float curB[NUM_LEDS];
    float * stepsR;
    float * stepsG;
    float * stepsB;
};