#include <Arduino.h>
#include <movement_sensor/movement_sensor.h>
#include "zone/zone.h"
#include "UARTHandler.h"
#include <light_sensor/multiplex.h>

multiplex tca(0x70);

Zone *zones[8]{nullptr};
UARTHandler UART;

unsigned long sendDataCurrentMillis = 0;
const unsigned long dataSendInterval = 1000; // Send data every second


void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        ; // Wait for serial port to connect
    }

    //I2C og multiplexer init
    tca.init();

    zones[0] = new Zone(1, "Living Room", 6, 22, tca, 1);
    zones[1] = new Zone(2, "Bedroom", 7, 23, tca, 4);
    zones[2] = new Zone(3, "Kitchen", 8, 24, tca, 5);

    zones[0]->updateLightColor({255, 255, 255});
    zones[1]->updateLightColor({255, 255, 255});
    zones[2]->updateLightColor({255, 255, 255});
}

void loop()
{
    if (UART.receiveData())
    {
        if (zones[UART.zoneNr] != nullptr)
        {
            Color newColor = {UART.redVal, UART.greenVal, UART.blueVal};
            zones[UART.zoneNr]->updateLightColor(newColor);
            zones[UART.zoneNr]->updateLightLevel(UART.brightness);

        }
    }

    if (millis() - sendDataCurrentMillis >= dataSendInterval) {
        sendDataCurrentMillis = millis();

        uint8_t onByte = 0;
        for (int i = 0; i < 8; ++i)
        {
            if (zones[i] != nullptr && zones[i]->isLightOn()) {
                onByte |= (1 << i);
            }
        }

        uint8_t packet[17];
        packet[0] = onByte;
        for (int i = 0; i < 8; ++i)
        {
            if (zones[i] != nullptr)
            {
                int luxLevel = (int)zones[i]->getLuxLevel();
                packet[1 + i * 2] = (uint8_t)(luxLevel & 0xFF);
                packet[2 + i * 2] = (uint8_t)((luxLevel >> 8) & 0xFF);
            }
            else
            {
                packet[1 + i * 2] = 0;
                packet[2 + i * 2] = 0;
            }
        }

        UART.sendData(packet);
}

    for (int i = 0; i < 3; ++i)
    {
        if (zones[i] != nullptr)
        {
            zones[i]->manageLight();
        }
    }
}

