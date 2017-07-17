#include "neopixel.h" // use for local build
#include <math.h>

// IMPORTANT: Set pixel PIN, COUNT, and TYPE
// Supported pixel types: WS2812, WS2812B, WS2812B2, WS2811, TM1803, TM1829, SK6812RGBW
#define TIMER_PIN D5
#define TIMER_COUNT 5

#define CENTER_PIN D6
#define CENTER_COUNT 15

#define TIMER_PIXEL_TYPE WS2812
#define CENTER_PIXEL_TYPE SK6812RGBW
#define BRIGHTNESS 50 // 0 - 255

//Input: Timer touch strip(5), pressure sensors(3), heart rate monitor (2), Yoga/meditation mode (1)
//Output: Vibrators(1), Timer LED(1), Center LED(1)
bool rolling,rolled = false;
int touchPins[TIMER_COUNT]={D0,D1,D2,D3,D4}; //I/P: Pins for timer touch strip
int modePin=D7;
int pressurePins[3]={A0,A1,A2}; //I/P: Pins for 3 pressure sensors
int heartPins[2]={A3,A4};//I/P: Pins for measuring heart rate and stress
int vibratorPin=A5;//O/P: Pins to provide meditative vibration

Adafruit_NeoPixel timer_strip = Adafruit_NeoPixel(TIMER_COUNT, TIMER_PIN, TIMER_PIXEL_TYPE);
Adafruit_NeoPixel center_ring = Adafruit_NeoPixel(CENTER_COUNT, CENTER_PIN, CENTER_PIXEL_TYPE);

void setup()
{
  Serial.begin(9600);
  initializePins();
  initializeCloud();
  initializeTimer();
  initializeCenter();
}

void initializeTimer()
{
    timer_strip.setBrightness(BRIGHTNESS);
    timer_strip.begin();

    for(uint16_t i = 0 ; i < 5 ; i++)
    {
        timer_strip.setPixelColor(i, 0, 0, 0, 0); //colors stay blank
        timer_strip.show();
    }
}

void initializeCenter()
{
    center_ring.setBrightness(BRIGHTNESS);
    center_ring.begin();

    for(uint16_t i = 0 ; i < 15 ; i++)
    {
        center_ring.setPixelColor(i, 0, 0, 0, 0); //colors stay blank
        center_ring.show();
    }
}

void initializePins()
{
  for(int i=0;i<5;i++)
  {
    pinMode(touchPins[i], INPUT);
  }

  for(int i=0;i<3;i++)
  {
    pinMode(pressurePins[i], INPUT);
  }

  for(int i=0;i<2;i++)
  {
    pinMode(heartPins[i], INPUT);
  }

  pinMode(vibratorPin,OUTPUT);
}

void initializeCloud(){}

void loop()
{
  /*float start = analogRead(startPin);*/
  rolling = start > 2000 ? true : false;

  if(rolling)
  {
    //make LEDs breath for about 5 secs
    //switch on mat

    //center lights switch on (not used for frequent use)

    //timerControl() checks if timer sensor has been touched and set
    //once timer has been set, center lights switched on
    //once pressure sensor detects that person is sitting and meditation button on, meditation starts

  }
}

void timerControl()
{
  int touchSense[5];
  for(int i=0;touchSense.length())
}

void frontLightControl(String control)
{
  unsigned long time_now = millis();

  if(control=="open mat")
  {
    //Lights breathe when opening the mat
    while(millis()-time_now<5000)
    {
      float brightness = 200*sin(millis()/2000.0 * M_PI)) - 0.36787944);
      for(int i=0;i<TIMER_COUNT;i++)
      {
        timer_strip.setPixelColor(i, 0, 0, 255, 0);
      }
      timer_strip.setBrightness(brightness);
      timer_strip.show();
    }
  }
  else if(control=="timer")
  {
    //Lights brighten depending on which strip has been touched
  }
  else if(control=="timer confirmed")
  {
    //Light pattern when the user has let go of the touch strip
  }
}
