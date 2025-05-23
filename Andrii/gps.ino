// written by Andrii
// slightly modified code for the gps module from the library example
#include "SparkFun_Ublox_Arduino_Library.h"
SFE_UBLOX_GPS myGPS;

long lastTime = 0;

void setup()
{
  Serial.begin(9600);
  while (!Serial); //Wait for user to open terminal
  Serial.println("SparkFun Ublox Example");

  Wire.begin();

  if (myGPS.begin() == false)
  {
    Serial.println(F("Ublox GPS not detected at default I2C address. Please check wiring. Freezing."));
    while (1);
  }

  myGPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)

}

void loop()
{
  if (millis() - lastTime > 1000)
  {
    lastTime = millis(); //Update the timer
    
    long latitude = myGPS.getLatitude();
    Serial.print(F("Lat: "));
    Serial.print(latitude);

    long longitude = myGPS.getLongitude();
    Serial.print(F(" Long: "));
    Serial.print(longitude);
    Serial.print(F(" (degrees)"));

    long altitude = myGPS.getAltitude();
    Serial.print(F(" Alt: "));
    Serial.print(altitude);
    Serial.print(F(" (mm)"));

    byte SIV = myGPS.getSIV(); // SIV - Satellites in View
    Serial.print(F(" SIV: "));
    Serial.print(SIV);

    Serial.println();
    Serial.print(myGPS.getYear());
    Serial.print("-");
    Serial.print(myGPS.getMonth());
    Serial.print("-");
    Serial.print(myGPS.getDay());
    Serial.print(" ");
    Serial.print(myGPS.getHour());
    Serial.print(":");
    Serial.print(myGPS.getMinute());
    Serial.print(":");
    Serial.println(myGPS.getSecond());
    
    Serial.println();
  }
}
