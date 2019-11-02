
// servo stuff 
#include <Servo.h>
Servo myservo;
Servo myservo2;
Servo myservo3;
int vel = 2;
int value;
int dif1, dif2, dif3;
int dif=1;
int pos = 70;    
int tarPos = 80;
int pos2 = 105;   
int tarPos2 = 114;
int pos3 = 90; 
int tarPos3 = 45;


// ultrasonic things 
const int trigPin = 5; //set pin variables
const int echoPin = 6;
int trigState = LOW; //state of trigPin
int interval = 1; // interval in milliseconds at which trigPin turns on
int interval2 = 1000; //time in milliseconds at which the distance is printed in serial monitors
int printState = LOW; //whether or not to print distance
unsigned long previousMillis = 0; //microsecond at which the pin was last writen


void setup() {
  
  // servo
  myservo.attach(3);
  myservo2.attach(10);
  myservo3.attach(11);
  
  //ultrasonic
  pinMode(trigPin,OUTPUT); //set pinmodes
  pinMode(echoPin,INPUT);

  pinMode(2,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {

  updateServo();
  updateDistSensor();
  //delay(5);
}

void updateServo(){
  
  if(Serial.available()){
    value = Serial.read();
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

   if(pos>tarPos) pos-=vel;
  else if (pos<tarPos) pos+=vel;
  myservo.write(pos); 
  
  if(pos2>tarPos2) pos2-=vel;
  else if (pos2<tarPos2) pos2+=vel;
  myservo2.write(pos2); 

  if(pos3>tarPos3) pos3-=vel;
  else if (pos3<tarPos3) pos3+=vel;
  myservo3.write(pos3); 
}

void updateDistSensor(){

    unsigned long currentMillis = millis(); //time in milliseconds from which the code was started
  if (currentMillis-previousMillis >= interval) { //check "blink without delay" code
    previousMillis = currentMillis;
    if (trigState == LOW){
      (trigState = HIGH);
    }
    else {
      (trigState = LOW);
    }
  }
  // printing if statement
  if (currentMillis-previousMillis >= interval2) { //check "blink without delay" code
    previousMillis = currentMillis;
    if (printState == LOW){
      (printState = HIGH);
    }
    else {
      (printState = LOW);
    }
  }
  digitalWrite(trigPin,trigState);
  int duration, distance; //variables
  duration = pulseIn(echoPin,HIGH);
  distance = (duration/2) / 29.1;
  if (printState = HIGH&&distance>0){
    long currenttime = millis();
  Serial.println(500+distance);
  Serial.flush();
  delay(2);
  serialFlush();
 
  }
}

  void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
} 
