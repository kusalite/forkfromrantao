#include "neopixel.h" // use for local build
#include <math.h>

// IMPORTANT: Set pixel PIN, COUNT, and TYPE
// Supported pixel types: WS2812, WS2812B, WS2812B2, WS2811, TM1803, TM1829, SK6812RGBW
#define TIMER_PIN D5
#define NEOPIXEL_COUNT 16
#define TIMER_COUNT 5
#define TIMER_PIXEL_TYPE WS2812
#define BRIGHTNESS 50 // 0 - 255

Adafruit_NeoPixel timer_strip = Adafruit_NeoPixel(NEOPIXEL_COUNT, TIMER_PIN, TIMER_PIXEL_TYPE);
int touchPin=A1;
unsigned long time_now = millis();
bool set_timer=false;
int numb_strips_buffer=0;
int timer_on=false;
unsigned long timer_start = millis();
int vibratorPin = A4;
int heartPin = A2;
int fsrPin = A1;

/*bool timerLights[5]={false,false,false,false,false};*/
int timer_period = 1*60*1000;//timer set to
Timer timer(timer_period,timerCompleted,true);

void setup(){
  Serial.begin(9600);
  pinMode(touchPin,INPUT_PULLUP);
  pinMode(heartPin,INPUT_PULLUP);
  pinMode(vibratorPin, OUTPUT);
  initializeTimerLED();
}

void loop(){
  int i = analogRead(touchPin);
  Serial.println(i);

  /*//Read and print values from Heart Sensor
  int heart = analogRead(heartPin);
  if(heart>20)
    Serial.printf("Heart value is: %d\n",heart);*/

  //Read and print values from FSR
  /*int fsr = analogRead(fsrPin);
  if(fsr>20)
    Serial.printf("Pressue value is: %d\n",fsr);*/

  //Light up the timer
  if(i>20)
  {
    timer_strip.setBrightness(BRIGHTNESS);
    timerLightControl(i);
  }
  else
  {
    breathe();
    analogWrite(vibratorPin, 0.0);
  }

  /*delay(100);*/
}

void initializeTimerLED()
{
    timer_strip.setBrightness(BRIGHTNESS);
    timer_strip.begin();

    for(uint16_t i = 0 ; i < NEOPIXEL_COUNT ; i++)
    {
        timer_strip.setPixelColor(i, 0, 0, 0, 0); //colors stay blank
    }

    timer_strip.show();
}

void timerLightControl(int touch){
  int i=0;

  i=touch/800+1; //Calculates # of lights to light up

  if(i>5)
    i=5;

  timerLightSet(i);
}

void timerLightSet(int numb_strips)
{
  if(numb_strips==0)
  {
    //The touch pot has not been touched
    //Turn all LEDs off
    display_timer(numb_strips);
    set_timer=false;
  }
  else
  {
    //If current value from touchpout is same as previous value for 3 secs then timer is set
    if(numb_strips_buffer != numb_strips)
    {
      time_now=millis();
      set_timer=false;
    }
    else if(millis()-time_now>2000)
    {
      set_timer=true;
      time_now = millis();
    }
    else
      set_timer=false;

    display_timer(numb_strips);
  }

  numb_strips_buffer = numb_strips;

  if(set_timer)
    timerSet(numb_strips);
}

//Sets the timer once the user has swiped the touch bar
void timerSet(int numb_strips)
{
  Serial.println("Setting timer!");

  if(numb_strips!=0)
  {
    //Blink the LEDs thrice when the timer is set
    for(int i=0;i<3;i++)
    {
      initializeTimerLED();

      delay(300);

      display_timer(numb_strips);

      delay(300);

      Serial.println("Blinking LEDs!");
    }

    /*timer.changePeriod(numb_strips*10*60*1000);
    timer.start();*/
    timer_start = millis();
    timer_on=true;
    Serial.println("Timer has started!");

    timerCountdown(numb_strips);
  }
}

//Counts down the timer updating the LEDs and sending vibration
void timerCountdown(int numb_strips)
{
    int strips_left = numb_strips;

    /*while(timer_on)
    {
      unsigned long time_now = millis();

      for(int i=numb_strips;i>0;i--)
      {
        display_timer(i);

        while(millis()-time_now<5000) //vibrates for 5sec per LED strip
          vibrate();

        Serial.printf("Counting down timer %d \n",i);
      }

      timer_on=false;
    }*/

    while(strips_left>0)
    {
      unsigned long time_now = millis();

      while(millis()-time_now<5000)
      {
        vibrate();
      }

      Serial.printf("Counting down timer %d \n",strips_left);

      strips_left--;
      display_timer(strips_left);
    }
    analogWrite(vibratorPin, 0.0);
    breathe();
}

void display_timer(int strips_lit)
{
  if(strips_lit==0)
  {
    for(int i=0;i<NEOPIXEL_COUNT;i++)
    {
      timer_strip.setPixelColor(i,0,0,0);
    }
  }
  else
  {
    Serial.printf("Lighting up LEDs %d \n",strips_lit);
    for(int i=0;i<NEOPIXEL_COUNT;i++)
    {
      if(i<strips_lit)
        timer_strip.setPixelColor(i,timer_strip.Color(0,255,0));
      else
        timer_strip.setPixelColor(i,0);
    }
  }

  timer_strip.show();
}

void breathe()
{
  Serial.printf("Breathing!");

  int i;

  //First setting pixel color of all pixels to green
  for(i=0; i< NEOPIXEL_COUNT; i++) {
    if(i<TIMER_COUNT)
      timer_strip.setPixelColor(i, 0, 255, 0);
    else
      timer_strip.setPixelColor(i,0,0,0);
  }
  timer_strip.show();

  delay (100);
  //
  int x = 1;
  for (int ii = 1 ; ii <100 ; ii = ii + x){
    timer_strip.setBrightness(ii);
    timer_strip.show();
    delay(10);
   }
   x = 1;
  for (int ii = 100 ; ii > 3 ; ii = ii - x){
    timer_strip.setBrightness(ii);
    timer_strip.show();
    delay(10);
    }
  delay(2);
  x = 1;
  for (int ii = 1 ; ii <100 ; ii = ii + x){
    timer_strip.setBrightness(ii);
    timer_strip.show();
    delay(10);
    }
  x = 1;
  for (int ii = 100 ; ii > 1 ; ii = ii - x){
    timer_strip.setBrightness(ii);
    timer_strip.show();
    delay(10);
  }
  delay (100);
}

void timerCompleted()
{
  timer.reset();
  timer_on=false;
  breathe();
  //Voice note or earcon to tell user that it's over
}

void vibrate()
{
<<<<<<< HEAD
  float val = abs(float(sin(float(millis())/10000 * 3.14159)*120));
=======
  float val = abs(float(sin(float(millis())/5000 * 3.14159)*150));
>>>>>>> master
  /*val= val*80+100;*/
  //val = (exp(time_constant) - 0.36787944)*200;
  Serial.printf("Vibrating with %f!\n",val);
  analogWrite(vibratorPin, val);
}
