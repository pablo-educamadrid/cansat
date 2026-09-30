/***************************************
    Conexionado Arduino


-------------------------------------
|PIN ARDUINO        |   PIN APC220  |
-------------------------------------
|   GND             |     GND       |
|   +5              |     VIN       |
|   +5              |     EN        |
|   PIN 3 (TX)      |     VIN       |
-------------------------------------


*****************************************/



#include <SoftwareSerial.h>




const byte rxPin = 2;
const byte txPin = 3;

// Set up a new SoftwareSerial object
SoftwareSerial apc (rxPin, txPin);


void setup()
{
   Serial.begin(9600);
   apc.begin(9600);
}

void loop()
{
  unsigned long now = millis();
  static unsigned long timer = 0;
  unsigned long interval = 1000;
  if(now - timer >= interval)
  {
   timer = millis();
   Serial.print("Sending USB ");
   Serial.println(now/1000);
   apc.print("Sending APC ");
   apc.println(now/1000);
  }
  
  if(apc.available() > 0)
  {
   Serial.print(char(apc.read()));
  }
}