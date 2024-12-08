#include "EffectsProcessor.h"

EffectsProcessor::EffectsProcessor(StripProcessor & strip) : strip(strip) {

    // Названия эффектов
    effects = {
        "test", "rainbow", "cyberpunk", "sunset", "optimus", "warm", "cold", 
        "hot", "pink", "comfy", "girl", "christmas", "acid", "smoke", 
        "aurora", "redwhite", "ocean", "fog", "candy", "police", "blueberry-candy",
        "lemonade", "mint-candy", "strawberry", "rain", "snow", "acid-rain",
        "bite-a-lemon", "hell-rain"
    };

    settings = {"test", false, 30};
}

void EffectsProcessor::begin() {
    // Загружаем настройки
    Storage::load("effects-settings", [this](JsonDocument & doc) {
        settings.name = doc["name"] | "test";
        settings.slideshow = doc["slideshow"] | false;
        settings.timeout = doc["timeout"] | 30;
    });

    setEffect(settings.name);
    if (settings.slideshow) {
        slideshowOn();
    }
}

bool EffectsProcessor::setEffect(String effectName) {
    Effect * newEffect = createEffect(strip, effectName);
    if (newEffect == nullptr) return false;

    delete currentEffect;
    currentEffect = newEffect;
    settings.name = effectName;
    saveSettings();

    return true;
}

String EffectsProcessor::getEffect() {
    return settings.name;
}

void EffectsProcessor::tick() {
    if (!strip.getStripState()) return;
    currentEffect->tick();

    // Slideshow
    if (settings.slideshow && 
        millis() - slideshowTimer > settings.timeout * 1000) {
        setRandomEffect();
        slideshowTimer = millis();
    }
}

void EffectsProcessor::setRandomEffect() {
    String rndEffName = effects[random(effects.size())];
    setEffect(rndEffName);
}

void EffectsProcessor::saveSettings() {
    // Сохраняем настройки
    Storage::save("effects-settings", [this](JsonDocument & doc) {
        doc["name"] = settings.name;
        doc["slideshow"] = settings.slideshow;
        doc["timeout"] = settings.timeout;
    });
}

void EffectsProcessor::slideshowOn(unsigned timeout) {
    if (timeout != 0) {
        settings.timeout = timeout;
    }
    settings.slideshow = true;
    saveSettings();
}

void EffectsProcessor::slideshowOff() {
    settings.slideshow = false;
}

// Анимации

void EffectsProcessor::setupAnimation(String name) {
    slideshowOff();
    delete currentEffect;
    currentEffect = new SetupAnimation(strip, name);
}

Effect * EffectsProcessor::getEffectPtr() {
    return currentEffect;
}

void EffectsProcessor::endSetup() {
    setEffect(getEffect());
}