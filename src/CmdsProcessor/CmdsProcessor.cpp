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
    cmd.toLowerCase();
    cmd.trim();

    int spaceIndex = cmd.indexOf(" ");
    String cmdName = cmd.substring(0, spaceIndex);
    String cmdArgs = spaceIndex == -1 ? "" : cmd.substring(spaceIndex + 1);

    if (cmdName == "effect") return effect(cmdArgs);
    else if (cmdName == "turn") return turn(cmdArgs);
    else return "Unknown command";
}

String CmdsProcessor::effect(String const & cmdArgs) {
    if (effectsProcessor->setEffect(cmdArgs)) {
        return "Effect set to " + cmdArgs;
    }
    return "Effect not found";
}

String CmdsProcessor::turn(String const & cmdArgs) {
    if (cmdArgs == "") {
        String message = "Strip is ";
        message += stripState ? "on" : "off";
        return message;
    }
    if (cmdArgs == "on") {
        stripState = true;
        return "Strip turned on";
    }
    if (cmdArgs == "off") {
        stripState = false;
        strip->clear();
        strip->show();
        return "Strip turned off";
    }
    return "Unknown command";
}