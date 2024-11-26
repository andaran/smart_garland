#pragma once

#include "Storage.h"

template<typename T>
bool Storage::save(const char* filename, const T& config, 
                   void (*serializeFunc)(JsonDocument&, const T&)) {
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
    serializeFunc(doc, config);

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

template<typename T>
bool Storage::load(const char* filename, T& config, 
                   void (*deserializeFunc)(const JsonDocument&, T&)) {
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

    deserializeFunc(doc, config);
    return true;
}