#include "CmdsProcessor.h"

CmdsProcessor::CmdsProcessor(EffectsProcessor * effectsProcessor, 
                             StripProcessor * strip, 
                             JsonObject & state, 
                             bool & stripState,
                             bool & streamState)
    : state(state), stripState(stripState), streamState(streamState) {
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
    if (cmdName == "power") return power(cmdArgs);
    if (cmdName == "stream") return stream(cmdArgs);
    return "Unknown command";
}

String CmdsProcessor::effect(String const & cmdArgs) {
    if (cmdArgs == "") {
        return "Current effect is " + effectsProcessor->getEffect();
    }
    if (effectsProcessor->setEffect(cmdArgs)) {
        return "Effect set to " + cmdArgs;
    }
    return "Effect not found";
}

String CmdsProcessor::power(String const & cmdArgs) {
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

String CmdsProcessor::stream(String const & cmdArgs) {
    if (cmdArgs == "") {
        String message = "Stream is ";
        message += streamState ? "on" : "off";
        return message;
    }
    if (cmdArgs == "on") {
        streamState = true;
        return "Stream turned on";
    }
    if (cmdArgs == "off") {
        streamState = false;
        return "Stream turned off";
    }
    return "Unknown command";
}