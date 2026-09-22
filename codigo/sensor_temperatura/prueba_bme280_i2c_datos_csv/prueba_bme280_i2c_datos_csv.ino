#include <Adafruit_BME280.h>




/*

|     Arduino      |   BME280     |
-----------------------------------
|        A5        | SCL  - SCK  |
|        A4        | SDA -  SDI

*/
Adafruit_BME280 bme; // I2C


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  
  Serial.println("bme status......   ");
  boolean bme280Status = bme.begin();
  Serial.println(bme280Status);

  if (!bme280Status) {  
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  } else {
    Serial.println("sensor ok.");
    Serial.println("[segundo],[temperatura],[humedad],[persión atmosférica],nombre del equipo");
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print((float)millis()/1000);
  Serial.print(",");
  Serial.print(bme.readTemperature());
  Serial.print(",");
  Serial.print(bme.readHumidity());
  Serial.print(",");
  Serial.print(bme.readPressure());
  Serial.print(",");
  Serial.println("CanSatIESGPB");

  delay(1000);
}
