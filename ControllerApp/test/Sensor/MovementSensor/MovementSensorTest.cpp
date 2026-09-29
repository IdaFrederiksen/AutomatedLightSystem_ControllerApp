#include "MovementSensorTest.h"

MovementSensorTest::MovementSensorTest()
{
}

MovementSensorTest::~MovementSensorTest()
{
}

void MovementSensorTest::testIsMotionDetected() {
    MovementSensor sensor1(MOVEMENT_SENSOR_PIN1);
    if (sensor1.isMotionDetected()) {
        Serial.print("Motion detected on sensor 1\n");
    }
    else {
        Serial.print("Motion detected on sensor 0\n");
    }
    delay(1000);
}
