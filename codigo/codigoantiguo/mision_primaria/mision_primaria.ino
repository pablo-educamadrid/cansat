#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Adafruit_BME280.h>


Adafruit_BME280 bme; // I2C

TinyGPS gps;
const byte rxPinGPS = 13;
const byte txPinGPS = 12;
SoftwareSerial ss(rxPinGPS, txPinGPS);


const byte rxPinAPC = 2;
const byte txPinAPC = 3;

// Set up a new SoftwareSerial object
SoftwareSerial apc(rxPinAPC, txPinAPC);


String gps_values = "";
String bme_values = "";
String values; 


void setup()
{

  Serial.println("IES-GPB");
  Serial.println("CanSat 2024");

  //USB serial port
  Serial.begin(9600);

  //GPS 
  ss.begin(9600);


  //APC220 Radio module
  apc.begin(9600);



  //temperature sensor
  Serial.println("bme status......   ");
  boolean bme280Status = bme.begin();
  Serial.println(bme280Status);

  if (!bme280Status) {  
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  } else {
    Serial.println("sensor ok.");
  }

  Serial.println("sensor ok.");

  Serial.println("[time in seconds],[lat],[long],[n satellites],[altitude],[gps date],[gps time],[temp],[pressure],[humidity]");
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
    gps_values = "";
    gps_values += flat;
    gps_values += ",";
    gps_values += flon;
    gps_values += ",";


    gps_values += gps.satellites();
    gps_values += ",";
    gps_values += (float)gps.altitude()/100;
    gps_values += ",";
    
    int year;
    byte month, day, hour, minute, second, hundredths;
    gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);

    gps_values += day;
    gps_values += "/";
    gps_values += month;
    gps_values += "/";
    gps_values += year;
    gps_values += ",";

    gps_values += hour;
    gps_values += ":";
    gps_values += minute;
    gps_values += ":";
    gps_values += second;
    gps_values += "-UTC,";

  } else {
    gps_values = "-,-,-,-,-,-,";
  }

  //BME280
  bme_values = "";
  bme_values += bme.readTemperature();
  bme_values += ",";
  bme_values += bme.readPressure();
  bme_values += ",";
  bme_values += bme.readHumidity();
  bme_values += ",";






  values = "";
  values += (float)millis()/1000;
  values += ",";
  values += gps_values;
  values += bme_values;

  Serial.println(values);
  apc.println(values);
}