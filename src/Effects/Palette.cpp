#include "Palette.h"

Palette::Palette(ColorPoint * palette, int paletteSize) {
    this->palette = palette;
    this->paletteSize = paletteSize;
}

void Palette::getColor(byte index, byte & r, byte & g, byte & b) {
    for (int i = 0; i < paletteSize - 1; i++) {
        if (index >= palette[i].position && index <= palette[i + 1].position) {
            // Интерполяция между firePalette[i] и firePalette[i + 1]
            uint8_t range = palette[i + 1].position - palette[i].position;
            uint8_t relativeIndex = index - palette[i].position;
            float fraction = (float)relativeIndex / range;

            r = palette[i].r + fraction * (palette[i + 1].r - palette[i].r);
            g = palette[i].g + fraction * (palette[i + 1].g - palette[i].g);
            b = palette[i].b + fraction * (palette[i + 1].b - palette[i].b);
            return;
        }
    }
    // Если индекс вне диапазона, вернуть последний цвет
    r = palette[paletteSize - 1].r;
    g = palette[paletteSize - 1].g;
    b = palette[paletteSize - 1].b;
}