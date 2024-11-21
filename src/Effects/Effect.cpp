#include "Effect.h"

Effect::Effect(StripProcessor & strip, unsigned long timeout) : 
    strip(strip), timeout(timeout), timer(millis()) {}

void Effect::tick() {
    if (millis() - timer >= timeout) {
        timer = millis();
        playFrame();
    }
}