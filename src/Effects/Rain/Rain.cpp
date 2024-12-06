#include "Rain.h"

EffectRain::EffectRain(StripProcessor & strip, 
    Color color) : Effect(strip, 500) {
    
    this->color = color;

    // Задаем фоновый эффект
    backgroundEffect = createEffect(strip, "fog");
    strip.setFgLayerState(true);
}

EffectRain::~EffectRain() {
    delete backgroundEffect;
    for (int i = 0; i < drops.size(); i++) {
        delete drops[i];
    }
    strip.setFgLayerState(false);
}

void EffectRain::playFrame() {
    strip.clearFgLayer();

    for (int i = 0; i < drops.size(); i++) {
        Drop * drop = drops[i];

        // Капля упала
        if (drop->turn == 0) {
            delete drop;
            drops.erase(drops.begin() + i);
            i--;
            continue;
        }

        // Капля падает
        drop->turn--;
        unsigned turnPos = map(drop->turnPos, 0, turns[0], 0, turns[drop->turn]);
        Color * colorPtr = new Color(color);
        strip.setFgLayerColor(
            getAbsoluteIndex(drop->turn, turnPos), colorPtr);
    }

    // Создаем новую каплю
    Drop * drop = new Drop();
    drop->turn = turns.size();
    drop->turnPos = random(turns[0]);
    drops.push_back(drop);

    strip.show();
}