#include "Test.h"

EffectTest::EffectTest(Adafruit_NeoPixel * strip) : Effect(strip, 500) {
    this->shift = 0;
}

void EffectTest::playFrame() {
    clear();
    for (int i = shift; i < NUM_LEDS; i += 4) {
        strip->setPixelColor(i, strip->Color(20, 20, 20));
    }
    strip->show();
    shift = (shift + 1) % 4;
}