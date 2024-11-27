#include "EffectsProcessor.h"

EffectsProcessor::EffectsProcessor(StripProcessor & strip) : strip(strip) {

    // Добавляем эффекты
    effects = {
        // Простые эффекты
        {"test", new EffectTest(strip)},
        {"rainbow", new EffectRainbow(strip)},

        // Эффекты на основе палитр
        {"fire", new PaletteEffect(strip, 50, FIRE_PALETTE, FIRE_PALETTE_SIZE)}
    };

    setEffect("test");
}

bool EffectsProcessor::setEffect(String effect) {
    strip.clear();
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
    if (!strip.getStripState()) return;
    effects[currentEffect].second->tick();
}