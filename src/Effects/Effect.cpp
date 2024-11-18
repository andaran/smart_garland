#include "Effect.h"

Effect::Effect(Adafruit_NeoPixel * strip, unsigned long timeout) {
    this->strip = strip;
    this->timeout = timeout;
    this->timer = millis();
}

void Effect::tick() {
    if (millis() - timer >= timeout) {
        timer = millis();
        playFrame();
    }
}

void Effect::clear() {
    for (int i = 0; i < NUM_LEDS; i++) {
        strip->setPixelColor(i, strip->Color(0, 0, 0));
    }
    strip->show();
}