// NRF24L01 data sending/receiving, adapted from the example code from the NRF24L01 library
#include <SPI.h>
#include "nRF24L01.h"

RF24 radio(9,10);

byte address[][6] = {"1Node","2Node","3Node","4Node","5Node","6Node"};
bool transmitter = 0; // a boolean indicating whether this module is a transmitter (1) or a receiver (0)
byte pipeNo, gotByte;

void setup(){
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(1); // Automatically acknowledge received messages
  radio.setRetries(0,15);  // Time between and number of attempts of sending a message
  radio.enableAckPayload();   // Enable sending data as an acknowledgemt of receivement
  radio.setPayloadSize(32);     // Package size in bytes
  if (transmitter){radio.openWritingPipe(1, address[0]);}  // Writing to Address 0
  else{radio.openReadingPipe(1,address[0]);}       // Listening to Address 0
  
  radio.setChannel(0x60);  // Choosing Channel

  radio.setPALevel (RF24_PA_MAX); //Power Level, RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); //Transfer speed, lower speed grants larger distances, RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  
  radio.powerUp();
  if (transmitter){radio.stopListenint();}
  else{radio.startListening();}
}

void loop(void) {
  if (transmitter){
    Serial.print("Sent: "); Serial.println(counter);
    radio.write(&counter, sizeof(counter));
    counter++;
    delay(10);
    
  }
  else{
    while( radio.available(&pipeNo)){
      radio.read( &gotByte, sizeof(gotByte) );

      Serial.print("Recieved: "); Serial.println(gotByte);
    }
  }
}


