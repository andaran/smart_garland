#include "EffectsProcessor.h"

EffectsProcessor::EffectsProcessor(Adafruit_NeoPixel * strip) {
    this->strip = strip;
    setEffect("test");

    // Создаем все эффекты
    EffectTest * effectTest = new EffectTest(strip);

    // Добавляем все эффекты в список
    effectsList.push_back(effectTest);
}

bool EffectsProcessor::setEffect(String effect) {
    clear();
    for (int i = 0; i < effects->length(); i++) {
        if (effect == effects[i]) {
            currentEffect = i;
            return true;
        }
    }
    return false;
}

void EffectsProcessor::tick() {
    effectsList[currentEffect]->tick();
}

void EffectsProcessor::clear() {
    for (int i = 0; i < NUM_LEDS; i++) {
        strip->setPixelColor(i, strip->Color(0, 0, 0));
    }
    strip->show();
}
