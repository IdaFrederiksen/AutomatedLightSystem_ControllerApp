#pragma once

#ifndef ZONE_H
#define ZONE_H

#include <artificial_light.h>
#include <movement_sensor/movement_sensor.h>
#include <light_sensor/multiplex.h>
#include <light_sensor/light_sensor.h>
#include <Arduino.h>

struct Settings {
    Color color;
    int luxThreshold;
};

class Zone {
public:
    Zone(int zoneId, String zoneName, int lightPin, int sensorPin, multiplex& tca, uint8_t lightSensorPort);
    ~Zone();
    void updateLightLevel(int lightLevel);
    void updateLightColor(Color color);
    void manageLight();
    bool isLightOn() const;
    float getLuxLevel() const;
private:
    int id;
    String name;
    ArtificialLight* light;
    MovementSensor* sensor;
    LightSensor* lightSensor;
    Settings settings;

    unsigned int targetBrightness;
    unsigned long lastBrightnessUpdate;
    const int brightnessStep = 1;
    const unsigned long brightnessUpdateInterval = 100;

    unsigned long lastMotionTime;
    const unsigned long motionTimeout = 30000;

    unsigned long lastLightSensorRead;
    const unsigned long lightSensorInterval = 1;
    float cachedLux;
    void updateBrightnessSmooth();
};

#endif // ZONE_H
