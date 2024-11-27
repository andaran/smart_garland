#pragma once

#include <Arduino.h>

struct ColorPoint {
    byte position; // Позиция в градиенте (0-255)
    byte r, g, b;  // Цвет (RGB)
};

class Palette {
public:
    Palette(ColorPoint * palette, int paletteSize);
    void getColor(byte index, byte & r, byte & g, byte & b);
private:
    ColorPoint * palette;
    int paletteSize;
};