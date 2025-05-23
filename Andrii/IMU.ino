// written by Andrii
// slightly modified code for the gps module from the library example"
#include "ICM_20948.h"
ICM_20948_I2C myICM;

void setup()
{
  Serial.begin(9600);
  while (!Serial); //Wait for user to open terminal

  Wire.begin();
  myICM.begin(Wire, true);
}

float find_angle(float x, float y){
  float result_ = atan(abs(x)/abs(y))*180/3.1415;
  if (y < 0){
    result_ = 180 - result_;
  }
  if (x < 0){
    result_ = 360 - result_;
  }
  return result_;
}

void loop()
{
  if (millis() - lastTime > 1000)
  {
    lastTime = millis(); //Update the timer

    myICM.getAGMT();
    Serial.print("Angle: ");
    Serial.println(find_angle(myICM.magX(), myICM.magY()));
  }
}
