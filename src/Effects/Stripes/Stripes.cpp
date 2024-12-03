#include "Stripes.h"

EffectStripes::EffectStripes(StripProcessor & strip, 
    Color color1, Color color2) : Effect(strip, 300) {
    
    this->color1 = color1;
    this->color2 = color2;
    for (int i = 0; i < turns.size(); i++) {
        steps.push_back(std::round(turns[i] / 4.0));
    }
}

void EffectStripes::playFrame() {
    for (int i = 0; i < turns.size(); i++) {
        // Ширина полоски на данном витке
        int step = steps[i];
        // Сдвиг полоски на данном витке
        int shift = map(iter, 0, turns[0], 0, turns[i]);
        // Заливаем полоску
        for (int j = 0; j < turns[i]; j++) {
            int index = (j + shift) % turns[i];
            bool color = (j / step) % 2 == 0;
            strip.setPixelColor(getAbsoluteIndex(i, index), 
                color ? color1.r : color2.r, 
                color ? color1.g : color2.g, 
                color ? color1.b : color2.b
            );
        }
    }
    
    iter = (iter + 1) % turns[0];
    strip.show();
}