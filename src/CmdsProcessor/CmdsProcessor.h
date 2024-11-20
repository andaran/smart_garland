#pragma once

#include <ArduinoJson.h>
#include <Arduino.h>
#include <string>
#include <unordered_map>

#include "../EffectsProcessor/EffectsProcessor.h"
#include "../Strip/StripProcessor.h"

class CmdsProcessor {
public:
    CmdsProcessor(EffectsProcessor * effectsProcessor, 
                  StripProcessor * strip, 
                  std::unordered_map<std::string, std::string> & state, 
                  bool & stripState,
                  bool & streamState);
    String processCmds(String cmd);
private:
    EffectsProcessor * effectsProcessor;
    StripProcessor * strip;
    std::unordered_map<std::string, std::string> & state;
    bool & stripState;
    bool & streamState;

    // Комманды
    String effect(String const & cmdArgs);
    String turn(String const & cmdArgs);
    String stream(String const & cmdArgs);
};