#include <zone/zone.h>

Zone::Zone(int zoneId, String zoneName, int lightPin, int sensorPin,multiplex& tca ,uint8_t lightSensorPort)
    : id(zoneId), name(zoneName), targetBrightness(0), lastBrightnessUpdate(0), lastMotionTime(0), lastLightSensorRead(0), cachedLux(0)
{
    light = new ArtificialLight(lightPin);
    sensor = new MovementSensor(sensorPin);
    lightSensor = new LightSensor(tca, lightSensorPort);

    settings.color = {255, 255, 255};
    settings.luxThreshold = 0;

    lightSensor->init();
    light->changeLightLevel(settings.luxThreshold);
    light->changeLightColor(settings.color);
    light->turnOn();
}

Zone::~Zone()
{
    delete light;
    delete sensor;
    delete lightSensor;
}

void Zone::updateLightLevel(int lightLevel)
{
    settings.luxThreshold = map(lightLevel, 0, 100, 0, 500);

    if (lightLevel == 0) {
        light->turnOff();
    }
}

void Zone::updateLightColor(Color color)
{
    light->changeLightColor(color);
    settings.color = color;
}

bool Zone::isLightOn() const
{
    return light->isOn();
}

void Zone::updateBrightnessSmooth()
{
    unsigned long currentTime = millis();
    unsigned long timeElapsed = currentTime - lastBrightnessUpdate;

    int stepsToTake = timeElapsed / brightnessUpdateInterval;

    if (stepsToTake > 0) {
        unsigned int currentBrightness = light->getBrightness();

        if (currentBrightness != targetBrightness) {
            int difference = targetBrightness - currentBrightness;

            int totalChange = brightnessStep * stepsToTake;

            int newBrightness;
            if (abs(difference) <= totalChange) {
                newBrightness = targetBrightness;
            } else if (difference > 0) {
                newBrightness = currentBrightness + totalChange;
            } else {
                newBrightness = currentBrightness - totalChange;
            }

            if (newBrightness < 0) {
                newBrightness = 0;
            }
            if (newBrightness > 255) {
                newBrightness = 255;
            }

            light->changeLightLevel(newBrightness);
            lastBrightnessUpdate = currentTime;
        }
    }
}

float Zone::getLuxLevel() const
{
    return cachedLux;
}

void Zone::manageLight()
{
    updateBrightnessSmooth();

    unsigned long currentTime = millis();
    bool motion = sensor->isMotionDetected();

    if (motion) {
        lastMotionTime = currentTime;
    }

    bool lightShouldBeOn = (currentTime - lastMotionTime) < motionTimeout;

    if (currentTime - lastLightSensorRead >= lightSensorInterval) {
        cachedLux = lightSensor->lightLevel();
        lastLightSensorRead = currentTime;
    }

    if (lightShouldBeOn) {
        light->turnOn();

        float luxDifference = settings.luxThreshold - cachedLux;

        float minDeadband = 20.0f;
        float percentDeadband = settings.luxThreshold * 0.25f;
        float hysteresis = (percentDeadband > minDeadband) ? percentDeadband : minDeadband;

        if (luxDifference > hysteresis) {
            int adjustment = (int)((luxDifference - hysteresis) * 0.5f);
            if (adjustment > 10) adjustment = 10;
            if (adjustment < 1) adjustment = 1;

            int newTarget = targetBrightness + adjustment;
            if (newTarget > 255) newTarget = 255;
            targetBrightness = newTarget;

        } else if (luxDifference < -hysteresis) {
            int adjustment = (int)((abs(luxDifference) - hysteresis) * 0.5f);
            if (adjustment > 10) adjustment = 10;
            if (adjustment < 1) adjustment = 1;

            int newTarget = targetBrightness - adjustment;
            if (newTarget < 0) newTarget = 0;
            targetBrightness = newTarget;
        }
    } else {
        targetBrightness = 0;
        if (light->getBrightness() == 0) {
            light->turnOff();
        }
    }
}
