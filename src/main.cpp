#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "settings.h"
#include "AppexConnector/AppexConnector.h"
#include "CmdsProcessor/CmdsProcessor.h"
#include "EffectsProcessor/EffectsProcessor.h"
#include "Strip/StripProcessor.h"

Adafruit_NeoPixel * ledStrip = new Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void appexCallback(std::unordered_map<std::string, std::string> & state);
void stripCallback(std::string & message);

std::unordered_map<std::string, std::string> initialState = {
    { "cmdToEsp", "" }, 
    { "ansFromEsp", "" },
    { "cmdId", "-1" },
    { "stripState", "" },
    { "lastChange", "0" }
};
bool stripState = true;

AppexConnector appex(roomIDSetting, roomPassSetting, initialState, appexCallback);

StripProcessor * strip = new StripProcessor(ledStrip, stripCallback);
EffectsProcessor * effectsProcessor = new EffectsProcessor(strip);
CmdsProcessor cmdsProcessor(effectsProcessor, strip, initialState, stripState);

void setup() {
    // запускаем Serial порт
    Serial.begin(115200);
    Serial.setDebugOutput(false);

    // настраиваем ленту
    ledStrip->begin();
    ledStrip->show();

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
    if (stripState) effectsProcessor->tick();
}

String cmdId = "-1";
void appexCallback(std::unordered_map<std::string, std::string> & state) {

    String id = state.at("cmdId").c_str();
    if (id == cmdId) {
        return;
    }
    if (cmdId == "-1") {
        cmdId = "0";

        DynamicJsonDocument doc(1024);
        JsonObject sendState = doc.createNestedObject();
        sendState["cmdId"] = cmdId;
        appex.message("updateState", sendState);
        
        return;
    }
    cmdId = id;

    String cmd = state.at("cmdToEsp").c_str();
    String ans = cmdsProcessor.processCmds(cmd);

    Serial.print("> ");
    Serial.println(cmd);

    // Отвечаем на команду
    DynamicJsonDocument doc(1024);
    JsonObject sendState = doc.createNestedObject();
    sendState["ansFromEsp"] = ans;
    appex.message("updateState", sendState);

    // Сбрасываем команду
    sendState["ansFromEsp"] = "[" + cmdId + "]";
    appex.message("updateState", sendState);

    Serial.println(ans);
}

void stripCallback(std::string & message) {
    // Отправляем состояние ленты на сервер
    DynamicJsonDocument doc(1024);
    JsonObject sendState = doc.createNestedObject();
    sendState["stripState"] = message;
    appex.message("updateState", sendState);
}