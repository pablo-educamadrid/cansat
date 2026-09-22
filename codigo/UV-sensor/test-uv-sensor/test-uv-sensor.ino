/***************************************
    Conexionado Arduino


---------------------------------------
|PIN ARDUINO        | PIN GUVA-S12SD  |
---------------------------------------
|   GND             |       GND       |
|   +5              |       Vcc       |
|   A0              |        S        |
---------------------------------------


*****************************************/



void setup()
{
   Serial.begin(9600);
}

void loop()
{
    Serial.print("Value: ");
    Serial.println(analogRead(A0));
    Serial.println(millis()/1000);
    delay(1000);
}