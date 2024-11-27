#include "PaletteEffect.h"

PaletteEffect::PaletteEffect(StripProcessor & strip, unsigned long timeout, 
                             ColorPoint * palette, int paletteSize)
    : Effect(strip, timeout), Palette(palette, paletteSize) {
}

void PaletteEffect::playFrame() {
    Serial.println("PaletteEffect::playFrame");
    for (int i = 0; i < NUM_LEDS; i++) {
        byte index = (startIndex + (i * 255 / NUM_LEDS)) % 255;
        byte r, g, b;
        getColor(index, r, g, b);
        strip.setPixelColor(i, r, g, b);
    }
    startIndex = (startIndex + 1) % 255;
    strip.show();
}