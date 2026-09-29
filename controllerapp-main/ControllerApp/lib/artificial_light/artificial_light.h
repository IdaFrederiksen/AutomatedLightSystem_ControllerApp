#pragma once

#ifndef ARTIFFICIAL_LIGHT_H
#define ARTIFFICIAL_LIGHT_H

#include <Adafruit_NeoPixel.h>

#define LED_COUNT 16

struct Color {
    int red;
    int green;
    int blue;
};

class ArtificialLight {
public:
    ArtificialLight(int pin);
    void turnOn();
    void turnOff();
    bool isOn() const;
    int getBrightness() const;
    bool changeLightLevel(int level);
    bool changeLightColor(Color color);
    Color getLightColor() const {
        return color;
    }
private:
    bool state;
    int brightness;
    Color color;
    int _pin;
    Adafruit_NeoPixel strip;
};

#endif // ARTIFICIAL_LIGHT_H
