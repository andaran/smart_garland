#include "AppexConnector.h"

AppexConnector::AppexConnector(String roomID, 
                               String roomPass,
                               JsonObject& state,
                               std::function<void()> callback) 
    : roomID(roomID), roomPass(roomPass), state(state), callback(callback) {}

void AppexConnector::setup() {
    socketIO.beginSSL("appex-system.ru", 443, "/socket.io/?EIO=4");

    socketIO.onEvent([this](socketIOmessageType_t type, uint8_t * payload, size_t length) {
        this->socketIOEvent(type, payload, length);
    });
}

void AppexConnector::socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {
    switch (type) {
        case sIOtype_DISCONNECT: {
            Serial.println("[IOc] Ошибка подключения!\n");
            
        } break;

        case sIOtype_CONNECT: {
            Serial.println("[IOc] Подключено!");

            // join default namespace (no auto join in Socket.IO V3)
            socketIO.send(sIOtype_CONNECT, "/");

            message("connectToRoom", {});

        } break;

        case sIOtype_EVENT: {
            char* json = (char*) payload;

            // парсим событие с новым состоянием
            parseEvent(json);

        } break;

        default: {
            Serial.println("[IOc] Пришло что-то непонятное :(");
            hexdump(payload, length);

        } break;
    }
}

void AppexConnector::parseEvent(char* json) {
    // Динамическая структура для JSON
    JsonDocument doc;

    // Парсинг JSON
    DeserializationError error = deserializeJson(doc, json);

    if (error) {
        Serial.println("[ERR] Ошибка парсинга JSON!");
        Serial.println(error.c_str()); // Показываем ошибку
        return;
    }

    // Проверяем, что это массив
    if (!doc.is<JsonArray>()) {
        Serial.println("[ERR] Ожидается массив JSON!");
        Serial.println(json);
        return;
    }

    JsonArray jsonArray = doc.as<JsonArray>();

    // Проверяем, что в массиве достаточно элементов
    if (jsonArray.size() != 2) {
        Serial.println("[ERR] Нарушена структура массива JSON!");
        Serial.println(json);
        return;
    }

    // Извлекаем элементы массива
    String messageType = jsonArray[0].as<String>();
    JsonObject params = jsonArray[1].as<JsonObject>();

    if (!params.containsKey("params")) {
        Serial.println("[ERR] JSON объект не содержит ключа 'params'!");
        Serial.println(json);
        return;
    }

    // Извлекаем параметры
    JsonObject paramValues = params["params"].as<JsonObject>();

    for (JsonPair kv : paramValues) {
        std::string prmName = kv.key().c_str();

        if (state.containsKey(prmName)) {
            state[prmName] = kv.value();
        } else {
            Serial.print("[ERR] Неизвестный параметр: ");
            Serial.println(prmName.c_str());
        }
    }

    // Вызываем callback
    callback();
}

void AppexConnector::message(const char* eventType, 
                             const std::vector<String> & updateParams) {

    // данные отсылаются в json
    JsonDocument doc;
    JsonArray array = doc.to<JsonArray>();

    // добавляем название события, обычно это 'update'
    array.add(eventType);

    // добавляем id и пароль комнаты для прохождения аутентификации,
    // добавляем обновленные данные
    JsonObject params = array.add<JsonObject>();
    params["roomId"] = roomID;
    params["roomPass"] = roomPass;

    if (!updateParams.empty()) {
        JsonObject update = params.createNestedObject("params");
        for (String param : updateParams) {
            update[param] = state[param];
        }
    }

    // преобразуем json в строку
    String output;
    if (serializeJson(doc, output) == 0) {
        Serial.println("[ERR] Ошибка сериализации JSON!");
        return;
    }

    // шлем событие на сервер appex
    socketIO.sendEVENT(output);
}

void AppexConnector::update(const std::vector<String> & updateParams) {
    message("updateState", updateParams);
}

void AppexConnector::tick() {
    socketIO.loop();
}