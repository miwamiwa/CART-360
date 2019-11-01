const int trigPin = 9; //set pin variables
const int echoPin = 10;

int trigState = LOW; //state of trigPin
int interval = 1; // interval in milliseconds at which trigPin turns on
int interval2 = 1000; //time in milliseconds at which the distance is printed in serial monitors
int printState = LOW; //whether or not to print distance
unsigned long previousMillis = 0; //microsecond at which the pin was last writen

void setup()
{
  Serial.begin(9600); //begin serial communication
  pinMode(trigPin,OUTPUT); //set pinmodes
  pinMode(echoPin,INPUT);
  
}

void loop()
{
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
  if (printState = HIGH){
  Serial.print(distance);
  Serial.println("cm");}
  

}
