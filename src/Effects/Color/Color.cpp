#include "Color.h"

EffectColor::EffectColor(StripProcessor & strip, Color color) 
    : Effect(strip, 20) {

    brightness = strip.getBrightness();
    brightnessKoef = brightness / 255.0;
    this->color.r = color.r * brightnessKoef;
    this->color.g = color.g * brightnessKoef;
    this->color.b = color.b * brightnessKoef;
    
    // Заполняем значения цвеов пикселей
    for (int i = 0; i < NUM_LEDS; i++) {
        pixels[i].offset = random(1, 254);
        pixels[i].direction = random(2);
    }

    strip.stealthClear();
    strip.getStrip().setBrightness(255);
}

EffectColor::~EffectColor() {
    strip.getStrip().setBrightness(brightness);
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