#pragma once

#include "settings.h"
#include "structs.h"
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
    void stealthClear();
    Adafruit_NeoPixel & getStrip();
    void begin();
    void setStripState(bool state);
    void switchStripState();
    bool getStripState();

    // Foreground layer
    void setFgLayerState(bool state);
    void clearFgLayer();
    void setFgLayerColor(int i, Color * color);

private:
    Color * fgLayer[NUM_LEDS];
    bool fgLayerActive = false;
    Adafruit_NeoPixel & strip;
    byte & streamState;
    StripSettings settings;
    std::function<void(char*)> callback;
    char* compressLEDs();
};