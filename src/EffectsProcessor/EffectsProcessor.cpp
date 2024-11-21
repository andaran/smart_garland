#include "EffectsProcessor.h"

EffectsProcessor::EffectsProcessor(StripProcessor * strip) {
    this->strip = strip;

    // Добавляем эффекты
    effects = {
        {"test", new EffectTest(strip)},
        {"rainbow", new EffectRainbow(strip)}
    };

    setEffect("test");
}

bool EffectsProcessor::setEffect(String effect) {
    strip->clear();
    for (int i = 0; i < effects.size(); i++) {
        if (effect == effects[i].first) {
            currentEffect = i;
            return true;
        }
    }
    return false;
}

String EffectsProcessor::getEffect() {
    return effects[currentEffect].first;
}

void EffectsProcessor::tick() {
    if (!strip->getStripState()) return;
    effects[currentEffect].second->tick();
}