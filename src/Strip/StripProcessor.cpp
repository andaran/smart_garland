#include "StripProcessor.h"

StripProcessor::StripProcessor(Adafruit_NeoPixel * strip, 
             std::function<void(char*)> callback) {
    this->strip = strip;
    this->callback = callback;
}

void StripProcessor::setPixelColor(int i, byte r, byte g, byte b) {
    strip->setPixelColor(i, strip->Color(r, g, b));
}

char* StripProcessor::compressLEDs() {
    size_t len = NUM_LEDS * 3;
    char data[len]; 
    char * result = new char[BASE64_LENGTH];

    // Заполняем массив цветами пикселей
    for (int i = 0; i < NUM_LEDS; i++) {
        uint32_t color = strip->getPixelColor(i);
        data[i * 3] = (color >> 16) & 0xFF;     // R
        data[i * 3 + 1] = (color >> 8) & 0xFF;  // G
        data[i * 3 + 2] = color & 0xFF;         // B
    }

    // Кодируем массив данных в Base64
    base64_encode(result, data, len);
    return result;
}

void StripProcessor::show() {
    strip->show();
    callback(compressLEDs());
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

Adafruit_NeoPixel * StripProcessor::getStrip() {
    return strip;
}