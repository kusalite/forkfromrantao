#include "neopixel.h" // use for local build
#include <math.h>

// IMPORTANT: Set pixel PIN, COUNT, and TYPE
// Supported pixel types: WS2812, WS2812B, WS2812B2, WS2811, TM1803, TM1829, SK6812RGBW
#define TIMER_PIN D5
#define NEOPIXEL_COUNT 16
#define TIMER_COUNT 5
#define TIMER_PIXEL_TYPE WS2812
#define BRIGHTNESS 50 // 0 - 255

//Byte values for the MP3 players
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

Adafruit_NeoPixel timer_strip = Adafruit_NeoPixel(NEOPIXEL_COUNT, TIMER_PIN, TIMER_PIXEL_TYPE);

//Defining the pins
int touchPin=A1;
int heartPin = A2;
int fsrPin = A3;
int vibratorPin = A4;

unsigned long time_now = millis();
bool set_timer=false;//Checks if timer needs to be set
int timer_on=false; //Checks if timer is on

int numb_strips_buffer=0;//Temporary value of # of strips lit up
unsigned long timer_start = millis();

int timer_period = 1*60*1000;//not being used
Timer timer(timer_period,timerCompleted,true);//not being used

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);//Serial 1 used to communicate with MP3 Player

  execute_CMD(0x3F, 0, 0);//Initialises the MP3 player
  execute_CMD(0x06, 0, 75);//Sets volume of MP3 player to 75

  pinMode(touchPin,INPUT_PULLUP);
  pinMode(heartPin,INPUT_PULLUP);
  pinMode(vibratorPin, OUTPUT);

  initializeTimerLED();
}

void loop(){

  int i = 4095;
  // sample 6 times...
  for( int j = 0 ; j < 6; j++ ){
    int val = analogRead(touchPin);
    if( val < i )
      i = val;
    delay(20);
  }

  //int i = analogRead(touchPin);
  Serial.printf("The touch value is: %d \n",i);

  //Lights up the timer
  if(i>30)//Noise values from 0-20 usually exist
  {
    timer_strip.setBrightness(BRIGHTNESS);
    timerLightControl(i);
  }
  else
  {
    breathe();
    analogWrite(vibratorPin, 0.0);
  }

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

  i=touch/400+1; //Calculates # of lights to light up

  if(i>5)//Ensures that max of 5 lights are lit up
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
    //If current value from touchpout is same as previous value for 2 secs then timer is set
    if(numb_strips_buffer != numb_strips)
    {
      time_now=millis();
      set_timer=false;
    }
    else if(millis()-time_now>3000)
    {
      set_timer=true;
      time_now = millis();
    }
    else
      set_timer=false;

    display_timer(numb_strips);
  }

  numb_strips_buffer = numb_strips;

  //Officially sets the timer
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

    execute_CMD(0x01,0,1);//Plays the next track in SD card once timer is started

    while(strips_left>0)
    {
      unsigned long time_now = millis();

      Serial.println("Vibrating!");

      while(millis()-time_now<7500)//Each LED represents 7.5 secs of time
      {
        vibrate();
      }

      Serial.printf("Counting down timer %d \n",strips_left);

      strips_left--;//Decrements illuminated strips once a 7.5 sec period over
      display_timer(strips_left);//Displays the timer
    }

    execute_CMD(0x16,0,1);
    analogWrite(vibratorPin, 0.0);//Resets vibrator once timer is over
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

//Breathing lights indicate a functional mat
void breathe()
{
  Serial.printf("Breathing!");

  /*int i;*/


  //First setting pixel color of all pixels to green
  for(int i=0; i< NEOPIXEL_COUNT; i++) {
    if(i<TIMER_COUNT)
      timer_strip.setPixelColor(i, 0, 255, 0);
    else
      timer_strip.setPixelColor(i,0,0,0);
  }
  /*timer_strip.show();*/

  float val = abs(float(sin(float(millis())/10000 * 3.14159)*100));
  timer_strip.setBrightness(val);
  timer_strip.show();
  /*delay (100);

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
  delay (100);*/
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
  float val = abs(float(sin(float(millis())/10000 * 3.14159)*120));
  /*val= val*80+100;*/
  //val = (exp(time_constant) - 0.36787944)*200;
  /*Serial.printf("Vibrating with %f!\n",val);*/
  analogWrite(vibratorPin, val);
}

//Passes byte code to the MP3 Player via TX pins and serial module
void execute_CMD(byte CMD, byte Par1, byte Par2) // Execute the command and parameters
{
 // Calculate the checksum (2 bytes)
 int16_t checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

 // Build the command line
 byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge, Par1, Par2, checksum >> 8, checksum & 0xFF, End_Byte};

 //Send the command line to the serial module
 for (byte k=0; k<10; k++)
 {
  Serial1.write( Command_line[k]);
 }
}
