#include "Rain.h"

EffectRain::EffectRain(StripProcessor & strip, 
    Color color) : Effect(strip, 300) {
    
    this->color = color;

    // Задаем фоновый эффект
    backgroundEffect = createEffect(strip, "fog");
    strip.setFgLayerState(true);
}

EffectRain::~EffectRain() {
    delete backgroundEffect;
    strip.setFgLayerState(false);
}

void EffectRain::playFrame() {
    strip.clearFgLayer();
    int index = random(NUM_LEDS);
    strip.setFgLayerColor(index, &color);
    strip.show();
}