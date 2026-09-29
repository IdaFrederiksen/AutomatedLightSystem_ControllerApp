#pragma once

#ifndef MOVEMENT_SENSOR_TEST_H
#define MOVEMENT_SENSOR_TEST_H

#include <Arduino.h>
#include <movement_sensor/movement_sensor.h>


const int MOVEMENT_SENSOR_PIN1 = 22;
const int MOVEMENT_SENSOR_PIN2 = 23;
const int MOVEMENT_SENSOR_PIN3 = 24;

class MovementSensorTest
{
private:

public:
    MovementSensorTest();
    ~MovementSensorTest();

    void testIsMotionDetected();
};

#endif // MOVEMENT_SENSOR_TEST_H
