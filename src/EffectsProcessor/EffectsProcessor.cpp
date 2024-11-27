#include "EffectsProcessor.h"

EffectsProcessor::EffectsProcessor(StripProcessor & strip) : strip(strip) {

    // Добавляем эффекты
    effects = {
        // Простые эффекты
        {"test", new EffectTest(strip)},
        {"rainbow", new EffectRainbow(strip)},

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

    settings = {"random", 30 * 1000};
}

void EffectsProcessor::begin() {
    // Загружаем настройки
    Storage::load("effects-settings", [this](JsonDocument & doc) {
        settings.name = doc["name"] | "random";
        settings.timeout = doc["timeout"] | 30 * 1000;
    });

    setEffect(settings.name);
}

bool EffectsProcessor::setEffect(String effect) {
    strip.clear();
    if (effect == "random") {
        setRandomEffect();
        return true;
    }
    for (int i = 0; i < effects.size(); i++) {
        if (effect != effects[i].first) continue;

        currentEffect = i;
        // Сохраняем эффект
        settings.name = effect;
        Storage::save("effects-settings", [this](JsonDocument & doc) {
            doc["name"] = settings.name;
        });

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
}

void EffectsProcessor::setRandomEffect() {
    currentEffect = random(effects.size());
    
    // Сохраняем эффект
    settings.name = effects[currentEffect].first;
    Storage::save("effects-settings", [this](JsonDocument & doc) {
        doc["name"] = settings.name;
    });
}