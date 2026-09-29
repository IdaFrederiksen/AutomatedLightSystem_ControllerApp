#include <Arduino.h>
#include <light_sensor/light_sensor.h>
#include <light_sensor/multiplex.h>
multiplex tca(0x70);

LightSensor sensor0(tca,0);
LightSensor sensor1(tca,1);
LightSensor sensor2(tca,2);

void setup(){
  Serial.begin(9600);
  delay(500);

  Serial.println("\nInitializing sensors...");

   bool fail = false;

  if (!sensor0.init()) { Serial.println("Sensor på port 0 ikke fundet"); fail = true; }
  if (!sensor1.init()) { Serial.println("Sensor på port 1 ikke fundet"); fail = true; }
  if (!sensor2.init()) { Serial.println("Sensor på port 2 ikke fundet"); fail = true; }

  if (fail)
      Serial.println("Ingen sensorer fundet!");
  else
      Serial.println("Lyssensorer initialiseret.");
}



void loop() {
  Serial.print("Port 0: "); Serial.println(sensor0.lightLevel());
  Serial.print("Port 1: "); Serial.println(sensor1.lightLevel());
  Serial.print("Port 2: "); Serial.println(sensor2.lightLevel());

  Serial.println("---");
  delay(1000);
}