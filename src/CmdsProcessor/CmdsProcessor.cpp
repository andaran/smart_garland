#include "CmdsProcessor.h"

CmdsProcessor::CmdsProcessor(EffectsProcessor & effectsProcessor, 
                             StripProcessor & strip, 
                             JsonObject & state, 
                             byte & streamState)
    : effectsProcessor(effectsProcessor), strip(strip), state(state), streamState(streamState) {
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
    if (cmdName == "brightness") return brightness(cmdArgs);
    return "Unknown command";
}

String CmdsProcessor::effect(String const & cmdArgs) {
    if (cmdArgs == "") {
        return "Current effect is " + effectsProcessor.getEffect();
    }
    if (effectsProcessor.setEffect(cmdArgs)) {
        return "Effect set to " + cmdArgs;
    }
    return "Effect not found";
}

String CmdsProcessor::power(String const & cmdArgs) {
    if (cmdArgs == "") {
        String message = "Strip is ";
        message += strip.getStripState() ? "on" : "off";
        return message;
    }
    if (cmdArgs == "on") {
        strip.setStripState(true);
        return "Strip turned on";
    }
    if (cmdArgs == "off") {
        strip.setStripState(false);
        return "Strip turned off";
    }
    return "Unknown command";
}

String CmdsProcessor::stream(String const & cmdArgs) {
    if (cmdArgs == "") {
        String message = "Streaming ";
        switch (streamState) {
            case 0:
                message += "is off";
                break;
            case 1:
                message += "via Wi-Fi";
                break;
            case 2:
                message += "via cable";
                break;
        }
        return message;
    }
    if (cmdArgs == "wifi") {
        streamState = 1;
        return "Stream switched to Wi-Fi";
    }
    if (cmdArgs == "cable") {
        streamState = 2;
        return "Stream switched to cable";
    }
    if (cmdArgs == "off") {
        streamState = 0;
        return "Stream turned off";
    }
    return "Unknown command";
}

String CmdsProcessor::brightness(String const & cmdArgs) {
    if (cmdArgs == "") {
        return "Brightness is " + String(strip.getBrightness());
    }
    byte brightness = cmdArgs.toInt();
    if (brightness < 0 || brightness > 255) {
        return "Brightness must be in range [0, 255]";
    }
    strip.setBrightness(brightness);
    return "Brightness set to " + String(brightness);
}