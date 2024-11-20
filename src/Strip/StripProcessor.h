#pragma once

#include "settings.h"
#include <Adafruit_NeoPixel.h>
#include <string>

class StripProcessor {
public:
    StripProcessor(Adafruit_NeoPixel * strip, 
          std::function<void(std::string)> callback);
    void setPixelColor(int i, byte r, byte g, byte b);
    void show();
    void setBrightness(byte brightness);
    void clear();
private:
    Adafruit_NeoPixel * strip;
    std::function<void(std::string)> callback;
};