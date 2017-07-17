#include "neopixel.h"

/*

	THIS IS A QUICK EXAMPLE OF A PROJECT THAT INVOLVES
	A SERIES OF STATES

	Imagine we're making a Pomodoro timer
	You'll have a few different states
  Like this https://blog.particle.io/2016/06/28/neopixels/

	The Pomodoro Technique is simple–to keep yourself alert and productive,
	work in 25 minute intervals then give yourself a 5 minute break.
	A 25 minute work period and 5 minute rest period constitutes one “pomodoro”.
	After four cycles, you should give yourself a longer break of 15-30 minutes.
	Four cycles of work and rest is called a “cycle” or “set”.

  We would have
	- A neopixel ring
	- A a button to start/stop
	- A piezo to make a beep in between intervals

	Simple.

	First we're going to have a few states
	- We'll want to show that the device is started up and ready to roll
	- We'll want a waiting to start state (i.e. nothing's happening)
	- We'll want a state for the main interval
	- We'll want a state for the 5 minute reset state

	Each of these will have different behaviors and actions.

	First let's define the states that we want...

*/

# define STATE_WELCOME 0
# define STATE_WAITING 1
# define STATE_INTERVAL 2
# define STATE_INTERVAL_COMPLETED 3
# define STATE_RESTING 4
# define STATE_RESTING_COMPLETED 5

// we also need a variable to store the state...

int state = 0;

// We know we have a few inputs so
// set them up

int buttonPin = D0;
int buttonValue = HIGH;


// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D1
#define PIXEL_COUNT 16
#define PIXEL_TYPE WS2812

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

// Finally set the speaker
int speakerPin = D2;


void setup() {

 Serial.begin(9600);
 Serial.println("setup complete");

 // add the button with a pull up resistor
 pinMode( buttonPin, INPUT_PULLUP );

 // add the neopixels
 strip.begin();
 strip.show();
 // Initialize all pixels to 'off'

 pinMode( speakerPin, OUTPUT );


}


void loop() {

	// Our loop becomes a place to decide which state is shown
	// And nothing more.
	// Each separate function controls output and input indepedently
  getButtonValue();

 switch( state ){
   case STATE_WELCOME:
     doWelcomeState();
     break;
   case STATE_WAITING:
     doWaitingState();
     break;
   case STATE_INTERVAL:
     doIntervalState();
     break;
   case STATE_INTERVAL_COMPLETED:
		 doIntervalCompletedState();
     break;
   case STATE_RESTING:
		 doRestingState();
     break;
   case STATE_RESTING_COMPLETED:
		 doRestingCompletedState();
     break;

 }


}

/***************************

  WELCOME STATE

***************************/

void doWelcomeState(){

  beep( 150 );
  blink( 3 );
  // now move to the waiting state...
  state = STATE_WAITING;

}

/***************************

  WAITING STATE

***************************/

void doWaitingState(){

  // We're going to show and do nothing
  // until we get a button push

  if( buttonValue == LOW ){
    beep( 200 ) ;
    state = STATE_INTERVAL;
  }

}


/***************************

  INTERVAL STATE

***************************/

//int INTERVAL_TIME = 25*60*1000; // 25 minutes
int INTERVAL_TIME = 60*1000; // 25 minutes
long startedIntervalAt = -1;

void doIntervalState(){

  // if this is the beginning...
  // let's keep a record of the time elapsed
  if( startedIntervalAt == -1 )
    startedIntervalAt = millis();

  // how many milliseconds have elapsed
  int timeElapsed = millis() - startedIntervalAt;

  int numPixelsToLight = map( timeElapsed, 0, INTERVAL_TIME, 0, strip.numPixels() );

  for( int i = 0; i < strip.numPixels(); i++ ){
    if( i <= numPixelsToLight ){
      strip.setPixelColor(i, strip.Color( 10,10,10 ));  // turn all pixels off
    }else{
      strip.setPixelColor(i, 0);  // turn all pixels off
    }
  }
  strip.show();

  // if we're beyond the time, let's move on
  if( timeElapsed > INTERVAL_TIME ){
    state = STATE_INTERVAL_COMPLETED;
  }

  delay( 100 );
}

/***************************

  INTERVAL COMPLETED

***************************/

void doIntervalCompletedState(){
  beep( 150 );
  wipeDownNeoPixels();

  state = STATE_RESTING;
}


/***************************

  RESTING STATE

***************************/

//int REST_TIME = 5*60*1000; // 25 minutes
int REST_TIME = 30*1000; // 25 minutes
long startedRestingAt = -1;

void doRestingState(){

  // if this is the beginning...
  // let's keep a record of the time elapsed
  if( startedRestingAt == -1 )
    startedRestingAt = millis();

  // how many milliseconds have elapsed
  int timeElapsed = millis() - startedRestingAt;

  int numPixelsToLight = map( timeElapsed, 0, INTERVAL_TIME, 0, strip.numPixels() );

  for( int i = 0; i < strip.numPixels(); i++ ){
    if( i <= numPixelsToLight ){
      strip.setPixelColor(i, strip.Color( 10,0,10 ));  // turn all pixels off
    }else{
      strip.setPixelColor(i, 0);  // turn all pixels off
    }
  }
  strip.show();

  // if we're beyond the time, let's move on
  if( timeElapsed > INTERVAL_TIME ){
    state = STATE_RESTING_COMPLETED;
  }

  delay( 100 );

}

/***************************

  RESTING COMPLETED

***************************/


void doRestingCompletedState(){


  wipeDownNeoPixels();

  for( int i = 0; i<5; i++){
    beep( 150 );
    blink( 1 );
  }

  startedIntervalAt = -1;
  startedRestingAt = -1;
  state = STATE_WAITING;

}


/***************************

   BUTTON METHODS

***************************/


void getButtonValue()
{
 buttonValue = digitalRead(buttonPin);
 Serial.print( "buttonValue = " );
 Serial.println( buttonValue );

}


/***************************

   SPEAKER METHODS

***************************/


void beep(unsigned char delayms){
  analogWrite(speakerPin, 20);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(speakerPin, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms
}


/***************************

  NEPIXEL HELPERS

***************************/

void wipeDownNeoPixels(){

  for (int i=strip.numPixels() - 1; i >= 0; i--) {
    strip.setPixelColor(i, 0);
    strip.show();
    delay( 200 );
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

void allNeopixelsOn(){
  for (int i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color( 10,10,10 ));  // turn all pixels off
  }
  strip.show();
}

void allNeopixelsOff(){
  for (int i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);  // turn all pixels off
  }
  strip.show();
}
