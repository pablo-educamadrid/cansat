#include <Adafruit_BME280.h>
#include <SoftwareSerial.h>

  unsigned long now;

const byte rxPin = 2;
const byte txPin = 3;

Adafruit_BME280 bme; // I2C

SoftwareSerial apc (rxPin, txPin);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   apc.begin(9600);
   if (!bme.begin()) {  
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
    Serial.println("[segundo],[temperatura],[humedad],[persión atmosférica],nombre del equipo");

}

void loop() {
  // put your main code here, to run repeatedly:
  static unsigned long timer = 0;
  unsigned long interval = 1000;
  now = millis();
   if(now - timer >= interval)
  {
  
      timer = millis();
     Serial.print(now/1000);
     apc.println(now/1000);
    Serial.print(",");
    Serial.print(bme.readTemperature());
    Serial.print(",");
    Serial.print(bme.readHumidity());
    Serial.print(",");
    Serial.print(bme.readPressure());
    Serial.print(",");
    Serial.println("Blue rocket");
  }

    //Serial.println("Blue rocket");

  
  delay(1000);
}

/*
 * 
 * 1,22.42,52.26,93472.91,blue rocket
 * 
 * 
 * 
 * 
 */
