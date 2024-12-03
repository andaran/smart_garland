#pragma once

#include <Arduino.h>
#include "settings.h"

struct SmoothTransition {
    uint32_t targetColors[NUM_LEDS];
    unsigned currentStep = 0;
    unsigned maxSteps = 0;
};