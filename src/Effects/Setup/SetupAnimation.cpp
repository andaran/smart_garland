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

void SetupAnimation::nextFrame() {
    save();
    frame++;
    if (frame >= animation.frames) {
        animation.frames = frame + 1;
    }
    strip.stealthClear();
    loadFrame();
}

void SetupAnimation::prevFrame() {
    save();
    if (frame > 0) {
        frame--;
        strip.stealthClear();
        loadFrame();
    }
}

void SetupAnimation::deleteFrame() {
    if (animation.frames == 1) {
        return;
    }

    save();

    for (int i = frame; i < animation.frames - 1; i++) {
        String fromPath = "anim-" + name + "-" + String(i + 1);
        String toPath = "anim-" + name + "-" + String(i);

        if (LittleFS.exists(fromPath)) {
            LittleFS.rename(fromPath.c_str(), toPath.c_str());
        }
    }

    if (frame == animation.frames - 1) {
        frame--;
    }

    animation.frames--;

    String lastFrame = "anim-" + name + "-" + String(animation.frames);
    if (LittleFS.exists(lastFrame)) {
        LittleFS.remove(lastFrame);
    }

    strip.stealthClear();
    loadFrame();
    save();
}

String SetupAnimation::getFrame() {
    return "Frame " + String(frame + 1) + " of " + String(animation.frames);
}