#pragma once

#include <Arduino.h>

#include "../Effect.h"
#include "../../Strip/StripProcessor.h"
#include "../../Storage/Storage.h"

#include "settings.h"

class SetupModel : public Effect {
public:
    SetupModel(StripProcessor & strip);
    ~SetupModel();
    void load();
private:
    void playFrame() override;
};