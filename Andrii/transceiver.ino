// written by Andrii
// slightly modified code for the gps module from the library example
#include "RF24.h"
RF24 radio(10, 9);

// radio stuff
byte address[][6] = {"1Node","2Node","3Node","4Node","5Node","6Node"};
bool transmitter = 1; // a boolean indicating whether this module is a transmitter (1) or a receiver (0)
byte pipeNo, gotByte;
double package_number, data[7];

void setup()
{
  Serial.begin(9600);
  setup_radio();

}

void setup_radio(){
  radio.begin();
  radio.setAutoAck(1); // Automatically acknowledge received messages
  radio.setRetries(0,15);  // Time between and number of attempts of sending a message
  radio.enableAckPayload();   // Enable sending data as an acknowledgemt of receivement
  radio.setPayloadSize(64);     // Package size in bytes
  if (transmitter){radio.openWritingPipe(address[0]);}  // Writing to Address 0
  else{radio.openReadingPipe(1, address[0]);}       // Listening to Address 0
  
  radio.setChannel(0x60);  // Choosing Channel

  radio.setPALevel (RF24_PA_MAX); //Power Level, RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); //Transfer speed, lower speed grants larger distances, RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  
  radio.powerUp();
  if (transmitter){radio.stopListening();}
  else{radio.startListening();}
}

void send_data(long latitude_, long longitude_, float angle_, float winch_status_, float pH_, float turn_angle_){
  //debug data
  Serial.print("Sending... ");
  Serial.print("  Longitude: ");
  Serial.print(latitude_);
  Serial.print("  Latitude: ");
  Serial.print(longitude_);
  Serial.print("  Angle: ");
  Serial.print(angle_);
  Serial.print("  Winch: ");
  Serial.print(winch_status_);
  Serial.print("  pH: ");
  Serial.println(pH_);

  //setting up the array
  data[0] += 1;
  data[1] = latitude_;
  data[2] = longitude_;
  data[3] = angle_;
  data[4] = winch_status_;
  data[5] = pH_;
  data[6] = turn_angle_;

  // transmitting the array
  radio.write(&data, sizeof(data));
}

void loop()
{
  if (millis() - lastTime > 1000)
  {
    // data = [latitude, longitude, angle, winch status, pH, turn_angle]
    send_data(536719842, -158127524, 120.1, 1.0, 7.0, 17.0);
  }
}
