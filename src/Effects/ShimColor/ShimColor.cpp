#include "ShimColor.h"

EffectShimColor::EffectShimColor(StripProcessor & strip, byte r, byte g, byte b)
    : Effect(strip, 800) {

    this->r = r;
    this->g = g;
    this->b = b;
}

void EffectShimColor::playFrame() {
    for (int i = 0; i < NUM_LEDS; i++) {
        int nr = r + (random(80) - 40);
        int ng = g + (random(80) - 40);
        int nb = b + (random(80) - 40);

        nr = nr < 0 ? 0 : nr > 255 ? 255 : nr;
        ng = ng < 0 ? 0 : ng > 255 ? 255 : ng;
        nb = nb < 0 ? 0 : nb > 255 ? 255 : nb;

        strip.setPixelColor(i, nr, ng, nb);
    }
    strip.show();
}