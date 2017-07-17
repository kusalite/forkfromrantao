#include "neopixel.h"

# define STATE_WELCOME 0
# define STATE_WAITING 1
# define STATE_SELECTION 2
# define STATE_MEDITATING 3
# define STATE_COMPLETED 4

// we also need a variable to store the state...

int state = 0;

// We know we have a few inputs and output so
// set them up

//Defining the pins
int touchPin = A1;
int softPotReading;

int heartPin = A2;
int fsrPin = A3;
int vibratorPin = A4;

//Byte values for the MP3 players
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D5
#define PIXEL_COUNT 5 //16
#define PIXEL_TYPE WS2812
#define BRIGHTNESS 50 // 0 - 255

Adafruit_NeoPixel timerStrip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {

  Serial.begin(9600);
  Serial.println("Setup complete");

  Serial1.begin(9600);//Serial 1 used to communicate with MP3 Player

  //Initialises the MP3 player
  sendMP3Command(0x3F, 0, 0);
  //Sets volume of MP3 player to 75
  sendMP3Command(0x06, 0, 75);

  pinMode(touchPin,INPUT_PULLUP);
  pinMode(heartPin,INPUT_PULLUP);
  pinMode(vibratorPin, OUTPUT);

  // add the neopixels
  timerStrip.begin();
  timerStrip.show();
  timerStrip.setBrightness( BRIGHTNESS );

}

void loop() {

  // get the current reading
  sampleFromSoftPotentiometer();

  updateStatesBasedOnSensors();

	// Our loop becomes a place to decide which state is shown
	// And nothing more.
	// Each separate function controls output and input independently

 switch( state ){
   case STATE_WELCOME:    doWelcomeState(); break; //Cycles up and down the LEDs
   case STATE_WAITING:    doWaitingState(); break; //Breathes the LEDs
   case STATE_SELECTION:  doSelectingState();break; //While touchput is being touched
   case STATE_MEDITATING: doMeditatingState();break; //Once meditation has started
   case STATE_COMPLETED:  doCompletedState();break; //Once meditation has been completed
 }

 delay( 100 );
}

void updateStatesBasedOnSensors(){

  // If the user is touching then
  // update the state to
  // show the user selection
  if(softPotReading > 30)
  {
    state = STATE_SELECTION;
  }

}

/***************************

  WELCOME STATE

***************************/

void doWelcomeState(){

  // blink the leds 3 times
  cycleUpLeds(  );
  // pulse vibration
  notifyWithVibration( 3 );
  // now move to the waiting state...
  state = STATE_WAITING;

}

/***************************

  WAITING STATE
  No activity until
  the user makes a selection

***************************/

void doWaitingState(){

  breathe();

}

/***************************

  SELECTION STATE
  Map the user input to
  visual read out

***************************/

// Selection is a range from
// 1 - 5
// i.e. the number of pixels on
// the neopixel
int selection = 0;

// wait for n seconds before
// moving to the next state
// so you know the user's actually
// confirmed
int delayBeforeSelection = 2000;//User must press the strip for 2 seconds to activate
long lastSelectionUpdate = -1;

const unsigned long DURATION = 7500;

unsigned long timerDuration = -1;
unsigned long timerStartedAt = -1;
unsigned long timerEndAt = -1;
bool timerRunning = false;

void doSelectingState(){

  // Update the selection

  if(softPotReading > 30)
  {
    // the user is still selecting

    selection = map( softPotReading, 0, 4000, 1, timerStrip.numPixels() ); //converts touch readings to value between 1-5
    selection = constrain( selection, 0, timerStrip.numPixels() ); // ensure it's in the range

    // update the time when
    // the user last selected
    lastSelectionUpdate = millis();

    displaySelectedLEDs( selection );

  }else if( lastSelectionUpdate + delayBeforeSelection < millis() ) {
    // finished selecting
    // and we should start
    // the timer

    timerRunning = true;
    timerDuration = selection * DURATION;
    timerStartedAt = millis();
    timerEndAt = timerStartedAt+timerDuration;
    Serial.println("Timer has started!");

    // confirmation
    notifyWithVibration( 3 );

    // update the states
    if( selection > 0 ){

      //Plays the next track in SD card once timer is started
      sendMP3Command(0x01,0,1);

      // move to the next state
      state = STATE_MEDITATING;
    }else{
      state = STATE_WAITING;
    }

  }

}

/***************************

  MEDIATING STATE
  VIbrate in time with breathing
  Slowly track down the
  indicators

***************************/

