#include "StripProcessor.h"

StripProcessor::StripProcessor(Adafruit_NeoPixel & strip, byte & streamState,
             std::function<void(char*)> callback) : strip(strip), streamState(streamState) {
    this->callback = callback;

    // Настройки ленты
    settings = {true, 255};
}

void StripProcessor::begin() {
    strip.begin();

    // Загружаем настройки
    Storage::load("strip-settings", [this](JsonDocument & doc) {
        settings.power = doc["power"] | true;
        settings.brightness = doc["brightness"] | 255;
    });

    strip.setBrightness(settings.brightness);
    clear();
    show();
}

void StripProcessor::setPixelColor(int i, byte r, byte g, byte b) {
    strip.setPixelColor(i, strip.Color(r, g, b));
}

char* StripProcessor::compressLEDs() {
    size_t len = NUM_LEDS * 3;
    char data[len]; 
    char * result = new char[BASE64_LENGTH];

    // Заполняем массив цветами пикселей
    for (int i = 0; i < NUM_LEDS; i++) {
        uint32_t color = strip.getPixelColor(i);
        data[i * 3] = (color >> 16) & 0xFF;     // R
        data[i * 3 + 1] = (color >> 8) & 0xFF;  // G
        data[i * 3 + 2] = color & 0xFF;         // B
    }

    // Кодируем массив данных в Base64
    base64_encode(result, data, len);
    return result;
}

void StripProcessor::show() {
    if (fgLayerActive) {
        for (int i = 0; i < NUM_LEDS; i++) {
            if (fgLayer[i] == nullptr) continue;
            strip.setPixelColor(i, 
                strip.Color(fgLayer[i]->r, fgLayer[i]->g, fgLayer[i]->b));
        }
    }

    strip.show();

    if (streamState) {
        callback(compressLEDs());
    }
}

void StripProcessor::setBrightness(byte brightness) {
    // Сохраняем яркость
    settings.brightness = brightness;
    Storage::save("strip-settings", [this](JsonDocument & doc) {
        doc["brightness"] = settings.brightness;
    });

    strip.setBrightness(brightness);
    strip.show();
}

byte StripProcessor::getBrightness() {
    return strip.getBrightness();
}

void StripProcessor::clear() {
    strip.clear();
    strip.show();
}

void StripProcessor::stealthClear() {
    strip.clear();
}

Adafruit_NeoPixel & StripProcessor::getStrip() {
    return strip;
}

void StripProcessor::setStripState(bool state) {
    settings.power = state;
    
    // Сохраняем состояние ленты
    Storage::save("strip-settings", [this](JsonDocument & doc) {
        doc["power"] = settings.power;
    });

    if (state) {
        strip.show();
    } else {
        clear();
    }
}

void StripProcessor::switchStripState() {
    settings.power = !settings.power;
    setStripState(settings.power);
}

bool StripProcessor::getStripState() {
    return settings.power;
}

// Foreground layer
void StripProcessor::setFgLayerState(bool state) {
    fgLayerActive = state;
}

void StripProcessor::clearFgLayer() {
    for (int i = 0; i < NUM_LEDS; i++) {
        delete fgLayer[i];
        fgLayer[i] = nullptr;
    }
}

void StripProcessor::setFgLayerColor(int i, Color * color) {
    fgLayer[i] = color;
}