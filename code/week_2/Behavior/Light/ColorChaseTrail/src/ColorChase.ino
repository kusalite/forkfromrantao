
#include "neopixel.h"
#include <math.h>

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D0
#define PIXEL_COUNT 16
#define PIXEL_TYPE WS2812

int trail[] = { 0,0,0,0,255,128,60,20,0,0,0,0,0,0,0 };

int pixel_position = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup(){

  Serial.begin( 9600 );

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop(){

  for(int i=0; i< strip.numPixels(); i++) {
    int val = trail[i];
    Serial.println( val );
    uint32_t c = strip.Color(val, val, val);
    strip.setPixelColor(i, c );
  }
  strip.show();

  updateTrails();

  delay( 100 );


}

void updateTrails(){

  int initial = trail[0];
  int num = strip.numPixels();
  for(int i=1; i< num; i++) {
    trail[ i - 1 ] = trail[ i ];
  }

  trail[ num - 1 ] = initial;

}
