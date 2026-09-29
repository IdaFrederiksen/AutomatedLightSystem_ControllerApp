#include "light_sensor.h"

LightSensor::LightSensor(multiplex& tca, uint8_t port) : _tca(tca), _port(port), _sensor(){
}

bool LightSensor::init(){
    _tca.selectPort(_port);
    delay(100);

    if(!_sensor.begin()){
        return false;
    }

    _sensor.setGain(TSL2591_GAIN_LOW);
    _sensor.setTiming(TSL2591_INTEGRATIONTIME_100MS);

    return true;       
}

float LightSensor::lightLevel() {
    _tca.selectPort( _port);
    delay(50);

    uint32_t lum = _sensor.getFullLuminosity();
    uint16_t ir   = lum >> 16;
    uint16_t full = lum & 0xFFFF;

    //Vigtigt calculate lux returnerer float og ikke unit32_t
    float lux = _sensor.calculateLux(full, ir);

    return lux;
}