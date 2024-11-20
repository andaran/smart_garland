#include "StripProcessor.h"

StripProcessor::StripProcessor(Adafruit_NeoPixel * strip, 
             std::function<void(std::string&)> callback) {
    this->strip = strip;
    this->callback = callback;
}

void StripProcessor::setPixelColor(int i, byte r, byte g, byte b) {
    strip->setPixelColor(i, strip->Color(r, g, b));
}

void StripProcessor::show() {
    strip->show();
    std::string message = "";
    for (int i = 0; i < NUM_LEDS; i++) {
        uint32_t color = strip->getPixelColor(i);
        byte r = (color >> 16) & 0xFF;
        byte g = (color >> 8) & 0xFF;
        byte b = color & 0xFF;
        message += std::to_string(r) + "-" + std::to_string(g) + "-" + std::to_string(b) + "/";
    }
    message.pop_back();
    callback(message);
}

void StripProcessor::setBrightness(byte brightness) {
    strip->setBrightness(brightness);
}

void StripProcessor::clear() {
    for (int i = 0; i < NUM_LEDS; i++) {
        strip->setPixelColor(i, strip->Color(0, 0, 0));
    }
    strip->show();
}