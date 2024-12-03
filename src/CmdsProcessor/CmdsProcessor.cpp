#include "CmdsProcessor.h"

CmdsProcessor::CmdsProcessor(EffectsProcessor & effectsProcessor, 
                             StripProcessor & strip, 
                             JsonObject & state, 
                             byte & streamState,
                             unsigned long & swithTimer)
    : effectsProcessor(effectsProcessor), strip(strip), 
      state(state), streamState(streamState), swithTimer(swithTimer) {
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
    if (cmdName == "timer") return timer(cmdArgs);
    if (cmdName == "fs") return fs(cmdArgs);
    if (cmdName == "slideshow") return slideshow(cmdArgs);
    if (cmdName == "memory") return memory(cmdArgs);
    return "Unknown command";
}

String CmdsProcessor::effect(String const & cmdArgs) {
    if (cmdArgs == "") {
        return "Current effect is " + effectsProcessor.getEffect();
    }
    if (cmdArgs == "random") {
        effectsProcessor.slideshowOff();
        effectsProcessor.setRandomEffect();
        return "Effect set to " + effectsProcessor.getEffect();
    }
    if (effectsProcessor.setEffect(cmdArgs)) {
        effectsProcessor.slideshowOff();
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

String CmdsProcessor::timer(String const & cmdArgs) {
    if (cmdArgs == "") {
        String message = "Timer is ";
        message += swithTimer ? "on" : "off";
        return message;
    }
    if (cmdArgs == "off") {
        swithTimer = 0;
        return "Timer turned off";
    }
    unsigned long timer = cmdArgs.toInt();
    if (timer < 0) {
        return "Timer must be positive";
    }
    swithTimer = millis() + timer * 1000 * 60;
    return "Timer set to " + String(timer) + " minutes";
}

String CmdsProcessor::fs(String const & cmdArgs) {
    if (cmdArgs == "format") {
        LittleFS.format();
        return "File system formatted";
    }
    if (cmdArgs == "list") {
        Dir dir = LittleFS.openDir("/");
        String files = "Files:\n";
        while (dir.next()) {
            files += "  " + dir.fileName() + "\n";
        }
        return files;
    }
    if (cmdArgs == "status") {
        FSInfo fs_info;
        LittleFS.info(fs_info);

        unsigned long total = fs_info.totalBytes / 1024;
        unsigned long used = fs_info.usedBytes / 1024;
        unsigned long available = total - used;
        double percent = ((double) used / (double) total) * 100;

        String status = "File system status (in Kb):";
        status += "\nTotal: " + String(total);
        status += "\nUsed: " + String(used);
        status += "\nAvailable: " + String(available);
        status += "\nUsage: " + String(percent, 2) + "%";
        return status;
    }

    // Команды с несколькими аргументами
    int spaceIndex = cmdArgs.indexOf(" ");
    String cmdName = cmdArgs.substring(0, spaceIndex);
    String cmdArgs2 = spaceIndex == -1 ? "" : 
        cmdArgs.substring(spaceIndex + 1);
    
    if (cmdName == "remove") {
        if (cmdArgs2 == "") {
            return "Filename is required";
        }
        if (Storage::remove(cmdArgs2.c_str())) {
            return "File removed";
        }
        return "File not found";
    }
    if (cmdName == "read") {
        if (cmdArgs2 == "") {
            return "Filename is required";
        }
        if (!Storage::exists(cmdArgs2.c_str())) {
            return "File not found";
        }
        return Storage::read(cmdArgs2.c_str()).c_str();
    }

    return "Unknown command";
}

String CmdsProcessor::slideshow(String const & cmdArgs) {
    if (cmdArgs == "" || cmdArgs == "on") {
        effectsProcessor.slideshowOn();
        return "Slideshow started";
    }
    if (cmdArgs == "off") {
        effectsProcessor.slideshowOff();
        return "Slideshow stopped";
    }
    unsigned timeout = cmdArgs.toInt();
    if (timeout <= 0) {
        return "Invalid timeout";
    }
    effectsProcessor.slideshowOn(timeout);
    return "Slideshow started with timeout " + String(timeout);
}

String CmdsProcessor::memory(String const & cmdArgs) {
    int freeHeap = ESP.getFreeHeap();
    float usagePercent = (float)(81920 - freeHeap) / 81920 * 100.0;

    String status = "Memory status (in bytes):";
    status += "\nTotal heap: 81920";
    status += "\nFree heap: " + String(freeHeap);
    status += "\nHeap fragmentation: " + String(ESP.getHeapFragmentation());
    status += "\nHeap usage: " + String(usagePercent, 2) + "%";
    return status;
}