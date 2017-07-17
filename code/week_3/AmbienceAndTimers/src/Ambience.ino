#include "math.h"
#include "neopixel.h"


// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D0
#define PIXEL_COUNT 16
#define PIXEL_TYPE WS2812

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);


# define STATE_ACTIVATING 0
# define STATE_AMBIENT 1
# define STATE_ALERT 2

int state = 0;

void setup() {

 Serial.begin(9600);
 Serial.println("start");


 strip.begin();
 strip.show(); // Initialize all pixels to 'off'


}


void loop() {

 switch( state ){
   case STATE_ACTIVATING: doStateActivating(); break;
   case STATE_AMBIENT: doStateAmbient();break;
   case STATE_ALERT: doStateAlert(); break;
 }

}
/*
  ACTIVATION STATE

  Ambient action:
  Slowly fade up to green
  Over n seconds to full brightness.
*/

# define ACTIVATE_AFTER 20000
int beganActivationAt = -1;

void doStateActivating()
{
  Serial.println( "doStateActivating()" );

  // start tracking activation time
  if( beganActivationAt == -1 ){
    beganActivationAt = millis();
  }

  // how much time has elapsed since it began
  int timeElapsed = millis() - beganActivationAt;

  // if it's fully activated go to the next state
  if( timeElapsed > ACTIVATE_AFTER ){
    state = STATE_AMBIENT;
    return;
  }

  Serial.print( "elapsed: " );
  Serial.print( timeElapsed );

  // other wise we need to convert to a percentage
  // and fade up to Green

  float percentElapsed = timeElapsed * 1.0f / ACTIVATE_AFTER;
  int colorComponent = 255 * percentElapsed;

  Serial.print( "  percent: " );
  Serial.print( percentElapsed );
  Serial.print( "  c: " );
  Serial.print( colorComponent );

  uint32_t c = strip.Color( 0 , colorComponent , 0 );
  setNeoPixelToColor( c );
  delay( 100 );
}

# define AMBIENT_FOR 40000
int beganAmbientAt = -1;

void doStateAmbient(){

  delay( 100 );

  Serial.println( "doStateAmbient()" );

  // start tracking activation time
  if( beganAmbientAt == -1 ){
    beganAmbientAt = millis();
  }

  // how much time has elapsed since it began
  int timeElapsed = millis() - beganAmbientAt;

  // if it's fully activated go to the next state
  if( timeElapsed > AMBIENT_FOR ){
    state = STATE_ALERT;
    return;
  }

  // other wise we need to convert to a percentage
  // and fade up to Green

  float percentElapsed = timeElapsed * 1.0f / AMBIENT_FOR;
  int colorComponent = 255 * percentElapsed;

  // switch from green to red
  uint32_t c = strip.Color( colorComponent ,  255 - colorComponent , 0 );
  setNeoPixelToColor( c );
  delay( 100 );

}



void doStateAlert(){
  pulseRed(  );
  delay( 100 );
}


/* Calc the sin wave for the breathing white led */
float pulseRed( ){
  float val = (exp(sin(millis()/2000.0*M_PI)) - 0.36787944)*108.0;
  uint16_t i;
  uint32_t c = strip.Color(val, 0, 0 );
  for(i=0; i< strip.numPixels(); i++) {
    strip.setPixelColor(0, c );
  }
  strip.show();
}


void setNeoPixelToColor( uint32_t color )
{
  for (int i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);  // turn all pixels off
  }
  strip.show();

}
