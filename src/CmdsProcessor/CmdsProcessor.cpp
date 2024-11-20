#include "CmdsProcessor.h"

CmdsProcessor::CmdsProcessor(EffectsProcessor * effectsProcessor, 
                             StripProcessor * strip, 
                             std::unordered_map<std::string, std::string> & state, 
                             bool & stripState)
    : state(state), stripState(stripState) {
    this->effectsProcessor = effectsProcessor;
    this->strip = strip;
}

String CmdsProcessor::processCmds(String cmd) {
    if (cmd == "hello") {
        return "Hello, world!";
    }
    return "Unknown command";
}