#pragma once
#include <Arduino.h>

class UARTHandler {
    public:
        uint8_t zoneNr{0}, brightness{155}, redVal{100}, greenVal{0}, blueVal{0}, checksum{255};
        bool receiveData();
        void sendData(const uint8_t* params);
};