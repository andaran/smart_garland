#include "Rainbow.h"

EffectRainbow::EffectRainbow(StripProcessor & strip) : Effect(strip, 50) {
    this->step = 0;
}

void EffectRainbow::playFrame() {
    for (int i = 0; i < NUM_LEDS; i++) {
        Rgb color = wheel((i + step) & 255);
        strip.setPixelColor(i, color.r, color.g, color.b);
    }
    step = (step + 5) % 256;
    strip.show();
}

Rgb EffectRainbow::wheel(byte wheelPos) {
    wheelPos = 255 - wheelPos;
    if (wheelPos < 85) {
        return Rgb{255 - wheelPos * 3, 0, wheelPos * 3};
    }
    if (wheelPos < 170) {
        wheelPos -= 85;
        return Rgb{0, wheelPos * 3, 255 - wheelPos * 3};
    }
    wheelPos -= 170;
    return Rgb{wheelPos * 3, 255 - wheelPos * 3, 0};
}