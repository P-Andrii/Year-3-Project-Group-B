// C++ code
// declare variables
const int forwardPin = 8;
const int backwardPin = 12;
const int forwardPin2 = 9;
const int backwardPin2 = 13;
const int DelayTime = 2000;
const int but1Pin = 2;
const int but2Pin = 3;
const int speedPin = 11;
int but1;
int but2;
int pot;
int speed;

void setup()
{
  Serial.begin(9600);
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
  pinMode(forwardPin2, OUTPUT);
  pinMode(backwardPin2, OUTPUT);
  pinMode(but1Pin, INPUT_PULLUP);
  pinMode(but2Pin, INPUT_PULLUP);
}

void loop()
{
  but1 = digitalRead(but1Pin);
  but2 = digitalRead(but2Pin);

  speed = 250;
  analogWrite(speedPin,speed);

  
  if(but1 == LOW){
    digitalWrite(forwardPin,LOW);
    digitalWrite(forwardPin2,LOW);
    Serial.print("Button 1 Pressed");
    Serial.print(speed);
    Serial.println();
  }
  else{
    digitalWrite(forwardPin,HIGH);
    digitalWrite(forwardPin2,HIGH);
  }
  if(but2 == LOW){
    digitalWrite(backwardPin,LOW);
    digitalWrite(backwardPin2,LOW);
    Serial.print("Button 2 Pressed, ");
    Serial.print(speed);   
    Serial.println();
  }
  else{
    digitalWrite(backwardPin,HIGH);
    digitalWrite(backwardPin2,HIGH);
  }
  
  
}