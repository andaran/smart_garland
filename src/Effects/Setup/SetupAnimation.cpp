#include "SetupAnimation.h"

SetupAnimation::SetupAnimation(StripProcessor & strip, 
    String name) : Effect(strip, 200) {

    strip.clear();
    strip.show();
    
    if (Storage::exists(("anim-" + name).c_str())) {
        loadAnimation(name);
    } else {
        animation.name = name;
        animation.duration = 200;
        animation.background = "";
        animation.frames = {};
        saveAnimation();
    }

    backgroundEffect = createEffect(strip, animation.background);
    strip.setFgLayerState(true);
}

SetupAnimation::~SetupAnimation() {
    strip.setFgLayerState(false);
}

void SetupAnimation::playFrame() {
    strip.clearFgLayer();

    // Отрисовываем кадр
    if (animation.frames.size() == 0) {
        strip.show();
        return;
    }
    for (int i = 0; i < animation.frames[frame].size(); i++) {
        std::array<unsigned, 4> led = animation.frames[frame][i];
        Color * color = new Color(led[1], led[2], led[3]);
        strip.setFgLayerColor(led[0], color);
    }

    strip.show();
}

void SetupAnimation::addLed(int i, byte r, byte g, byte b) {
    std::array<unsigned, 4> colors = {i, r, g, b};
    if (!animation.frames.size()) {
        animation.frames.push_back({});
    }
    animation.frames[frame].push_back(colors);
    saveAnimation();
}

void SetupAnimation::removeLed(int i) {
    if (!animation.frames.size()) return;
    for (int j = 0; j < animation.frames[frame].size(); j++) {
        if (animation.frames[frame][j][0] == i) {
            animation.frames[frame].erase(animation.frames[frame].begin() + j);
            saveAnimation();
            strip.stealthClear();
            return;
        }
    }
}

void SetupAnimation::loadAnimation(String name) {
    Storage::load(("anim-" + name).c_str(), [this](JsonDocument& doc) {
        // Загружаем основные поля
        animation.name = doc["name"] | "";
        animation.duration = doc["duration"] | 0;
        animation.background = doc["background"] | "";

        // Загружаем массив кадров
        JsonArray framesArray = doc["frames"].as<JsonArray>();

        // Загружаем кадры
        for (JsonArray frame : framesArray) {

            // Загружаем значения пикселей
            std::vector<std::array<unsigned, 4>> frameRow;
            for (JsonArray cell : frame) {
                std::array<unsigned, 4> colors = {
                    cell[0] | 0,
                    cell[1] | 0,
                    cell[2] | 0,
                    cell[3] | 0
                };
                frameRow.push_back(colors);
            }
            animation.frames.push_back(frameRow);
        }
    });
}

void SetupAnimation::saveAnimation() {
    Storage::save(("anim-" + animation.name).c_str(), [this](JsonDocument& doc) {
        // Сохраняем основные поля
        doc["name"] = animation.name;
        doc["duration"] = animation.duration;
        doc["background"] = animation.background;

        // Сохраняем массив кадров
        JsonArray framesArray = doc.createNestedArray("frames");

        // Сохраняем кадры
        for (std::vector<std::array<unsigned, 4>> frame : animation.frames) {
            JsonArray frameArray = framesArray.createNestedArray();
            for (std::array<unsigned, 4> cell : frame) {
                JsonArray cellArray = frameArray.createNestedArray();
                cellArray.add(cell[0]);
                cellArray.add(cell[1]);
                cellArray.add(cell[2]);
                cellArray.add(cell[3]);
            }
        }
    });
}