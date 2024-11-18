#include "Strip.h"

Strip::Strip(Adafruit_NeoPixel * strip, 
             std::function<void(std::string&)> callback) {
    this->strip = strip;
    this->callback = callback;
}

void Strip::setPixelColor(int i, byte r, byte g, byte b) {
    strip->setPixelColor(i, strip->Color(r, g, b));
}

void Strip::show() {
    strip->show();
    std::string message = "show";
    callback(message);
}

void Strip::setBrightness(byte brightness) {
    strip->setBrightness(brightness);
}

void Strip::clear() {
    for (int i = 0; i < NUM_LEDS; i++) {
        strip->setPixelColor(i, strip->Color(0, 0, 0));
    }
    strip->show();
}