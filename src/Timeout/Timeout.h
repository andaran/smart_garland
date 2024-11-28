#pragma once

#include <functional>
#include <vector>
#include <utility>
#include <Arduino.h>

// Класс для управления задачами с отложенным выполнением
class Timeout {
public:
    static Timeout& getInstance();

    void setTimeout(unsigned duration, std::function<void()> callback);
    void tick();

    Timeout(const Timeout&) = delete;
    Timeout& operator=(const Timeout&) = delete;

private:
    Timeout();
    std::vector<std::pair<unsigned long, std::function<void()>>> timeouts;
};
