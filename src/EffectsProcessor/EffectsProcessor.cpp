#include "EffectsProcessor.h"

EffectsProcessor::EffectsProcessor(StripProcessor * strip) {
    this->strip = strip;
    setEffect("test");

    // Создаем все эффекты
    EffectTest * effectTest = new EffectTest(strip);

    // Добавляем все эффекты в список
    effectsList.push_back(effectTest);
}

bool EffectsProcessor::setEffect(String effect) {
    strip->clear();
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