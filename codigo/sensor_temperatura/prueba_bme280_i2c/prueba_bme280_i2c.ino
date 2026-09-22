#include <Adafruit_BME280.h>





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
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("");
  Serial.print("Temp: ");
  Serial.println(bme.readTemperature());
  Serial.print("pressure: ");
  Serial.println(bme.readPressure());
  Serial.print("humidity: ");
  Serial.println(bme.readHumidity());
  Serial.println("");
  Serial.println("");

  
  delay(1500);
}