void doMeditatingState(){

  // work out the numebr of LEDs to display

  int elapsed = millis() - timerStartedAt;
  float percentElapsed = elapsed * 1.0f / timerDuration;
  int numLeds = map( 1 - percentElapsed, 0, 1, 0 , timerStrip.numPixels() );

  displaySelectedLEDs( numLeds );

  vibrate();

  if( millis() > timerEndAt ){
    // we hen finished move to the
    // next state
    state = STATE_COMPLETED;
  }

}

/***************************

  COMPLETED STATE
  VIbrate once to indicate
  completion
  Then return to
  waiting

***************************/

void doCompletedState(){

  Serial.println( "Completed countdown" );

  //Voice note or earcon to tell user that it's over
  sendMP3Command(0x16,0,1);

  notifyWithVibration( 3 );

  stopVibration();

  state = STATE_WAITING;

}

/***************************

   SOFT POT METHODS

***************************/

void sampleFromSoftPotentiometer()
{
  softPotReading = 4095;
  // sample 6 times...
  for( int j = 0 ; j < 6; j++ ){
    int val = analogRead(touchPin);
    if( val < softPotReading )
      softPotReading = val;
    delay(20);
  }
  /*int i = analogRead(touchPin);*/
  Serial.printf("The touch value is: %d \n",softPotReading);

}

/***************************

   VIBRATION MOTOR METHODS

***************************/

void stopVibration()
{
  analogWrite(vibratorPin, 0.0);
}

void notifyWithVibration( int times )
{
  for( int i = 0 ; i < times; i++ ){
    analogWrite(vibratorPin, 255);
    delay( 200 );
    analogWrite(vibratorPin, 0);
    delay( 200 );
  }
}

void vibrate()
{
  float val = abs(float(sin(float(millis())/10000 * 3.14159)*120));
  analogWrite(vibratorPin, val);
}

/***************************
  NEOPIXEL HELPERS
***************************/
//Breathing lights indicate a functional mat
void breathe()
{
  Serial.println("Breathing!");
  float brightness=abs(float(sin(float(millis())/3000 * 3.14159)*75));
  //First setting pixel color of all pixels to green
  for(int i=0; i< timerStrip.numPixels(); i++)
  {
    //if(i<selection)
      timerStrip.setPixelColor(i, 0, brightness, 0);
    //else
    //  timerStrip.setPixelColor(i,0,0,0);
  }
}

void blink( int times ){
  // blink n times
  for( int i = 0 ; i < times; i++ ){
    allNeopixelsOn();
    delay( 150);
    allNeopixelsOff();
    delay( 150);
  }
}

void cycleUpLeds(  ){
  allNeopixelsOff();

  // wipe up
  for (int i=0; i < timerStrip.numPixels(); i++) {
    timerStrip.setPixelColor(i, timerStrip.Color( 0,255,0 ));  // turn all pixels on
    timerStrip.show();
    delay( 200 );
  }

  // wipe down
  for (int i= timerStrip.numPixels() - 1 ; i >= 0 ; i-- ) {
    timerStrip.setPixelColor(i, timerStrip.Color( 0,0,0 ));  // turn all pixels off
    timerStrip.show();
    delay( 200 );
  }


}

void displaySelectedLEDs( int num ){

  // wipe up
  for (int i=0; i < timerStrip.numPixels(); i++) {
    if( i < num ){
      timerStrip.setPixelColor(i, timerStrip.Color( 0,255,0 ));  // turn all pixels off
    }
  }
  timerStrip.show();

}


void allNeopixelsOn(){
  for (int i=0; i < timerStrip.numPixels(); i++) {
    timerStrip.setPixelColor(i, timerStrip.Color( 0,255,0 ));  // turn all pixels off
  }
  timerStrip.show();
}

void allNeopixelsOff(){
  for (int i=0; i < timerStrip.numPixels(); i++) {
    timerStrip.setPixelColor(i, 0);  // turn all pixels off
  }
  timerStrip.show();
}

/***************************

  SOUND HELPERS

***************************/

//Passes byte code to the MP3 Player via TX pins and serial module
void sendMP3Command(byte CMD, byte Par1, byte Par2) // Execute the command and parameters
{
 // Calculate the checksum (2 bytes)
 int16_t checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

 // Build the command line
 byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge, Par1, Par2, checksum >> 8, checksum & 0xFF, End_Byte};

 //Send the command line to the serial module
 for (byte k=0; k<10; k++)
 {
  Serial1.write( Command_line[k]);
 }
}
