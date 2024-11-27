#include "Storage.h"

bool Storage::exists(const char* filename) {
    return LittleFS.exists(filename);
}

bool Storage::remove(const char* filename) {
    if (!LittleFS.exists(filename)) {
        return false;
    }
    return LittleFS.remove(filename);
}

void Storage::begin() {
    if (!LittleFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }
}

std::string Storage::read(const char* filename) {
    if (!LittleFS.exists(filename)) {
        return "";
    }

    File file = LittleFS.open(filename, "r");
    if (!file) {
        return "";
    }

    std::string content;
    while (file.available()) {
        content += (char) file.read();
    }

    file.close();
    return content;
}