#include "neopixel.h"
#define PIXEL_PIN D0
#define PIXEL_COUNT 16
#define PIXEL_TYPE SK6812RGBW

Adafruit_NeoPixel ring = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {
  Serial.begin(9600);

//  ring.setBrightness(55);
  ring.begin();
  ring.show();

  //rainforest

}

void loop() {
 hueChase(ring.color(127, 100, 0), 50);
}
void finishedeating(const char *event,const char *data) {
  hueChase(ring.Color(127, 100, 0), 50); // Lime Green
  hueChase(ring.Color(80, 0, 127), 50); // Cyan
  hueChase(ring.Color(127, 0, 0), 50); // Green
  hueChase(ring.Color(127, 100, 0), 50); // Lime Green
  hueChase(ring.Color(80, 0, 127), 50); // Cyan
  hueChase(ring.Color(127, 0, 0), 50); // Green
  off();
}

void spacefinishedeating(const char *event, const char *data) {
  greencolor();
  redcolor();
  bluecolor();
}

void greencolor(){
  for(int i = 0; i <= 240; i += 20) {
    changeColor(ring.Color(i,0,0,0));
    delay(1);
  }
  delay(500);
  for(int i = 240; i >= 0; i -= 20) {
    changeColor(ring.Color(i,0,0,0));
    delay(1);
  }
}

void redcolor(){
  for(int i = 0; i <= 240; i += 20) {
    changeColor(ring.Color(0,i,0,0));
    delay(1);
  }
  delay(500);
  for(int i = 240; i >= 0; i -= 20) {
    changeColor(ring.Color(0,i,0,0));
    delay(1);
  }
}

void bluecolor(){
  for(int i = 0; i <= 240; i += 20) {
    changeColor(ring.Color(0,0,i,0));
    delay(1);
  }
  delay(500);
  for(int i = 240; i >= 0; i -= 20) {
    changeColor(ring.Color(0,0,i,0));
    delay(1);
  }
}

void hueChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<5; j++) {
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < ring.numPixels(); i=i+3) {
        ring.setPixelColor(i+q, c);
      }
      ring.show();
      delay(wait);

      for (uint16_t i=0; i < ring.numPixels(); i=i+3) {
        ring.setPixelColor(i+q, 0);
      }
    }
  }
}

void off() {
  changeColor(ring.Color(0, 0, 0, 0));
}
