
// servo stuff 

// Include the library:
#include <NewPing.h>
// Define pins and max distance:
#define trigPin  2
#define echoPin  3

#define trigPin2  7
#define echoPin2  6

#define MAX_DISTANCE 200
NewPing sonar(trigPin, echoPin, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(trigPin2, echoPin2, MAX_DISTANCE);

float duration, distance, duration2, distance2;
long lastMillis1=0;
long lastMillis2=0;

#include <Servo.h>
Servo myservo;
Servo myservo2;
Servo myservo3;
int vel = 2;
int value;
int dif1, dif2, dif3;
int dif=1;

int pos1 = 70;    
int tarPos1 = 70;
int pos1a = 70;
int pos1b = 62;

int pos2 = 33;   
int tarPos2 = 33;
int pos2a = 33;
int pos2b = 40;

int pos3 = 109; 
int tarPos3 = 109;
int pos3a = 109;
int pos3b = 115;

bool comStarted = false;

void setup() {
  
  // servo
  myservo.attach(3);
  myservo2.attach(10);
  myservo3.attach(11);
  
  //ultrasonic
  pinMode(trigPin,OUTPUT); //set pinmodes
  pinMode(echoPin,INPUT);
  pinMode(trigPin2,OUTPUT); //set pinmodes
  pinMode(echoPin2,INPUT);
  pinMode(12, INPUT);
  
  Serial.begin(9600); 
}

void loop() {

 // int msState = digitalRead(motionSensorPin);
 // Serial.println(msState);

   if(!comStarted){
    if(digitalRead(12)==HIGH) {
      comStarted = true;
      int mess = 300+int(distance);
      Serial.println(mess);
    }
  }

  getDist();
  getDist2();
  receiveMax();

 // long mess1 = 300+long(distance) + long(distance2)*1000;
 //   Serial.println( long(distance2)*1000);


  updateServo();
  
}

void getDist(){
  
  long currentMillis = millis();
  
  if(currentMillis-lastMillis1>30){
    lastMillis1 = currentMillis;
    duration = sonar.ping();
  distance = (duration / 2) * 0.0343;
  }
}

void getDist2(){
  
  long currentMillis2 = millis();
  
  if(currentMillis2-lastMillis2>30){
    lastMillis2 = currentMillis2;
    duration2 = sonar2.ping();
  distance2 = (duration2 / 2) * 0.0343;
  }
}

void receiveMax(){

   if(Serial.available()&&comStarted){

    value = Serial.read();

    if (value<300){

     if(value%2==0) tarPos1 = pos1a;
    else tarPos1 = pos1b;

    int val2 = value/10;

    if(val2%2==0) tarPos2 = pos2a;
    else tarPos2 = pos2b;

    int val3 = value/100;

    if(val3%2==0) tarPos3 = pos3a;
    else tarPos3 = pos3b;

      long mess1 = 300+long(distance) + long(distance2)*1000;
      Serial.println(mess1);
    }
  }
}


void updateServo(){
  
   if(pos1>tarPos1) pos1-=vel;
  else if (pos1<tarPos1) pos1+=vel;
  myservo.write(pos1); 
  
  if(pos2>tarPos2) pos2-=vel;
  else if (pos2<tarPos2) pos2+=vel;
  myservo2.write(pos2); 

  if(pos3>tarPos3) pos3-=vel;
  else if (pos3<tarPos3) pos3+=vel;
  myservo3.write(pos3); 
}
