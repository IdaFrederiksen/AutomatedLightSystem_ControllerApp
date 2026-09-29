#include "artificial_light.h"

ArtificialLight::ArtificialLight(int pin) : _pin(pin), strip(LED_COUNT, _pin, NEO_GRB + NEO_KHZ800)
{
    strip.begin();
    state = false;
    brightness = 0;
    color = {255, 255, 255};
}

void ArtificialLight::turnOn()
{
    if (state) {
        return;
    }

    state = true;
    strip.setBrightness(brightness);
    // Apply current color to all pixels
    for (int i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, strip.Color(color.red, color.green, color.blue));
    }
    strip.show();
}

void ArtificialLight::turnOff()
{
    if (!state) {
        return;
    }

    state = false;
    strip.setBrightness(0);
    strip.show();
}

bool ArtificialLight::isOn() const
{
    return state;
}

int ArtificialLight::getBrightness() const
{
    return brightness;
}

bool ArtificialLight::changeLightLevel(int level)
{
    if (level < 0 || level > 255) {
        return false;
    }
    brightness = level;
    if (state) {
        strip.setBrightness(brightness);
        for (int i = 0; i < LED_COUNT; i++) {
            strip.setPixelColor(i, strip.Color(color.red, color.green, color.blue));
        }
        strip.show();
    }
    return true;
}

bool ArtificialLight::changeLightColor(Color color)
{
    this->color = color;
    if (state) {
        for (int i = 0; i < LED_COUNT; i++) {
            strip.setPixelColor(i, strip.Color(color.red, color.green, color.blue));
        }
        strip.show();
    }
    return true;
}
