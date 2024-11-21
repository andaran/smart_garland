#pragma once

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>
#include <string>
#include <unordered_map>

class AppexConnector {
private:
    String roomID;
    String roomPass;
    JsonObject & state;
    std::function<void()> callback;

    SocketIOclient socketIO;

    void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length);
    void parseEvent(char* json);

public:
    AppexConnector(String roomID, 
                   String roomPass,
                   JsonObject & state,
                   std::function<void()> callback);

    void connectToRoom();
    void message(const char* eventType, const std::vector<String>& params);
    void update(const std::vector<String>& params);
    void setup();
    void tick();
};
