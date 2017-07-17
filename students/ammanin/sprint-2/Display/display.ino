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

// width: 128 height: 64
static const unsigned char brain[] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xBF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x1F, 0x4F, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xDF, 0x1F, 0x1F, 0x3F, 0xDF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x47, 0x77,
  0xF7, 0xE7, 0xE6, 0xE1, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x80, 0x08, 0x1C, 0x0E, 0x2E, 0x3F, 0x3F,
  0x3F, 0x37, 0x06, 0x0E, 0x00, 0x80, 0x01, 0x03, 0x03, 0x83, 0x03, 0x1F, 0x1D, 0xCF, 0xEF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0x73, 0x67,
  0x5A, 0x9A, 0xBB, 0xFF, 0xFF, 0x4F, 0x01, 0x10, 0x40, 0x06, 0x2F, 0x1F, 0x16, 0xFC, 0xFC, 0x7C,
  0xFC, 0xFE, 0xFE, 0xFF, 0xCF, 0x1F, 0x08, 0x40, 0x01, 0x7F, 0xFF, 0xFB, 0xFA, 0x60, 0x70, 0x70,
  0x76, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0x9F, 0xEB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF,
  0xFF, 0xDF, 0xDF, 0xDF, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0xC3, 0xF8,
  0x73, 0x87, 0x03, 0x03, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0xB3, 0xFF, 0xFF, 0xFF, 0xF3, 0xC0,
  0xF6, 0xB6, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFE, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x9F, 0x9F, 0x4F, 0xCF, 0xCF,
  0xC7, 0xCF, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x30, 0x78, 0x3C, 0x3C, 0x1E, 0x0C, 0x0E, 0x04, 0x87,
  0x86, 0x07, 0x0E, 0x1E, 0x3C, 0x7C, 0x78, 0x30, 0x00, 0x00, 0x0F, 0x1F, 0x1F, 0x1F, 0x6F, 0xEB,
  0xFB, 0xF3, 0xE3, 0xF5, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCE, 0xEF, 0xF7,
  0xF7, 0xE7, 0xE3, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x1C, 0xF8, 0xF0, 0xC0, 0xC6, 0xFE, 0xFF,
  0xFF, 0xD8, 0xC0, 0xE0, 0x70, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC2, 0xC6, 0x8E, 0xBE,
  0xFE, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F,
  0xFF, 0xFF, 0xFF, 0xF8, 0xFC, 0xFF, 0xF8, 0xF8, 0xF0, 0xF8, 0xF6, 0xE7, 0xC7, 0xF1, 0xFF, 0xFF,
  0xF3, 0x83, 0xEF, 0xE6, 0x00, 0xB8, 0xF8, 0xFC, 0xFF, 0xFF, 0xF7, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFE, 0xFF, 0xFD, 0xFF, 0xFB, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xEF,
  0xEF, 0xEF, 0xFF, 0xEF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x5F, 0x9F, 0xCF, 0xDF, 0xDF, 0xFF, 0xCF, 0x1F, 0x7F, 0x0F, 0xCF, 0x7F, 0x7F, 0x0F, 0x2F, 0x1F,
  0xCF, 0x1F, 0x9F, 0xEF, 0x3F, 0x0F, 0xBF, 0xCF, 0xFF, 0xAF, 0x4F, 0xAF, 0x4F, 0x7F, 0x0F, 0x9F
};


// width: 128 height: 64

// setup() runs once, when the device is first turned on.
void setup() {

  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();

  // miniature bitmap display
  display.clearDisplay();
  // void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
  display.drawBitmap(0, 0,  brain, 64, 32, 1);
  display.display();
  Particle.function("clear", handleClear);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  delay( 10 );
}

int handleClear( String command ){

  display.clearDisplay();
  return 1;
}
