#include "Timeout.h"

Timeout& Timeout::getInstance() {
    static Timeout instance;
    return instance;
}

Timeout::Timeout() = default;

void Timeout::setTimeout(unsigned duration, std::function<void()> callback) {
    timeouts.emplace_back(millis() + duration, callback);
}

void Timeout::tick() {
    unsigned long currentTime = millis();
    auto it = timeouts.begin();

    while (it != timeouts.end()) {
        if (currentTime >= it->first) {
            it->second();
            it = timeouts.erase(it);
        } else {
            ++it;
        }
    }
}