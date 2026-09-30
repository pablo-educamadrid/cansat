#include <Adafruit_BMP280.h>


Adafruit_BMP280 bmp; // I2C

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  
  Serial.println("bmp status......   ");
  boolean bmp280Status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  Serial.println(bmp280Status);

  if (!bmp280Status) {  
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
  Serial.println(bmp.readTemperature());
  Serial.print("pressure: ");
  Serial.println(bmp.readPressure());

  Serial.println("");
  Serial.println("");

  
  delay(1500);
}