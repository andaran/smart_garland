#include "Test.h"

EffectTest::EffectTest(StripProcessor & strip) : Effect(strip, 500) {
    this->shift = 0;
}

void EffectTest::playFrame() {
    strip.clear();
    for (int i = shift; i < NUM_LEDS; i += 4) {
        strip.setPixelColor(i, 255, 255, 255);
    }
    strip.show();
    shift = (shift + 1) % 4;
}