#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2591.h>

#include "multiplex.h"
#include "../sensor.h"


class LightSensor :public Sensor {
    public:
    LightSensor(multiplex& tca, uint8_t port);

    bool init();
    float lightLevel();

    private:
    multiplex& _tca;
    uint8_t _port;
    Adafruit_TSL2591 _sensor;

};
#endif //LIGHTSENSOR_H