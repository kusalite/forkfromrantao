
#include "neopixel.h"
#include <math.h>

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D0
#define PIXEL_COUNT 16
#define PIXEL_TYPE WS2812

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {

  Serial.begin( 9600 );

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  breathe();
  delay( 50 );
}

/* Calc the sin wave for the breathing white led */
float breathe( ){

  float val = (exp(sin(millis()/2000.0*M_PI)) - 0.36787944)*108.0;
  Serial.println( val );

  uint16_t i;
  uint32_t c = strip.Color(val, val, val);

  for(i=0; i< strip.numPixels(); i++) {
    strip.setPixelColor(i, c );
  }
  strip.show();

}
