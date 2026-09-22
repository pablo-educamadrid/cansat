#include <SoftwareSerial.h>
#include <TinyGPS.h>
//GPS   |  Arduino
// Vcc  |   5v
//  Tx  |   13 (rx)
// GND  |   GND

TinyGPS gps;
const byte rxPinGPS = 13;
const byte txPinGPS = 12;
SoftwareSerial ss(rxPinGPS, txPinGPS);

void setup()
{
  Serial.begin(9600);
  ss.begin(9600);
  
  Serial.print("Simple TinyGPS library v. "); Serial.println(TinyGPS::library_version());
  Serial.println();
}

void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);//String lat=String( flat, 8);
    Serial.println(lat);
    
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    Serial.print(" ALT=");
    Serial.print((float)gps.altitude()/100); 
    Serial.print(" TIME=");
    int year;

    byte month, day, hour, minute, second, hundredths;
    gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
    Serial.print("Fecha: "); 
    Serial.print(day, DEC); 
    Serial.print("/");
     Serial.print(month, DEC); 
     Serial.print("/"); 
     Serial.print(year);
      Serial.print(" Hora: "); 
      Serial.print(hour, DEC); 
      Serial.print(":"); 
      Serial.print(minute, DEC); 
      Serial.print(":"); 
      Serial.print(second, DEC); 
  }
  
  gps.stats(&chars, &sentences, &failed);
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  if (chars == 0)
    Serial.println("** No characters received from GPS: check wiring **");
}