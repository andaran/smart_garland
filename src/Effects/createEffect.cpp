#include "createEffect.h"

Effect * createEffect(StripProcessor & strip, String name) {
    // Простые эффекты
    if (name == "test") return new EffectTest(strip);
    if (name == "rainbow") return new EffectRainbow(strip);

    // Мерцающий цвет
    if (name == "color-red") return new EffectColor(strip, {255, 0, 0});

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
    if (name == "fog") return new PaletteEffect(
        strip, 50, FOG_PALETTE, FOG_PALETTE_SIZE);

    // Эффекты - полоски
    if (name == "candy") return new EffectStripes(
        strip, {180, 180, 180}, {255, 0, 0});
    if (name == "police") return new EffectStripes(
        strip, {0, 0, 255}, {255, 0, 0});
    if (name == "blueberry-candy") return new EffectStripes(
        strip, {155, 89, 182}, {0, 0, 0});
    if (name == "lemonade") return new EffectStripes(
        strip, {241, 196, 15}, {255, 65, 24});
    if (name == "mint-candy") return new EffectStripes(
        strip, {16, 255, 126}, {156, 136, 255});
    if (name == "strawberry") return new EffectStripes(
        strip, {232, 65, 24}, {76, 209, 55});

    // Эффекты - дождь (с бэкграундом)
    if (name == "rain") return new EffectRain(strip, {0, 0, 255});
    if (name == "snow") return new EffectRain(strip, {255, 255, 255});
    if (name == "acid-rain") return new EffectRain(strip, {76, 209, 55});
    if (name == "bite-a-lemon") return new EffectRain(strip, {254, 211, 48});
    if (name == "hell-rain") return new EffectRain(strip, {232, 65, 24});

    // Анимации
    if (name.startsWith("anim-")) {
        if (!LittleFS.exists(name)) return nullptr;
        return new EffectAnimation(strip, name.substring(5));
    }

    return nullptr;
}