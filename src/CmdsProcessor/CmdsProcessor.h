#pragma once

#include <ArduinoJson.h>
#include <Arduino.h>
#include <string>
#include <unordered_map>

#include "../EffectsProcessor/EffectsProcessor.h"
#include "../Strip/StripProcessor.h"
#include "../Storage/Storage.h"
#include "../Effects/setup/SetupAnimation.h"

class CmdsProcessor {
public:
    CmdsProcessor(EffectsProcessor & effectsProcessor, 
                  StripProcessor & strip, 
                  JsonObject & state, 
                  byte & streamState,
                  unsigned long & swithTimer);
    String processCmds(String cmd);
private:
    EffectsProcessor & effectsProcessor;
    StripProcessor & strip;
    JsonObject & state;
    byte & streamState;
    unsigned long & swithTimer;

    enum states {
        INITAL,
        SETUP_ANIMATION,
        SETUP_TEXT,
        SETUP_MODEL
    };
    byte cmdsState = INITAL;
    String setupName = "";

    // Комманды основного состояния
    String effect(String const & cmdArgs);
    String power(String const & cmdArgs);
    String stream(String const & cmdArgs);
    String brightness(String const & cmdArgs);
    String timer(String const & cmdArgs);
    String fs(String const & cmdArgs);
    String slideshow(String const & cmdArgs);
    String memory(String const & cmdArgs);
    String turns(String const & cmdArgs);

    // Универсальные команды
    String setup(String const & cmdArgs);
    String save(String const & cmdArgs);

    // Комманды настроек анимации
    String led(String const & cmdArgs);
    String background(String const & cmdArgs);
};