#include "CmdsProcessor.h"

String CmdsProcessor::processCmds(String cmd) {
    if (cmd == "hello") {
        return "Hello, world!";
    }
    return "Unknown command";
}