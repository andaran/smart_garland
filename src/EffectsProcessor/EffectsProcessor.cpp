#include "EffectsProcessor.h"

EffectsProcessor::EffectsProcessor(StripProcessor & strip) : strip(strip) {

    // Названия эффектов
    effects = {
        "test", "rainbow", "cyberpunk", "sunset", "optimus", "warm", "cold", 
        "hot", "pink", "comfy", "girl", "christmas", "acid", "smoke", 
        "aurora", "redwhite", "ocean"
    };

    settings = {"random", false, 30};
}

Effect * EffectsProcessor::createEffect(String name) {
    // Простые эффекты
    if (name == "test") return new EffectTest(strip);
    if (name == "rainbow") return new EffectRainbow(strip);
    // Эффекты на основе палитр (по вертикали)
    if (name == "cyberpunk") return new PaletteEffect(
        strip, 50, CYBERPUNK_PALETTE, CYBERPUNK_PALETTE_SIZE);
    if (name == "sunset") return new PaletteEffect(
        strip, 50, SUNSET_PALETTE, SUNSET_PALETTE_SIZE);
    if (name == "optimus") return new PaletteEffect(
        strip, 50, OPTIMUS_PALETTE, OPTIMUS_PALETTE_SIZE);
    if (name == "warm") return new PaletteEffect(
        strip, 50, WARM_PALETTE, WARM_PALETTE_SIZE);
    if (name == "cold") return new PaletteEffect(
        strip, 50, COLD_PALETTE, COLD_PALETTE_SIZE);
    if (name == "hot") return new PaletteEffect(
        strip, 50, HOT_PALETTE, HOT_PALETTE_SIZE);
    if (name == "pink") return new PaletteEffect(
        strip, 50, PINK_PALETTE, PINK_PALETTE_SIZE);
    if (name == "comfy") return new PaletteEffect(
        strip, 50, COMFY_PALETTE, COMFY_PALETTE_SIZE);
    if (name == "girl") return new PaletteEffect(
        strip, 50, GIRL_PALETTE, GIRL_PALETTE_SIZE);
    if (name == "christmas") return new PaletteEffect(
        strip, 50, CHRISTMAS_PALETTE, CHRISTMAS_PALETTE_SIZE);
    if (name == "acid") return new PaletteEffect(
        strip, 50, ACID_PALETTE, ACID_PALETTE_SIZE);
    if (name == "smoke") return new PaletteEffect(
        strip, 50, SMOKE_PALETTE, SMOKE_PALETTE_SIZE);
    if (name == "aurora") return new PaletteEffect(
        strip, 50, AURORA_PALETTE, AURORA_PALETTE_SIZE);
    if (name == "redwhite") return new PaletteEffect(
        strip, 50, REDWHITE_PALETTE, REDWHITE_PALETTE_SIZE);
    if (name == "ocean") return new PaletteEffect(
        strip, 50, OCEAN_PALETTE, OCEAN_PALETTE_SIZE);
    return nullptr;
}

void EffectsProcessor::begin() {
    // Загружаем настройки
    Storage::load("effects-settings", [this](JsonDocument & doc) {
        settings.name = doc["name"] | "random";
        settings.slideshow = doc["slideshow"] | false;
        settings.timeout = doc["timeout"] | 30;
    });

    setEffect(settings.name);
    if (settings.slideshow) {
        slideshowOn();
    }
}

bool EffectsProcessor::setEffect(String effectName) {
    Effect * newEffect = createEffect(effectName);
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