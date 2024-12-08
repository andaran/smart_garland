#include "AnimEffect.h"

AnimEffect::AnimEffect(StripProcessor & strip, String name) 
    : Effect(strip, 50) {

    strip.clear();
    strip.show();

    this->name = name;

    if (Storage::exists(("anim-" + name).c_str())) {
        loadAnimation();
    } else {
        animation.duration = 200;
        animation.background = "";
        animation.frames = 1;
        saveAnimation();
    }

    for (int i = 0; i < (NUM_LEDS + 7) / 8; i++) {
        ledStates[i] = 0;
    }
    for (int i = 0; i < NUM_LEDS * 3; i++) {
        ledColors[i] = 0;
    }

    strip.setFgLayerState(true);
    strip.clearFgLayer();
}

AnimEffect::~AnimEffect() {
    strip.clearFgLayer();
    strip.setFgLayerState(false);
}

void AnimEffect::saveAnimation() {
    Storage::save(("anim-" + name).c_str(), [this](JsonDocument & doc) {
        doc["background"] = animation.background;
        doc["duration"] = animation.duration;
        doc["frames"] = animation.frames;
    });
}

void AnimEffect::loadAnimation() {
    Storage::load(("anim-" + name).c_str(), [this](JsonDocument & doc) {
        animation.background = doc["background"] | "";
        animation.duration = doc["duration"] | 200;
        animation.frames = doc["frames"] | 1;
    });
}

void AnimEffect::setLed(unsigned index, bool isOn, 
                        uint8_t r, uint8_t g, uint8_t b) {
    int byteIndex = index / 8;
    int bitIndex = index % 8;

    if (isOn) {
        ledStates[byteIndex] |= (1 << bitIndex); // Установить бит в 1
        ledColors[index * 3] = r;
        ledColors[index * 3 + 1] = g;
        ledColors[index * 3 + 2] = b;
    } else {
        ledStates[byteIndex] &= ~(1 << bitIndex); // Сбросить бит в 0
    }
}

bool AnimEffect::getLedState(unsigned index) {
    int byteIndex = index / 8;
    int bitIndex = index % 8;
    return (ledStates[byteIndex] & (1 << bitIndex)) != 0;
}

void AnimEffect::getLedColor(unsigned index, uint8_t & r, uint8_t & g, uint8_t & b) {
    r = ledColors[index * 3];
    g = ledColors[index * 3 + 1];
    b = ledColors[index * 3 + 2];
}

void AnimEffect::saveFrame() {
    File file = LittleFS.open(("anim-" + name + "-" + String(frame)).c_str(), "w");

    // Сохраняем состояния
    file.write(ledStates, (NUM_LEDS + 7) / 8);

    // Сохраняем цвета для включённых светодиодов
    for (int i = 0; i < NUM_LEDS; i++) {
        if (getLedState(i)) {
            file.write(ledColors[i * 3]);     // R
            file.write(ledColors[i * 3 + 1]); // G
            file.write(ledColors[i * 3 + 2]); // B
        }
    }

    file.close();
}

void AnimEffect::loadFrame() {
    String frameName = "anim-" + name + "-" + String(frame);

    // Если кадр отсутствует, создаём его
    if (!LittleFS.exists(frameName)) {
        saveFrame();
        return;
    }

    File file = LittleFS.open(frameName, "r");

    // Загружаем состояния
    file.read(ledStates, (NUM_LEDS + 7) / 8);

    // Загружаем цвета для включённых светодиодов
    for (int i = 0; i < NUM_LEDS; i++) {
        if (getLedState(i)) {
            ledColors[i * 3] = file.read();     // R
            ledColors[i * 3 + 1] = file.read(); // G
            ledColors[i * 3 + 2] = file.read(); // B
        }
    }

    file.close();
}