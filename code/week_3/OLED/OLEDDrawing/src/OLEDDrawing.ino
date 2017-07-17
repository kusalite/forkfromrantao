
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

/* Uncomment this block to use hardware SPI
// If using software SPI (the default case):
#define OLED_MOSI   D0
#define OLED_CLK    D1
#define OLED_DC     D2
#define OLED_CS     D3
#define OLED_RESET  D4
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
*/

// use hardware SPI
#define OLED_DC     D3
#define OLED_CS     D4
#define OLED_RESET  D5
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);


// setup() runs once, when the device is first turned on.
void setup() {

  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();


  Particle.function("draw", handleDraw);
  Particle.function("clear", handleClear);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  delay( 10 );
  //drawRandomPixel();
}

int handleDraw( String command ){

  if( command == "PIXEL" ){

    drawRandomPixel();

  }else if( command == "CIRCLE" ){

    drawRandomCircle();

  }
  return 1;

}

int handleClear( String command ){

  display.clearDisplay();
  return 1;
}

void drawRandomPixel(){
  int x = random( 0, 127 );
  int y = random( 0, 63 );
  display.drawPixel( x, y, WHITE);
  display.display();
}

void drawRandomCircle(){
  int x = random( 0, 127 );
  int y = random( 0, 63 );
  int radius = random( 1, 10 );
  display.drawCircle( x, y, radius, WHITE );
  display.display();
}
