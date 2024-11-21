#include "EffectsProcessor.h"

EffectsProcessor::EffectsProcessor(StripProcessor * strip) {
    this->strip = strip;
    setEffect("test");

    // Создаем все эффекты
    EffectTest * effectTest = new EffectTest(strip);
    EffectRainbow * effectRainbow = new EffectRainbow(strip);

    // Добавляем все эффекты в список
    effectsList.push_back(effectTest);
    effectsList.push_back(effectRainbow);
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

String EffectsProcessor::getEffect() {
    return effects[currentEffect];
}

void EffectsProcessor::tick() {
    if (!strip->getStripState()) return;
    effectsList[currentEffect]->tick();
}