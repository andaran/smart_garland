#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "settings.h"
#include "AppexConnector/AppexConnector.h"
#include "CmdsProcessor/CmdsProcessor.h"
#include "EffectsProcessor/EffectsProcessor.h"
#include "Strip/StripProcessor.h"

Adafruit_NeoPixel * ledStrip = new Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void appexCallback(std::unordered_map<std::string, std::string> & state);
void stripCallback(char* message);

std::unordered_map<std::string, std::string> initialState = {
    { "cmdToEsp", "" }, 
    { "ansFromEsp", "" },
    { "cmdId", "-1" },
    { "stripState", "" },
    { "lastChange", "0" }
};
bool stripState = true;
bool streamState = true;

AppexConnector appex(roomIDSetting, roomPassSetting, initialState, appexCallback);

StripProcessor * strip = new StripProcessor(ledStrip, stripCallback);
EffectsProcessor * effectsProcessor = new EffectsProcessor(strip);
CmdsProcessor cmdsProcessor(effectsProcessor, strip, initialState, 
                            stripState, streamState);

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
bool updated = true;
void appexCallback(std::unordered_map<std::string, std::string> & state) {
    updated = true;

    String id = state.at("cmdId").c_str();
    if (id == cmdId) {
        return;
    }
    if (cmdId == "-1") {
        cmdId = "0";

        JsonDocument doc;
        JsonObject sendState = doc.add<JsonObject>();
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
    JsonDocument doc;
    JsonObject sendState = doc.add<JsonObject>();
    sendState["ansFromEsp"] = ans;
    appex.message("updateState", sendState);

    // Сбрасываем команду
    sendState["ansFromEsp"] = "[" + cmdId + "]";
    appex.message("updateState", sendState);

    Serial.println(ans);
}

unsigned long lastUpdate = 0;
void stripCallback(char* message) {
    // Отправляем состояние ленты на сервер

    //Serial.println("STRIP_STATE_START:" + String(message.c_str()) + ":STRIP_STATE_END");

    if (millis() - lastUpdate >= 500 && streamState) {

        updated = false;
        lastUpdate = millis();

        JsonDocument doc;
        JsonObject sendState = doc.add<JsonObject>();
        sendState["stripState"] = message;
        appex.message("updateState", sendState);
    }

    delete message;
}