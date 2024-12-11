#include "Animation.h"

EffectAnimation::EffectAnimation(StripProcessor & strip, 
    String name) : AnimEffect(strip, name) {
    
    backgroundEffect = createEffect(strip, animation.background);
    timeout = animation.duration;

    loadFrame();
}

EffectAnimation::~EffectAnimation() {
    delete backgroundEffect;
}

void EffectAnimation::playFrame() {
    strip.clearFgLayer();
    strip.stealthClear();

    // Отрисовываем кадр
    for (int i = 0; i < NUM_LEDS; i++) {
        if (getLedState(i)) {
            uint8_t r, g, b;
            getLedColor(i, r, g, b);
            strip.setFgLayerColor(i, new Color(r, g, b));
        }
    }

    if (!backgroundEffect) {
        strip.show();
    }
    nextFrame();
}

void EffectAnimation::nextFrame() {
    if (frame < animation.frames - 1) {
        frame++;
    } else {
        frame = 0;
    }
    loadFrame();
}