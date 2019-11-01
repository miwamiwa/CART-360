#include <Servo.h>

const int buttonPin = 2;
//const int ledPin = 13;
int vel = 2;

int buttonState =0;
int lastButtonState = 0;
int randVal =0;
int value;
int posValue=0;
int dif1, dif2, dif3;
int dif=1;

int pos = 70;    // variable to store the servo position
int tarPos = 80;
int pos2 = 105;    // variable to store the servo position
int tarPos2 = 114;
int pos3 = 90;    // variable to store the servo position
int tarPos3 = 45;
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
  myservo.attach(3);
  myservo2.attach(10);
  myservo3.attach(11);
  Serial.begin(9600);
}

void loop() {

  if(Serial.available()){
    value = Serial.read();

  //  Serial.print(value);

 //   digitalWrite(ledPin, value);
  if(value==10) tarPos =70+dif1;
  else if(value==11) tarPos = 69+dif1;
  else if(value==20) tarPos2=109+dif2;
  else if(value==21) tarPos2 = 101+dif2;
  else if(value==30) tarPos3 =33+dif3;
  else if(value==31) tarPos3 = 42+dif3;
  else if(value==40) dif1+=dif;
  else if(value==41) dif1-=dif;
  else if(value==50) dif2+=dif;
  else if(value==51) dif2-=dif;
  else if(value==60) dif3+=dif;
  else if(value==61) dif3-=dif;
    
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
  pos += getPos(pos,tarPos);
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
  delay(5);
}

int getPos(int p, int tp){
  if(p>tp){
    if(p-tp<vel) return p-tp;
    else return -vel;
  }
  else if(p<tp){
    if(tp-p<vel) return tp-p;
    else return vel;
  }
  else return 0;
}
