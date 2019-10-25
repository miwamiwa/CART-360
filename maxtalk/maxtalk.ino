#include <Servo.h>

const int buttonPin = 2;
//const int ledPin = 13;
int vel = 10;

int buttonState =0;
int lastButtonState = 0;
int randVal =0;
int value;
int posValue=0;

int pos = 40;    // variable to store the servo position
int tarPos = 30;
int pos2 = 70;    // variable to store the servo position
int tarPos2 = 80;
int pos3 = 90;    // variable to store the servo position
int tarPos3 = 100;
int rate = 15;
int nextUpdate = 15;

boolean buttonPressed = false;


Servo myservo;
Servo myservo2;
Servo myservo3;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
//  pinMode(ledPin,OUTPUT);
  myservo.attach(9);
  myservo2.attach(10);
  myservo3.attach(11);
  Serial.begin(9600);
}

void loop() {

  if(Serial.available()){
    value = Serial.read();

  //  Serial.print(value);

 //   digitalWrite(ledPin, value);
  if(value==10) tarPos =30;
  else if(value==11) tarPos = 40;
  else if(value==20) tarPos2=70;
  else if(value==21) tarPos2 = 80;
  else if(value==30) tarPos3 =90;
  else if(value==31) tarPos3 = 100;
    
  }
/*
  int buttonReading = analogRead(A2);
  if(buttonReading>900){
    if(!buttonPressed){
      buttonPressed=true;
      Serial.println("41");
    }
  }
  else if(buttonReading>400){
    if(!buttonPressed){
      buttonPressed=true;
      Serial.println("42");
    }
  }
  else if(buttonReading>200){
    if(!buttonPressed){
      buttonPressed=true;
      Serial.println("43");
    }
  }
  else buttonPressed = false;
*/
  if(pos>tarPos) pos-=vel;
  else if (pos<tarPos) pos+=vel;
  myservo.write(pos); 

  if(pos2>tarPos2) pos2-=vel;
  else if (pos2<tarPos2) pos2+=vel;
  myservo2.write(pos2); 

  if(pos3>tarPos3) pos3-=vel;
  else if (pos3<tarPos3) pos3+=vel;
  myservo3.write(pos3); 
  
 // Serial.println(buttonReading);
  /*
  randVal = random(1000);
  buttonState = digitalRead(buttonPin);

  if(buttonState != lastButtonState){
    if(buttonState==HIGH){
      
    }
    else {
      Serial.println(randVal);
    }
    delay(50);
  }
    if(pos>tarPos) pos-=vel;
  else if (pos<tarPos) pos+=vel;
  
  myservo.write(pos); 
  
  lastButtonState = buttonState;
  */
  delay(10);
}
