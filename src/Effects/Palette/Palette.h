#pragma once

#include <Arduino.h>
#include "structs.h"

class Palette {
public:
    Palette(ColorPoint * palette, int paletteSize);
    void getColor(byte index, byte & r, byte & g, byte & b);
private:
    ColorPoint * palette;
    int paletteSize;
};