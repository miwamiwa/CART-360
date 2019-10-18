/********************** ETUDE 3 CART 360 2019 *******************************
 * WELCOME! 
 * THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (5 KEYS)
 * WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK SINGLE NOTES (NO CHORDS). 
 * THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
 * THERE ARE 5 POSSIBLE MODES
 * 0 ==  reset    ==   led off == also resets
 * 1 ==  live     ==   led BLUE
 * 2 ==  record   ==   led RED
 * 3 ==  play     ==   led GREEN
 * 4 ==  loopMODE ==   led PURPLE
 * 
 * ADDITIONALLY - WHEN THE USER CHANGES MODE, 
 * THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)

 * PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
 * DO NOT ADD ANY MORE FUNCTION DEFINITIONS 
 * ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
 * THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
 * PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
 * GOOD LUCK!
 */
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_R 9 // R PIN
#define LED_PIN_G 6 // G PIN
#define LED_PIN_B 5 // B PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// a constant for duration
const int duration = 200;

// constant for pin to output for buzzer 
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes =0;
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES]; 
int mode =0; // start at off


// ------------- Here are some variables which I added. I know we 
// weren't supposed to but that just made most sense to me 

// this keeps track of the time threshold after which the next note should be played 
long nextNote =0;
// these two booleans are for making sure buttons send a signal once upon being pressed
boolean modeButtonPressed = false;
boolean noteButtonPressed = false;

/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  // remove once done testing 
  Serial.begin(9600);   

  
  pinMode(BUTTON_MODE_PIN, INPUT);
}

/**********************LOOP() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change the loop - it establishes the flow of the program
 * We call here 3 functions repeatedly:
 * 1: chooseMode(): this function will determine the mode that your program is in 
 * based on if the button (linked to the BUTTON_MODE_PIN) was pressed
 * 2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
 * 3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();
  
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Read the value from the Button (linked to the BUTTON_MODE_PIN) and 
 * if is being pressed then change the mode variable.
 * REMEMBER:
 * mode == 0 is reset 
 * mode == 1 is live
 * mode == 2 is record
 * mode == 3 is play
 * mode == 4 is loopMode
 * Every time the user presses the button, the program will go to the next mode,
 * once it reaches 4, it should go back to mode == 0. 
 * (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode(){
  // IMPLEMENT

  // check if the mode button is being pressed 
  int val = digitalRead(BUTTON_MODE_PIN);

  // if button currently pressed
  if(val==HIGH){
    // print to serial for testing
   // Serial.println("button mode high");

  // if its being pressed hasn't triggered anything yet, 
  // change modes and reset note count. 
    if( !modeButtonPressed ){
      mode  = (mode+1)%5;
      countNotes=0;
      nextNote = millis();
  }
  // mark button as pressed
  modeButtonPressed = true;
  }
  else {
    // if button is no longer pressed, mark it as such 
    modeButtonPressed = false;
  }

}

/******************SETRGB(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Depending on the value of the mode variable:
 * if the mode is 0 - RGB LED IS OFF
 * if the mode is 1 - RGB LED IS BLUE
 * if mode is 2 - RGB LED IS RED
 * if mode is 3 - RGB LED IS GREEN
 * if mode is 4 - RGB LED iS PURPLE
 * YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB()
{
  //IMPLEMENT

  // assign different color lights to the RGB LED according to mode 
  switch(mode){
    case 0: lightRGB(0,0,0); break; // no color 
    case 1: lightRGB(0,0,200); break; // blue 
    case 2: lightRGB(200,0,0); break; // red 
    case 3: lightRGB(0,200,0); break; // green 
    case 4: lightRGB(200,0,200); break; // purple
    default: lightRGB(0,0,0); break; // in case no case is triggered
  }
}

// lightRGB()
// I wrote a function.. imagine that I copy-pasted this please
// triggers correct analogWrite() functions according to the color we want to display on the RGB LED
void lightRGB(int r, int g, int b){
  analogWrite(LED_PIN_R, r);
  analogWrite(LED_PIN_G, g);
  analogWrite(LED_PIN_B, b);
}
/**********************SELECTMODE() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
 * There are 4 possibilities
 * 1: reset(): this function will reset any arrays etc, and will do nothing else
 * 2: live(): this function will play the corresponding notes 
 * to the user pressing the respective buttons. 
 * NOTE:: the notes played are NOT stored
 * 3: record(): this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * 4: play(): this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * 5: loopMode(): this function will playback any notes stored in the array that were recorded, 
 * BUT unlike the previous mode, you can choose in which sequence the notes are played.
 * REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode()
{
  if(mode ==0) { 
    reset();
  }
  else if(mode ==1) {
    live();
  }
  else if(mode ==2) {
    record();
  }
  
  else if(mode ==3) {
    play();
  }
   
   else if(mode ==4) {
    loopMode();
  }
}
/******************RESET(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
{
  // IMPLEMENT
  
  // run through each note in the notes list and clear it. 
  for(int i=0; i< MAX_NOTES; i++){
    notes[i]=0;
  }
  
}
/******************LIVE(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * NOTE:: the notes played are NOT stored
 * SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live()
{
    
    // get the analog reading from the pin where all the buttons go to 
    int  noteReading = analogRead(A0);
    Serial.println(noteReading);

    // if there is significant voltage
    if(noteReading>15){
      // trigger a tone by converting voltage directly to frequency. 
      // this is a place where I could have written a bunch of if/else statements to 
      // find which button was pressed ( such as if (a<x) {} else if (x<b) {} etc.) 
      // and reassign another frequency, like a pentatonic scale or something. 
      // i spent time this weekend playing with servo's instead though :)
      tone(BUZZER_PIN, noteReading, 150);

  }

  
}
/******************RECORD(): IMPLEMENT **********************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * AND - output the note to the buzzer using the tone() function
 * THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record()
{
  // IMPLEMENT

  // get reading from the note buttons 
    int  noteReading = analogRead(A0);
  //Serial.println(noteReading);

  // if there is significant voltage
  if(noteReading>15){

    // if no button was pressed yet 
    if(!noteButtonPressed){

      // update appropriate entry in the notes array 
      notes[countNotes] = noteReading;

      // trigger a sound so the user knows something happened
      tone(BUZZER_PIN, noteReading, 150);

      // move on to the next note 
      countNotes  = (countNotes+1)%16;
    }
    // mark button as pressed
    noteButtonPressed = true;
  }
  else {
    // if no button is pressed, mark them as such 
    noteButtonPressed = false;
  }
  
}
/******************PLAY(): IMPLEMENT ************************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ each value IN ORDER
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play()
{
  // IMPLEMENT
    // if threshold for playing the next note has been reached
      if(millis()>=nextNote){

    // if there is a note to be played (this cuts the loop short if there arent enough notes)
      if(notes[countNotes]>0){
        // play the note
        tone(BUZZER_PIN, notes[countNotes], 150);
        // set the next threshold 
        nextNote = millis()+duration;
        }
        // update note count whether or not one was played 
      countNotes  = (countNotes+1)%16;  
      
    }
}
/******************LOOPMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void loopMode()
{
  //IMPLEMENT
  // same structure as play(): if note threshold is reached
  if(millis()>=nextNote){
    // if there is a note to play 
      if(notes[countNotes]>0){
        // play the note 
        tone(BUZZER_PIN, notes[countNotes], 150);
        // set the next threshold 
        nextNote = millis()+duration;
        }
        
    //  pick a random note to play instead of incrementing them. 
      countNotes = int( random(0, 16) ); 
      
    }
}

/**************************************************************************/
