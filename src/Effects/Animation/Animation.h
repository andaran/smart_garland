#pragma once

#include "../AnimEffect.h"
#include "../createEffect.h"

#include "structs.h"

class EffectAnimation : public AnimEffect {
public:
    EffectAnimation(StripProcessor & strip, String name);
    ~EffectAnimation();

protected:
    void playFrame() override;

    void nextFrame();
};