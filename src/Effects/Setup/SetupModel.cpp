#include "SetupModel.h"

SetupModel::SetupModel(StripProcessor & strip) 
    : Effect(strip, 200) {
    
    strip.clear();
}

SetupModel::~SetupModel() {
    strip.stealthClear();
}

void SetupModel::load() {
    loadTurns();
}

void SetupModel::playFrame() {
    strip.stealthClear();

    for (int i = 0; i < turns.size(); i++) {
        strip.setPixelColor(
            getAbsoluteIndex(i, 0), 0, 0, 255);
    }

    strip.show();
}