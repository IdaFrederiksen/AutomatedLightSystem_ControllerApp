#include <Arduino.h>
#include "UARTHandler.h"

bool UARTHandler::receiveData()
{
    const int PACKET_SIZE = 6;
    uint8_t data[6];
    if (Serial.available() >= PACKET_SIZE)
    {
        Serial.readBytes(data, PACKET_SIZE);

        uint8_t calculatedChecksum = 0;
        for (int i = 0; i < 5; ++i)
        {
            calculatedChecksum += data[i]; // Simple summation checksum
        }
        if (calculatedChecksum == data[5])
        {
            zoneNr = data[0];
            brightness = data[1];
            redVal = data[2];
            greenVal = data[3];
            blueVal = data[4];
            Serial.write(170); // ACK or NACK header
            Serial.print("A");
            return true;
        }
        else
        {
            Serial.write(170); // ACK or NACK header
            Serial.print("N");
            return false;
        }
    }
    return false;
}
void UARTHandler::sendData(const uint8_t* params)
{
    // We expect 5 bytes of data (Zone, Brightness, R, G, B)
    const int PAYLOAD_SIZE = 17;

    // Array size is payload + 1 byte for checksum
    uint8_t data[PAYLOAD_SIZE + 1];
    uint8_t checksum = 0;

    // Copy payload and calculate checksum
    for (int i = 0; i < PAYLOAD_SIZE; ++i)
    {
        data[i] = params[i];
        checksum += params[i];
    }

    // Add checksum at the end
    data[PAYLOAD_SIZE] = checksum;

    // Send the full packet (Payload + Checksum)
    Serial.write(data, PAYLOAD_SIZE + 1);
}
