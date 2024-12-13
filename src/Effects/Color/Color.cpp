#include "Color.h"

EffectColor::EffectColor(StripProcessor & strip, Color color) 
    : Effect(strip, 20) {

    this->color = color;
    
    // Заполняем значения цвеов пикселей
    for (int i = 0; i < NUM_LEDS; i++) {
        pixels[i].offset = random(1, 254);
        pixels[i].direction = random(2);
    }

    strip.stealthClear();
}

void EffectColor::playFrame() {
    strip.stealthClear();

    for (int i = 0; i < NUM_LEDS; i++) {
        byte offset = pixels[i].offset;
        byte r = color.r * offset / 255;
        byte g = color.g * offset / 255;
        byte b = color.b * offset / 255;

        strip.setPixelColor(i, r, g, b);

        pixels[i].offset += pixels[i].direction ? 1 : -1;
        if (pixels[i].offset <= 1 || pixels[i].offset >= 254) {
            pixels[i].direction = !pixels[i].direction;
        }
    }

    strip.show();
}