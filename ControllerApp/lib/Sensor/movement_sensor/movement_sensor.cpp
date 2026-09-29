#include "movement_sensor.h"
#include <Arduino.h>

MovementSensor::MovementSensor(const int& pin) : _pin(pin)
{
    pinMode(_pin, INPUT);
}

MovementSensor::~MovementSensor()
{
}

bool MovementSensor::isMotionDetected()
{
    int sensorValue = digitalRead(_pin);
    if (sensorValue == HIGH) {
        return true;
    }
    return false;
}
