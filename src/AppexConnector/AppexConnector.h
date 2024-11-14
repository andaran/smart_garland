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
    std::unordered_map<std::string, std::string> & state;
    std::function<void(std::unordered_map<std::string, std::string>&)> callback;

    SocketIOclient socketIO;

    void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length);
    void parseEvent(char* json);

public:
    AppexConnector(String roomID, 
                   String roomPass,
                   std::unordered_map<std::string, std::string> & state,
                   std::function<void(std::unordered_map<std::string, std::string>&)> callback);

    void connectToRoom();
    void message(String eventType, JsonObject sendState);
    void setup();
    void tick();
};
