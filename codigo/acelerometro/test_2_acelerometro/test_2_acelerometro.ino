#include <Wire.h>

const int MPU = 0x68; // Dirección I2C del MPU6050

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Registro de lectura de acelerómetro
  Wire.endTransmission();
  Wire.requestFrom(MPU, 6); // Leer 6 bytes de datos
  while(Wire.available()) {
    int data = Wire.read();
    Serial.print("Aceleración X: ");
    Serial.print(data, DEC);
    Serial.print(" | Aceleración Y: ");
    data = Wire.read();
    Serial.print(data, DEC);
    Serial.print(" | Aceleración Z: ");
    data = Wire.read();
    Serial.println(data, DEC);
  }
  delay(1000);
}
