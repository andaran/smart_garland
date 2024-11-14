#include <Arduino.h>

#include "settings.h"
#include "AppexConnector/AppexConnector.h"

String cmdId = "-1";

void appexCallback(std::unordered_map<std::string, std::string> & state);

std::unordered_map<std::string, std::string> initialState = {
    { "cmdToEsp", "" }, 
    { "ansFromEsp", "" },
    { "cmdId", "0" },
    { "lastChange", "0" }
};

AppexConnector appex(roomIDSetting, roomPassSetting, initialState, appexCallback);

void setup() {
    // запускаем Serial порт
    Serial.begin(115200);
    Serial.setDebugOutput(false);

    // подключаемся к WiFi
    WiFi.begin(ussid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(300);
        Serial.print(".");
    }
    Serial.println("\n[LOG] Wifi connected!\n");

    // ip адрес устройства
    String ip = WiFi.localIP().toString();
    Serial.printf("[SETUP] IP adress: %s\n", ip.c_str());

    // настраиваем подключение к Appex
    appex.setup();
}

void loop() {
    appex.tick();
}

void appexCallback(std::unordered_map<std::string, std::string> & state) {

    String id = state.at("cmdId").c_str();
    if (id == cmdId) {
        return;
    }
    cmdId = id;

    String cmd = state.at("cmdToEsp").c_str();
    String ans;

    Serial.print("> ");
    Serial.println(cmd);

    if (cmd == "hello") {
        ans = "Hello world!";
    } else if (cmd == "appex") {
        ans = "is the best remote control system!";
    } else {
        ans = "Unknown command";
    }

    // Отвечаем на команду
    DynamicJsonDocument doc(1024);
    JsonObject sendState = doc.createNestedObject();
    sendState["ansFromEsp"] = ans;
    appex.message("updateState", sendState);

    // Сбрасываем команду
    DynamicJsonDocument doc2(1024);
    JsonObject sendState2 = doc2.createNestedObject();
    sendState2["ansFromEsp"] = "[" + cmdId + "]";
    appex.message("updateState", sendState2);

    Serial.println(ans);
}