#pragma once

#include <Arduino.h>
#include "settings.h"

struct SmoothTransition {
    uint32_t targetColors[NUM_LEDS];
    unsigned currentStep = 0;
    unsigned maxSteps = 0;
};

struct Color {
    Color(byte r, byte g, byte b);
    Color(Color & color);
    Color();
    byte r;
    byte g;
    byte b;
};

struct Animation {
    String background;
    unsigned duration = 200;
    unsigned frames = 1;
};

struct ColorPoint {
    byte position; // Позиция в градиенте (0-255)
    byte r, g, b;  // Цвет (RGB)
};