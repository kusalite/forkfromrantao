#include "24neopixelring.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D4
#define PIXEL_COUNT 24
#define PIXEL_TYPE SK6812RGBW
#define BRIGHTNESS 50 // 0 - 255

#define STATE_MAT_OPEN 0
#define STATE_MAT_CLOSED 1

Adafruit_NeoPixel standStrip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int hallPin = D0;
int greenIndicatorPin=D1;
int redIndicatorPin=D2;
int matDetectionPin=D3;

int currentVal=LOW;
int lastVal=LOW;

void setup() {

  Serial.begin(9600);
  Serial.println("Setup complete");
  Particle.subscribe("advait/matopening",matOpen);
  Particle.subscribe("advait/matclosing",matClose);

  // add the neopixels
  standStrip.begin();
  standStrip.show();
  /*standStrip.setBrightness( BRIGHTNESS );*/

  pinMode(hallPin, INPUT_PULLUP);
  pinMode(greenIndicatorPin, OUTPUT);
  pinMode(redIndicatorPin, OUTPUT);
  pinMode(matDetectionPin,INPUT_PULLUP);
}

void loop() {

  checkMatState();

  delay(200);

  Serial.println("Loop running.");

}

void checkMatState() {
  currentVal = digitalRead(matDetectionPin);
  Serial.printf("The mat detection value is: %d\n",currentVal);

  if(currentVal==LOW and lastVal==HIGH)
  {
    Particle.publish("advait/matclosing");
    /*Serial.println("Mat closing.");*/
  }
  else if(currentVal==HIGH and lastVal==LOW)
  {
    Particle.publish("advait/matopening");
    /*Serial.println("Mat opening.");*/
  }

  lastVal=currentVal;
}

void matOpen(const char *event,const char *data)
{
  Serial.println("Mat Opening");
  blinkLedOpen();
}

void lightUpStand()
{
  Serial.println("Lighting up stand.");

  for(int j=0;j<3;j++)
  {
    uint32_t c = standStrip.Color( 0, 0, 255, 0);
    for(int i=0;i<standStrip.numPixels();i++)
    {
      standStrip.setPixelColor(i,c);
      Serial.println("Setting pixel color.");
    }

    standStrip.show();

    delay(500);

    for(int i=0;i<standStrip.numPixels();i++)
    {
      standStrip.setPixelColor(i,0);
    }

    standStrip.show();

    delay(500);
  }
}

void matClose(const char *event,const char *data)
{
  Serial.println("Mat Closing");
  blinkContactLed(4);
}

void blinkLedOpen(int num)
{
  for(int i=0;i<num;i++)
  {
    digitalWrite(greenIndicatorPin, HIGH); //green led blinks
    delay(100);
    digitalWrite(greenIndicatorPin, LOW); //green led blinks
    delay(100);
  }
}

void blinkLedClose()
{
  for(int i=0;i<3;i++)
  {
    digitalWrite(redIndicatorPin, HIGH); //red led blinks
    delay(100);
    digitalWrite(redIndicatorPin, LOW); //red led blinks
    delay(100);
  }
}
