#include "Effect.h"

Effect::Effect(StripProcessor * strip, unsigned long timeout) {
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