#pragma once

#include "settings.h"
#include <Adafruit_NeoPixel.h>
#include <string>
#include <Base64.h>

class StripProcessor {
public:
    StripProcessor(Adafruit_NeoPixel * strip, 
          std::function<void(char*)> callback);
    void setPixelColor(int i, byte r, byte g, byte b);
    void show();
    void setBrightness(byte brightness);
    void clear();
    Adafruit_NeoPixel * getStrip();
private:
    Adafruit_NeoPixel * strip;
    std::function<void(char*)> callback;
    char* compressLEDs();
};