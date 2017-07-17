
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

  display.clearDisplay();   // clears the screen and buffer
  display.setCursor(0,0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Welcome");

  display.setTextSize(1);
  display.println("Send a message");
  display.println("With Particle.function");

  display.display();

  Particle.function("draw", handleDraw);
  Particle.function("clear", handleClear);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

  delay( 10 );

}

int handleDraw( String command ){

  display.clearDisplay();   // clears the screen and buffer
  display.setCursor(0,0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println(command);
  display.display();

  return 1;

}

int handleClear( String command ){

  display.clearDisplay();
  return 1;
}
