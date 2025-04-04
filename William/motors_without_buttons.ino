// C++ code
// declare variables
const int forwardPin = 8;
const int backwardPin = 12;
const int forwardPin2 = 9;
const int backwardPin2 = 13;
const int DelayTime = 2000;
const int speedPin = 11;
int speed;

void setup()
{
  Serial.begin(9600);
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
  pinMode(forwardPin2, OUTPUT);
  pinMode(backwardPin2, OUTPUT);
  speed = 250;
  analogWrite(speedPin,speed);
}

void loop()
{
  digitalWrite(forwardPin,LOW);
  digitalWrite(forwardPin2,LOW);
  delay(500);
  digitalWrite(forwardPin,HIGH);
  digitalWrite(forwardPin2,HIGH);
  delay(500);
  digitalWrite(backwardPin,LOW);
  digitalWrite(backwardPin2,LOW);
  delay(500);
  digitalWrite(backwardPin,HIGH);
  digitalWrite(backwardPin2,HIGH);
  delay(500);
  
}
