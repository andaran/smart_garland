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

bool Storage::save(const char* filename, 
                   std::function<void(JsonDocument&)> serializeFunc) {
    JsonDocument doc;

    // Если файл существует, загружаем существующий JSON
    if (LittleFS.exists(filename)) {
        File file = LittleFS.open(filename, "r");
        if (!file) {
            return false;
        }

        DeserializationError error = deserializeJson(doc, file);
        file.close();

        // Если файл поврежден или пуст, очищаем документ
        if (error) {
            doc.clear();
        }
    }

    // Вызываем пользовательскую функцию для обновления JSON
    serializeFunc(doc);

    // Открываем файл для записи
    File file = LittleFS.open(filename, "w");
    if (!file) {
        return false;
    }

    // Сохраняем обновленный JSON
    if (serializeJson(doc, file) == 0) {
        file.close();
        return false;
    }

    file.close();
    return true;
}

bool Storage::load(const char* filename, 
                   std::function<void(JsonDocument&)> deserializeFunc) {
    if (!LittleFS.exists(filename)) {
        return false;
    }

    File file = LittleFS.open(filename, "r");
    if (!file) {
        return false;
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, file);
    file.close();

    if (error) {
        return false;
    }

    deserializeFunc(doc);
    return true;
}