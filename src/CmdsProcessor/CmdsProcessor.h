#pragma once

#include <ArduinoJson.h>
#include <Arduino.h>
#include <string>
#include <unordered_map>

#include "../EffectsProcessor/EffectsProcessor.h"
#include "../Strip/StripProcessor.h"

class CmdsProcessor {
public:
    CmdsProcessor(EffectsProcessor & effectsProcessor, 
                  StripProcessor & strip, 
                  JsonObject & state, 
                  byte & streamState);
    String processCmds(String cmd);
private:
    EffectsProcessor & effectsProcessor;
    StripProcessor & strip;
    JsonObject & state;
    byte & streamState;

    // Комманды
    String effect(String const & cmdArgs);
    String power(String const & cmdArgs);
    String stream(String const & cmdArgs);
    String brightness(String const & cmdArgs);
};