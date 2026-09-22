#include<Wire.h>
const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int secs=0;

/* GY-521     | Arduino
----------------------------------------
 * scl        |   A5
 * sda        |   A4
 * Vcc        |  5V4
 * GND        |   -   GND
 * 
 * */





void  setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);
  Serial.println("[Ax,Ay,Az,Gx,Gy,Gz]");


}



void  loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  
  
  /*Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = ");  Serial.println(AcZ); 
  
  Serial.print("Gyroscope: ");
  Serial.print("X  = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");*/
  String text = "";

  secs =  millis()/1000;
  text = "";
  text += secs;
    text += ","; 

  text += "AcX,";
  text += AcX;
  text += ","; 
  text += "AcY, ";
  text += AcY;
  text += ","; 
  text += "AcZ,";
  text += AcZ;
  Serial.println(text);



  delay(1000);
}
