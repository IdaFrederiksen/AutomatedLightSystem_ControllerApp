#pragma once
#ifndef MULTIPLEX_H


#include <Arduino.h>
#include <Wire.h>

class multiplex {
    public:
    multiplex(uint8_t tcaAddr);

    void init();
    uint8_t getPort() const;
    void selectPort(uint8_t port);

    private:
    uint8_t _tcaAddr;
    
};
#endif //MULTIPLEX_H