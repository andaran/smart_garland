#pragma once

#include <ArduinoJson.h>

#include "../AppexConnector/AppexConnector.h"

class CmdsProcessor {
public:
    //CmdsProcessor();
    String processCmds(String cmd);
};