
/*
Project: Sleepy Hi
Discription: This device will create a soothing environment to help those that suffer from insomnia and night anxiety, to fall asleep
Author: Ammani
Date: 4/17/2017
Version: 1.2

*/
#include "neopixel.h"
#define PIXEL_PIN D5
#define PIXEL_COUNT 20
#define PIXEL_TYPE SK6812RGBW
// Currently, I think this is what is sent to the serial as output verification data. Haven't deleted it because I'm sure
// To understand more about this, look at DFplayer_basic_sample.ino in the audio folder
Adafruit_NeoPixel ring = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]
# define STATE_WELCOME 0 // When you switch on device
# define STATE_LISTENING 1 // When the device is monitering your movement and light
# define STATE_PRIMARY 2 // When the device is putting you to sleep
# define STATE_SECONDARY 3 //  When the device detects you might be waking up and responds minimally to put you back to sleep

int aromapin = D0; // Output to diffuser
int ambilight = A0;// This is the input from the ambient light sensor
int Command; // Input for the DF Player
int Parameter1; // Input for the DF Player
int Parameter2; // Input for the DF Player
int state = 0;    // This is for the backround interut task, WHICH ISN'T WORKING
int pirState = D2;
int pirSense = 0;
long lastDebounceTime = 0;
long debounceDelay = 5000;
long lastMovementCalled = 0;
bool primaryStateOn = FALSE;
bool movement = FALSE;
void setup()
{
  Serial.begin(9600);
  pinMode(aromapin, OUTPUT);   //smell number 1 control pin
  pinMode(ambilight, INPUT);

  Particle.subscribe( "ammani/movement" , callingMovement );
  pinMode(pirState, INPUT);
  ring.begin();
  ring.show();
  Serial.print("aromapin high");
  // execute_CMD(0x3F, 0, 0); // Send request for initialization parameters for the DFplayer
  Particle.variable("pir", &pirSense, INT);
  delay(30); // Pretty long delays between succesive commands needed (not always the same)
  //attachInterrupt( pirState, handleChangeState, RISING);// if someone waves their hand in front of the device, it will interrupt any state and move to the alternative
  // Initialize sound to very low volume. Adapt according used speaker and wanted volume
  execute_CMD(0x05, 0, 1); // Set the volume (0x00~0x30)

}

void loop()
{
  switch( state )
  {
    case STATE_WELCOME:
      Serial.println("Welcome State");
      doWelcomeState();
      break;
    case STATE_LISTENING:
      Serial.println("Listening State");
      doListeningState();
      break;
    case STATE_PRIMARY:
      doPrimaryState();
      break;
    case STATE_SECONDARY:
      doSecondaryState();
      break;
  }
}



/*void handleChangeState()
{
  //if current time minus the last trigger time is greater than

  //switch was pressed, do whatever you need to here

  switch( state )
  {
    case STATE_WELCOME:
      // Start pulsing Light
      // It checks if the light is out
      state = STATE_PRIMARY;
      break;
    case STATE_LISTENING:
      // It checks if the light is out and if you're moving to see if you're coming out of sleep
      state = STATE_SECONDARY;
      break;
    case STATE_PRIMARY:
      //Durin this state, the device is actuating the light, aroma and music. The state changes after a set period of time
      state = STATE_LISTENING;
      break;
    case STATE_SECONDARY:
      // During this state, only the aroma and music is actuated. The sound will be softer and the diffuser will be set off less frequently
      state = STATE_LISTENING;
      break;
  }

}*/

void doWelcomeState()
{
  greencolor();
  Serial.println("No Green?");
  pirSense = digitalRead(pirState);

  if (millis() > 10000)
  {
    lastDebounceTime = millis();
    primaryStateOn = TRUE;
    state = STATE_PRIMARY;
  }
}

void doListeningState()
{
  pirSense = digitalRead(pirState);
  // if (ambilight = LOW) && movement is minimal
  bluecolor();

  if ( millis() > ( lastDebounceTime + debounceDelay))
  {if (pirSense == 1)
  {
    lastDebounceTime = millis();
    primaryStateOn = TRUE;
    state = STATE_PRIMARY;
  }

  }
  if (movement == TRUE )
  {
    movement == FALSE;
    primaryStateOn = TRUE;
    state = STATE_PRIMARY;
  }
  //state = STATE_SECONDARY;
}

void doPrimaryState()
{
  pirSense = digitalRead(pirState);
  redcolor();
  if (primaryStateOn = TRUE)
  {
    digitalWrite(aromapin,HIGH);
    delay(1000);
    digitalWrite(aromapin,LOW);
    primaryStateOn = FALSE;
  }
  // In future I will code out the intervals and timings.

  if (millis() > ( lastDebounceTime + debounceDelay))
  {if (pirSense == 1)
  {
    lastDebounceTime = millis();
    state = STATE_LISTENING;
  }
}
  //digitalWrite(aromapin, HIGH); //turns smell 1 on the smell release
  // E.g. 3,0,1 (or 3 0 1 or 3;0;1) will play first track on the TF-card
  // Excecute the entered command and parameters
  //execute_CMD(Command, Parameter1, Parameter2);
  // At the End

  //state = STATE_LISTENING;

}

void doSecondaryState()
{
  // In future I will code out the intervals and timings.
  //digitalWrite(aromapin, HIGH); //turns smell 1 on the smell release
  // E.g. 3,0,1 (or 3 0 1 or 3;0;1) will play first track on the TF-card
  // Excecute the entered command and parameters
  //execute_CMD(Command, Parameter1, Parameter2);
  // At the End
  //state = STATE_LISTENING;
}

/*void moving( movementx, movementy, movementz)
{
  using the variables from the accelerometer, check if the person is moving enough to suggest they are waking up or awake
}*/

/*void lightsOut()
{
  check if there is light in the room
}*/

// Code used for the DFplayer
void execute_CMD(byte CMD, byte Par1, byte Par2) // Excecute the command and parameters
{
 // Calculate the checksum (2 bytes)
 int16_t checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

 // Build the command line
 byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge, Par1, Par2, checksum >> 8, checksum & 0xFF, End_Byte};

 //Send the command line to the module
 for (byte k=0; k<10; k++)
 {
  Serial1.write( Command_line[k]);
 }
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

void changeColor(uint32_t color) {
  for(uint16_t i=0; i < ring.numPixels(); i++) {
    ring.setPixelColor(i, color);
    ring.show();
  }
}

void callingMovement(const char *event, const char *data)
{
  Serial.println("Reached Calling Movement Handler");
  moving();
}

void moving()
{
  if (millis() > ( lastMovementCalled + 900000))
  {
  lastMovementCalled = millis();
  movement == TRUE;
  }
}
