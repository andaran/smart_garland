#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#include "settings.h"
#include "AppexConnector/AppexConnector.h"
#include "CmdsProcessor/CmdsProcessor.h"
#include "EffectsProcessor/EffectsProcessor.h"
#include "Strip/StripProcessor.h"

Adafruit_NeoPixel * ledStrip = new Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void appexCallback();
void stripCallback(char* message);

JsonDocument jsonDoc;
JsonObject state = jsonDoc.add<JsonObject>();

bool stripState = true;
byte streamState = 0;

AppexConnector appex(roomIDSetting, roomPassSetting, state, appexCallback);

StripProcessor * strip = new StripProcessor(ledStrip, stripCallback);
EffectsProcessor * effectsProcessor = new EffectsProcessor(strip);
CmdsProcessor cmdsProcessor(effectsProcessor, strip, state, 
                            stripState, streamState);

void setup() {
    // Начальное состояние
    state["cmdToEsp"] = "";
    state["ansFromEsp"] = "";
    state["cmdId"] = -1;
    state["stripState"] = "";
    state["lastChange"] = 0;

    // Инициализируем EEPROM
    EEPROM.begin(512);

    // запускаем Serial порт
    Serial.begin(115200);
    Serial.setDebugOutput(false);

    // настраиваем ленту
    strip->begin();

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

int cmdId = -1;
bool updated = true;
void appexCallback() {
    updated = true;

    int id = state["cmdId"];
    if (id == cmdId) {
        return;
    }
    if (cmdId == -1) {
        cmdId = 0;
        state["cmdId"] = cmdId;
        appex.update({"cmdId"});
        return;
    }

    cmdId = id;
    String ans = cmdsProcessor.processCmds(state["cmdToEsp"].as<String>());

    state["ansFromEsp"] = ans;
    appex.update({"ansFromEsp"});

    state["ansFromEsp"] = "[" + String(cmdId) + "]";
    appex.update({"ansFromEsp"});

    Serial.print("> ");
    Serial.println(state["cmdToEsp"].as<String>());
    Serial.println(ans);
}

unsigned long lastUpdate = 0;
void stripCallback(char* message) {
    // Стримим состояние ленты

    if (streamState == 1 && millis() - lastUpdate >= 500 && updated) {
        updated = false;
        lastUpdate = millis();

        state["stripState"] = message;
        appex.update({"stripState"});
    }
    if (streamState == 2 && millis() - lastUpdate >= 100) {
        lastUpdate = millis();
        Serial.print("STRIP_STATE_START:" + String(message) + ":STRIP_STATE_END");
    }

    delete message;
}