
#include "neopixel.h"
#include <math.h>

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D0
#define PIXEL_COUNT 16
#define PIXEL_TYPE WS2812

int pixel_position = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup(){

  Serial.begin( 9600 );

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop(){

  for(int i=0; i< strip.numPixels(); i++) {
    uint32_t c;

    if( pixel_position == i ){
      c = strip.Color(255, 255, 255);
    }else{
      c = strip.Color(0, 0, 0);
    }
    strip.setPixelColor(i, c );
  }
  strip.show();

  pixel_position++;
  if( pixel_position >= strip.numPixels() )
  {
    pixel_position = 0;
  }

  delay( 50 );


}
