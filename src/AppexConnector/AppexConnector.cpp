#include "AppexConnector.h"

AppexConnector::AppexConnector(String roomID, 
                               String roomPass,
                               std::unordered_map<std::string, std::string> & state,
                               std::function<void(
                                std::unordered_map<std::string, std::string>&)> callback) 
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

        /*

        Теперь подключаемся к комнате. 
        Это работает как группа в каком-нибудь мессенджере - 
        как только один участник напишет сообщение 
        (передаст обновление для объекта состояния),
        это сообщение сразу же получат все другие участники 
        (телефоны, платы esp, можно и малину подключить). 
        
        */
        connectToRoom();

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

    /* parse json */
    String messageType = "";
    String parsedParams = "";
    char oldSimbool;
    bool parseTypeFlag = false;
    bool parseParamsFlag = false;

    for (unsigned long i = 0; i < strlen(json); i++) {
        if (json[i] == '{') {
            parseParamsFlag = true;
            parsedParams = "";
        }

        if (json[i] == '"') {
        if (parseTypeFlag) {
            parseTypeFlag = false;
        } else if (messageType.length() == 0) {
            parseTypeFlag = true;
        }

        if (parseTypeFlag) {
            continue;
        }
        }

        if (parseTypeFlag) {
            messageType += json[i];
        }
        if (parseParamsFlag) {
            parsedParams += json[i];
        }

        if (json[i] == '}') {
            parseParamsFlag = false;
        }
            oldSimbool = json[i];
    }

    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, parsedParams);

    if (error) {
        Serial.print("[ERR] Ошибка парсинга json!");
    } else {
        
        /* count quantity of params and delete unnecessary symbols */
        String prms = "";
        int prmsQuant = 1;
        for (unsigned long i = 1; i < parsedParams.length() - 1; i++) {
        if (parsedParams[i] == '"') { continue; }
        if (parsedParams[i] == ',') { prmsQuant++; }
            prms += parsedParams[i];
        }

        /* put params to array cells */
        String namesAndValues[prmsQuant];
        int numberOfParam = 0;
        for (unsigned long i = 0; i < prms.length(); i++) {
            if (prms[i] == ',') {
                numberOfParam++;
                continue;
            }
            namesAndValues[numberOfParam] += prms[i];
        }

        /* split params and values */
        std::string prmName;
        std::string prmValue;
        char* values[prmsQuant];
        bool typeFlag = false;
        for (int i = 0; i < prmsQuant; i++) {
            typeFlag = false;
            prmName = "";
            prmValue = "";
            for (int j = 0; j < namesAndValues[i].length(); j++) {
                if (namesAndValues[i][j] == ':') {
                    typeFlag = true;
                    continue;
                }

                if (typeFlag) {
                    prmValue += namesAndValues[i][j];
                } else {
                    prmName += namesAndValues[i][j];
                }
            }

            /* save changes */
            if (state.count(prmName) != 0) {
                state.at(prmName) = prmValue;
            } else {
                Serial.print("[ERR] Неизвестный параметр \"");
                Serial.print(prmName.c_str());
                Serial.println("\"!");
            }
        }

        /* call update function */
        callback(state);
    }
}

void AppexConnector::connectToRoom() {
    // данные отсылаются в json
    DynamicJsonDocument doc(1024);
    JsonArray array = doc.to<JsonArray>();

    // добавляем название события, в данном случае - "connectToRoom".
    array.add("connectToRoom");

    // добавляем id и пароль комнаты для прохождения аутентификации
    JsonObject params = array.createNestedObject();
    params["roomId"] = roomID;
    params["roomPass"] = roomPass;

    // преобразуем json в строку
    String output;
    serializeJson(doc, output);

    // отправляем событие подключения к комнате 
    socketIO.sendEVENT(output);
}

void AppexConnector::message(String eventType, JsonObject sendState) {

    // данные отсылаются в json
    DynamicJsonDocument doc(1024);
    JsonArray array = doc.to<JsonArray>();

    // добавляем название события, обычно это 'update'
    array.add(eventType);

    // добавляем id и пароль комнаты для прохождения аутентификации,
    // добавляем обновленные данные
    JsonObject params = array.createNestedObject();
    params["roomId"] = roomID;
    params["roomPass"] = roomPass;
    params["params"] = sendState;

    // преобразуем json в строку
    String output;
    serializeJson(doc, output);

    // шлем событие на сервер appex
    socketIO.sendEVENT(output);
}

void AppexConnector::tick() {
    socketIO.loop();
}