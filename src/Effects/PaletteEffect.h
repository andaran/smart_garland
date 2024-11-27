#pragma once

#include <Arduino.h>
#include "Effect.h"
#include "Palette.h"

class PaletteEffect : public Effect, public Palette {
public:
    PaletteEffect(StripProcessor & strip, unsigned long timeout, 
                  ColorPoint * palette, int paletteSize);
    void playFrame() override;

private:
    byte startIndex = 0;
};