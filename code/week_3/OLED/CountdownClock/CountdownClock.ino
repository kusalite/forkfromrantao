
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "neopixel.h"
#include <math.h>

// Making a state machine
// We need to be able to track the current state
// And changes to it.

// Holds the state that the device is in
int currentState = -1;
// this allows us to know to transition
int targetState = 0;

// The states are as follows
// 0. Welcome state / waiting for setup
// 1. Select time limit
// 2. Start timer
// 3. Timer running - counts down over time; the timer can be cancelled with a push of the button
// 4 Timer expired

// All of our components are included here:

// Vibration motor is on pin D2
int motorPin = D2;
int buttonPin = D1;
int potPin = A0;

int timerDuration = 0;
long timerStartTime = -1;

// Neopixe;
#define PIXEL_PIN D0
#define PIXEL_COUNT 16
#define PIXEL_TYPE WS2812

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

#define OLED_DC     D3
#define OLED_CS     D4
#define OLED_RESET  D5

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

void setup(){
  pinMode( buttonPin, INPUT_PULLDOWN );
  pinMode( potPin , INPUT); // sets pin as input
  pinMode(motorPin, OUTPUT);

  Serial.begin( 9600 );

  Time.zone(-5);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop(){

  if( currentState != targetState ){
    doTransition( );
  }

  updateCurrentState();

  // Check if state changed from high to low (button press).
  if ( digitalRead(buttonPin) == HIGH ) {

      delay( 100 );
      // Check if button is still low after debounce.
      if (digitalRead(buttonPin) == LOW) {
        targetState = targetState + 1;

        if( targetState >= 5 ){
          targetState = 0;
        }
      }
      Serial.print( "State Changed" );
      Serial.println( targetState );
  }

}


void updateCurrentState( ){

  switch( targetState ){
    case 0: updateWelcomeState(); break;
    case 1: updateSelectTimeLimitState(); break;
    case 2: updateStartTimerState(); break;
    case 3: updateTimerRunningState(); break;
    case 4: updateTimerExpiredState(); break;
  }

}


void updateWelcomeState(){
  //colorChase( strip.Color( 10,10,10 ), 50);
}


void updateSelectTimeLimitState(){

  int potVal = analogRead(potPin);    // read the value from the sensor
  int increments = map( potVal, 0, 4094, 0, 16 );

  timerDuration = increments * 60 * 1000;

  display.clearDisplay();

  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println( increments );
  display.println("");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setTextSize(1);
  display.println("minutes");
  display.display();

  // show desired minutes on ring...

  // show desired minutes on ring...
  uint16_t i;
  uint32_t c_on = strip.Color(255, 255, 255);
  uint32_t c_off = strip.Color(0, 0, 0);

  for(i=0; i< strip.numPixels(); i++) {
    if( i < increments )
      strip.setPixelColor(i, c_on );
    else
      strip.setPixelColor(i, c_off );
  }
  strip.show();
  delay(20);

}

void updateStartTimerState(){

  breathe(20);

}

void updateTimerRunningState(){

  int timeElapsed = millis() - timerStartTime;

  int remaining = map( timerDuration - timeElapsed, 0, strip.numPixels() * 60 * 1000 , 0, 16  );

  // show desired minutes on ring...
  uint16_t i;
  uint32_t c_on = strip.Color(255, 255, 255);
  uint32_t c_off = strip.Color(0, 0, 0);

  for(i=0; i< strip.numPixels(); i++) {
    if( i < remaining )
      strip.setPixelColor(i, c_on );
    else
      strip.setPixelColor(i, c_off );
  }
  strip.show();

  int mins = (timerDuration - timeElapsed ) / (60*1000);
  int secs = (( timerDuration - timeElapsed ) / 1000) % (mins*60);

  // text display tests
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print( mins );
  display.print("m ");
  display.print( secs );
  display.print("s ");
  display.println(" remaining! ");
  display.println("");
  display.display();

  delay( 20 );


}
void updateTimerExpiredState(){

  // buzz every minute
  // text display tests
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("OUT OF TIME!");
  display.println("");
  display.display();

  //vibrate();

  delay( 20 );


}


void doTransition( ){

  switch( targetState ){
    case 0: transitionIntoWelcomeState(); break;
    case 1: transitionIntoSelectTimeLimitState(); break;
    case 2: transitionIntoStartTimerState(); break;
    case 3: transitionIntoTimerRunningState(); break;
    case 4: transitionIntoTimerExpiredState(); break;
  }

  // update the currnet state
  currentState = targetState;
}

void transitionIntoWelcomeState(){
  // Clear the buffer.
  display.clearDisplay();

  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Welcome!");
  display.println("");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setTextSize(1);
  display.println("Press button!");
  display.display();

}

void transitionIntoSelectTimeLimitState(){
  // Clear the buffer.
  display.clearDisplay();


}

void transitionIntoStartTimerState(){
  // Clear the buffer.
  display.clearDisplay();

  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Start timer!");
  display.println("");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setTextSize(1);
  display.println("Press button!");
  display.display();

}

void transitionIntoTimerRunningState(){
  // Clear the buffer.
  display.clearDisplay();

  // capture the beginning time.
  timerStartTime = -1;

}
void transitionIntoTimerExpiredState(){
  // Clear the buffer.
  display.clearDisplay();

  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("OUT OF TIME!");
  display.println("");
  display.display();

  vibrate();
}



// Vibrates 3 times in a second
// We use this when the countdown timer gets to zero
void vibrate()
{
    int speed =  200;

    for( int i = 0; i < 3 ; i++ ){
      analogWrite(motorPin, speed);
      delay(200);
      analogWrite(motorPin, 0);
      delay(200);
    }
}


/* Calc the sin wave for the breathing white led */
void breathe( uint8_t wait ){

  float val = (exp(sin(millis()/2000.0*M_PI)) - 0.36787944)*108.0;
  Serial.println( val );

  uint16_t i;
  uint32_t c = strip.Color(val, val, val);

  for(i=0; i< strip.numPixels(); i++) {
    strip.setPixelColor(i, c );
  }
  strip.show();
  delay(wait);

}
// Chase a dot down the strip
// good for testing purposes
void colorChase(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);  // turn all pixels off
  }

  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c); // set one pixel
      strip.show();              // refresh strip display
      delay(wait);               // hold image for a moment
      strip.setPixelColor(i, 0); // erase pixel (but don't refresh yet)
  }
  strip.show(); // for last erased pixel
}
