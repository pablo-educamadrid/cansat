/***************************************
    Conexionado Arduino


-------------------------------------------
|PIN ARDUINO         |   PIN GPS          |
-------------------------------------------
|   GND              |     GND            |
|   +5               |     Vcc            |
|   PIN 13 (RX)      |     TX     blanco  |
|   PIN 12 (TX)      |     RX   - verde   |
-------------------------------------------

*****************************************/



#include <SoftwareSerial.h>

const byte rxPinGPS = 13;
const byte txPinGPS = 12;
SoftwareSerial serialGPS(rxPinGPS, txPinGPS);

char data = ' ';
char previousData=' ';

void setup()
{
 Serial.begin(9600);            
 serialGPS.begin(9600); 
}

void loop()
{
  if(serialGPS.available())
  {
    previousData = data;
    data=serialGPS.read();
    
    if ((previousData =='$') && (data == 'G')){
      Serial.println("");
    }
    Serial.print(data);
    delay(50);
  } else {
      Serial.println("No data");
      delay(5000);
  }
}
