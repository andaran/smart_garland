#include "EffectsProcessor.h"

EffectsProcessor::EffectsProcessor(StripProcessor & strip) : strip(strip) {

    // Добавляем эффекты
    effects = {
        // Простые эффекты
        {"test", new EffectTest(strip)},
        {"rainbow", new EffectRainbow(strip)},
        {"shim-gold", new EffectShimColor(strip, 255, 215, 0)},
        {"shim-blue", new EffectShimColor(strip, 52, 152, 219)},
        {"shim-red", new EffectShimColor(strip, 231, 76, 60)},

        // Эффекты на основе палитр (по вертикали)
        {"cyberpunk", new PaletteEffect(strip, 50, 
            CYBERPUNK_PALETTE, CYBERPUNK_PALETTE_SIZE)},
        {"sunset", new PaletteEffect(strip, 50,
            SUNSET_PALETTE, SUNSET_PALETTE_SIZE)},
        {"optimus", new PaletteEffect(strip, 50,
            OPTIMUS_PALETTE, OPTIMUS_PALETTE_SIZE)},
        {"warm", new PaletteEffect(strip, 50,
            WARM_PALETTE, WARM_PALETTE_SIZE)},
        {"cold", new PaletteEffect(strip, 50,
            COLD_PALETTE, COLD_PALETTE_SIZE)},
        {"hot", new PaletteEffect(strip, 50,
            HOT_PALETTE, HOT_PALETTE_SIZE)},
        {"pink", new PaletteEffect(strip, 50,
            PINK_PALETTE, PINK_PALETTE_SIZE)},
        {"comfy", new PaletteEffect(strip, 50,
            COMFY_PALETTE, COMFY_PALETTE_SIZE)},
        {"girl", new PaletteEffect(strip, 50,
            GIRL_PALETTE, GIRL_PALETTE_SIZE)},
        {"christmas", new PaletteEffect(strip, 50,
            CHRISTMAS_PALETTE, CHRISTMAS_PALETTE_SIZE)},
        {"acid", new PaletteEffect(strip, 50,
            ACID_PALETTE, ACID_PALETTE_SIZE)},
        {"smoke", new PaletteEffect(strip, 50,
            SMOKE_PALETTE, SMOKE_PALETTE_SIZE)},
        {"aurora", new PaletteEffect(strip, 50,
            AURORA_PALETTE, AURORA_PALETTE_SIZE)},
        {"redwhite", new PaletteEffect(strip, 50,
            REDWHITE_PALETTE, REDWHITE_PALETTE_SIZE)},
        {"ocean", new PaletteEffect(strip, 50,
            OCEAN_PALETTE, OCEAN_PALETTE_SIZE)}
    };

    settings = {"random", false, 30};
}

void EffectsProcessor::begin() {
    // Загружаем настройки
    Storage::load("effects-settings", [this](JsonDocument & doc) {
        settings.name = doc["name"] | "random";
        settings.slideshow = doc["slideshow"] | false;
        settings.timeout = doc["timeout"] | 30;
    });

    if (settings.slideshow) {
        slideshowOn();
    } else {
        setEffect(settings.name);
    }
}

bool EffectsProcessor::setEffect(String effect) {
    strip.clear();
    for (int i = 0; i < effects.size(); i++) {
        if (effect != effects[i].first) continue;

        currentEffect = i;

        settings.name = effect;
        settings.slideshow = false;
        saveSettings();
        return true;
    }
    return false;
}

String EffectsProcessor::getEffect() {
    return effects[currentEffect].first;
}

void EffectsProcessor::tick() {
    if (!strip.getStripState()) return;
    effects[currentEffect].second->tick();

    // Slideshow
    if (settings.slideshow && 
        millis() - slideshowTimer > settings.timeout * 1000) {
        setRandomEffect();
        slideshowTimer = millis();
    }
}

void EffectsProcessor::setRandomEffect() {
    currentEffect = random(effects.size());
    settings.name = effects[currentEffect].first;
    saveSettings();
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
    saveSettings();
    setEffect(settings.name);
}