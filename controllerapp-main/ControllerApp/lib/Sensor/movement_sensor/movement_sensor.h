#pragma once

#ifndef MOVEMENT_SENSOR_H
#define MOVEMENT_SENSOR_H

#include "../sensor.h"

class MovementSensor : public Sensor {
public:
    MovementSensor(const int& pin);
    ~MovementSensor();

    bool isMotionDetected();
private:
    int _pin;
};

#endif // MOVEMENT_SENSOR_H
