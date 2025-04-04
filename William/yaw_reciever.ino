// // Include the required Wire library for I2C<br>
 #include  <Wire.h>

void setup() {
//   // Start the I2C Bus as Master
   Serial.begin(9600);
   Wire.begin(9); 
   Wire.onReceive(receiveEvent);
}
int FinalYaw = 0;
void receiveEvent(int bytes) {
  
   int Yaw = Wire.read();    // read one character from the I2C
   int Yaw2 = Wire.read();
   if(Yaw2 > 0){
    FinalYaw = Yaw2 + 256;
   }
   else{
    FinalYaw = Yaw;
   }
   //Serial.print(Yaw);
   //Serial.print("        ");
   //Serial.println(Yaw2);
   Serial.println(FinalYaw);
 }
void loop() {
  //Wire.requestFrom(9, 2);     // request 2 bytes from slave device #2

  //  while(Wire.available())    // slave may send less than requested
  // { 
  //    int x = Wire.read();         
  //    int y = Wire.read();         
  //    int z = y * 256 + x;
  //    Serial.println(z);
  // }
}
