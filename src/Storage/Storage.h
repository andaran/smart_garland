#pragma once

#include <ArduinoJson.h>
#include <LittleFS.h>

class Storage {
public:
    static void begin();

    template<typename T>
    static bool save(const char* filename, const T& config, 
                     void (*serializeFunc)(JsonDocument&, const T&));

    template<typename T>
    static bool load(const char* filename, T& config, 
                     void (*deserializeFunc)(const JsonDocument&, T&));

    static bool exists(const char* filename);
    static bool remove(const char* filename);
};

#include "Storage.tpp"