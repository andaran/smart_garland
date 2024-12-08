#include "SetupAnimation.h"

SetupAnimation::SetupAnimation(StripProcessor & strip, 
    String name) : AnimEffect(strip, name) {

    backgroundEffect = createEffect(strip, animation.background);

    loadFrame();
}

SetupAnimation::~SetupAnimation() {
    save();
}

void SetupAnimation::playFrame() {
    // Отрисовываем кадр
    for (int i = 0; i < NUM_LEDS; i++) {
        if (getLedState(i)) {
            uint8_t r, g, b;
            getLedColor(i, r, g, b);
            strip.updateFgLayerColor(i, r, g, b);
        } else {
            strip.removeFgLayerColor(i);
        }
    }

    strip.show();
}

void SetupAnimation::addLed(int i, byte r, byte g, byte b) {
    setLed(i, true, r, g, b);
}

void SetupAnimation::removeLed(int i) {
    setLed(i, false);
    strip.stealthClear();
}

void SetupAnimation::addBackground(String name) {
    animation.background = name;
    saveAnimation();
    delete backgroundEffect;
    backgroundEffect = createEffect(strip, name);
}

void SetupAnimation::removeBackground() {
    animation.background = "";
    saveAnimation();
    delete backgroundEffect;
    backgroundEffect = nullptr;
    strip.stealthClear();
}

void SetupAnimation::save() {
    saveAnimation();
    saveFrame();
}