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
  Serial.println("[segundo],[temperatura],[humedad],[persión atmosférica],[lat],[lon],[n sats],[hdop precision],[altitude],[GPS date],[GPS time],[nombre del equipo]");

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

  gps.stats(&chars, &sentences, &failed);

  if (newData)
  {
    gpsData = "";
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    gpsData += flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6; //append lat
    gpsData += ",";//

    
    gpsData += flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6; //append lon
    gpsData += ",";//

    gpsData += gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites(); //number of satellites
    gpsData += ",";//

    gpsData += gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop(); //number of precision
    gpsData += ",";//

    gpsData += (float)gps.altitude()/100; //altidude (m)
    gpsData += ",";//


    int year;
    byte month, day, hour, minute, second, hundredths;
    gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);

    gpsData += day, DEC;
    gpsData +=  "/";
    gpsData +=  month, DEC;
    gpsData += "/";
    gpsData += year; //date dd/mm/yyyy
    gpsData += ",";//
    gpsData += hour, DEC;
    gpsData += ":";
    gpsData += minute, DEC;
    gpsData += ":";
    gpsData += second, DEC; //date dd/mm/yyyy
    gpsData += ",";//

  } else {
    //no new data
    //lat,lon,n sats, hdop precision, altitude, GPS date, GPS time
    if(chars == 0){
      gpsData = "check connection no chars,-,-,-,-,-,-,";
    } else{
      gpsData = "NO GPS YET";
      gpsData += chars;
      gpsData += ",-,-,-,-,-,";
    }
  
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

    generalData += gpsData;

    generalData +="Blue rocket";// append pressure
  
    //send data to usb
    Serial.println(generalData);

    //send dato to radio
    apc.println(generalData);
    
  
}

