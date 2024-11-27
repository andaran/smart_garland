#pragma once

#include <ArduinoJson.h>
#include <LittleFS.h>

class Storage {
public:
    static void begin();

    static bool save(const char* filename, 
                     std::function<void(JsonDocument&)>);

    static bool load(const char* filename, 
                     std::function<void(JsonDocument&)>);

    static bool exists(const char* filename);
    static bool remove(const char* filename);
    static std::string read(const char* filename);
};