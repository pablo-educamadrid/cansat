#include <Adafruit_BME280.h>
#include <SoftwareSerial.h>

#include <SoftwareSerial.h>

#include <TinyGPS.h>



unsigned long now;



//modulo de radio apc220
const byte rxPin = 2;
const byte txPin = 3;
SoftwareSerial apc (rxPin, txPin);



//sensor de temperatura y presion 
Adafruit_BME280 bme; // I2C

//GPS
TinyGPS gps;
const byte rxPinGPS = 13;
const byte txPinGPS = 12;
SoftwareSerial ss(rxPinGPS, txPinGPS);



//DATA
String generalData = "";
String gpsData = "";


void setup() {
  //conexion USB
  Serial.begin(9600);

  //conexion radio
  apc.begin(9600);

  //inicializacion sensor temperatura
   if (!bme.begin()) {  
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  //GPS
  ss.begin(9600);

  //cabecera dato csv
  Serial.println("[segundo],[temperatura],[humedad],[persión atmosférica],[nombre del equipo]");

}

void loop() {
  //GPS
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
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
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
  if (chars == 0){
    Serial.println("** No characters received from GPS: check wiring **");
  }

    generalData = ""; //start with an empty string
    generalData += millis();// append time
    generalData += ",";// append ,
    
    generalData += bme.readTemperature();// append temp
    generalData += ",";// append 

    generalData += bme.readHumidity();// append humidity
    generalData += ",";// append 

    generalData += bme.readPressure();// append pressure
    generalData += ",";// append 
    generalData +="Blue rocket";// append pressure
    generalData += ",";// append 
  

    Serial.print(generalData);
    apc.println(generalData);
    
  
}

/*
 * 
 * 1,22.42,52.26,93472.91,blue rocket
 * 
 * 
 * 
 * 
 */
