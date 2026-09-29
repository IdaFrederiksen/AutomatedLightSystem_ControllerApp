#include "Wire.h" 

void setup() { 
    Serial.begin(9600); 
    delay(1000); 
    Wire.begin(); 
     
    Serial.println("Testing TCA9548A..."); 
    Wire.beginTransmission(0x70); 
    uint8_t error = Wire.endTransmission(); 
    

    if (error == 0) { 
        Serial.println("TCA9548A responds!"); 
    } else { 
        Serial.println("TCA9548A NOT found!"); 
        Serial.print("Error code: "); 
        Serial.println(error); 
    } 
} 

void loop() {}