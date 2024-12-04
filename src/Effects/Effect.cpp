#include "Effect.h"

Effect::Effect(StripProcessor & strip, unsigned long timeout) : 
    strip(strip), timeout(timeout), timer(millis()) {

    // Заполняем массив витков
    Storage::load("turns", [this](JsonDocument & doc) {
        int size = doc["size"];
        for (int i = 0; i < size; i++) {
            turns.push_back(doc["turns"][i]);
        }
    });
}

void Effect::tick() {
    if (backgroundEffect != nullptr) {
        backgroundEffect->tick();
    }
    if (millis() - timer >= timeout) {
        timer = millis();
        playFrame();
    }
}

byte Effect::getTurnNumber(int index) {
    byte turn = 0;
    int i = 0;
    while (i <= index) {
        i += turns[turn];
        turn++;
    }
    return turn - 1;
}

int Effect::getAbsoluteIndex(byte turn, int index) {
    int absoluteIndex = 0;
    for (int i = 0; i < turn; i++) {
        absoluteIndex += turns[i];
    }
    return absoluteIndex + index;
}