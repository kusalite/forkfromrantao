/*
Project: Sleepy Hi
Discription: This device will create a soothing environment to help those that suffer from insomnia and night anxiety, to fall asleep
Author: Ammani
Date: 4/29/2017
Version: 1.3
*/
#include "neopixel.h"
#define PIXEL_PIN D5
#define PIXEL_COUNT 30
#define PIXEL_TYPE SK6812RGBW
// Currently, I think this is what is sent to the serial as output verification data. Haven't deleted it because I'm sure
// To understand more about this, look at DFplayer_basic_sample.ino in the audio folder
Adafruit_NeoPixel ring = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]
# define STATE_OFF 0
# define STATE_WELCOME 1 // When you switch on device
# define STATE_LISTENING 2 // When the device is monitering your movement and light
# define STATE_PRIMARY 3 // When the device is putting you to sleep
# define STATE_SECONDARY 4 //  When the device detects you might be waking up and responds minimally to put you back to sleep


int onSwitch = A0;
int aromapin = D2; // Output to diffuser
int Command; // Input for the DF Player
int Parameter1; // Input for the DF Player
int Parameter2; // Input for the DF Player
int state = 0;
int pirState = D0;
int pirSense = 0;
int head  = 0;
int tail = -10; // Index of first 'on' and 'off' pixels

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(aromapin, OUTPUT);   //smell number 1 control pin
  pinMode(onSwitch, INPUT);
  Particle.subscribe( "ammani/movement" , callingMovement );
  pinMode(pirState, INPUT);
  ring.begin();
  ring.show();
  Particle.variable("pir", &pirSense, INT);
  delay(30); // Pretty long delays between succesive commands needed (not always the same)
  // Initialize sound to very low volume. Adapt according used speaker and wanted volume
    //Initialises the MP3 player
  execute_CMD(0x3F, 0, 0);
  execute_CMD(0x06, 0, 30);
  execute_CMD(0x16, 0 , 1);
}

void loop()
{
  Serial.println(digitalRead(pirState));
  delay(100);
  switch( state )
  { case STATE_OFF:
      doOffState();
      break;
    case STATE_WELCOME:
      Serial.println("Welcome State");
      doWelcomeState();
      break;
    case STATE_LISTENING:
    //Serial.println("Listening State");
      doListeningState();
      break;
    case STATE_PRIMARY:
    //  Serial.println("Primary State");
      doPrimaryState();
      break;
    case STATE_SECONDARY:
      Serial.println("Secondary State");
      doSecondaryState();
      break;
  }
}


long lastDebounceTime = 0;
long debounceDelay = 3000;
long lastMovementCalled = 0;
bool primaryStateOn = FALSE;
bool movement = FALSE;
long enteredWelcomeStateAt = -1;
bool secondaryStateOn = FALSE;
long lightcheck = 0;

void doOffState(){
    off();
    execute_CMD(0x16, 0 ,1);
    Serial.println("Off state");
    delay(500);
    if (analogRead(onSwitch) < 100){
    state = STATE_WELCOME;
    }
}

void doWelcomeState()
{
  if( enteredWelcomeStateAt == -1 ) enteredWelcomeStateAt = millis();
  star();
  //hueChase(ring.Color(10, 80, 0), 150); // Lime Green
  if (analogRead(onSwitch) > 100){
    off();
    enteredWelcomeStateAt = -1;
    lastDebounceTime = millis();
    head  = 0;
    tail = -10;
    state  = STATE_OFF;
    }
  else if( enteredWelcomeStateAt + 8000 < millis() )
  {
    lastDebounceTime = millis();
    enteredWelcomeStateAt = -1;
    head  = 0;
    tail = -10;
    changeColor(ring.Color(10,160,0,0));
    Serial.println("listeningstate");
    state = STATE_LISTENING;
  }
}

void doListeningState()
{
  pirSense = digitalRead(pirState);
  if (analogRead(onSwitch) > 100){
    off();
    state  = STATE_OFF;
    }
  else if (movement == TRUE )
    {
      movement == FALSE;
      secondaryStateOn = TRUE;
      state = STATE_SECONDARY;
    }
  else if ( lastDebounceTime + debounceDelay < millis())
    {if (pirSense == 1)
    {
      //Serial.println("Pirlistening");
      lastDebounceTime = millis();
      primaryStateOn = TRUE;
      //execute_CMD(0x01,0,0);   //Plays the next track in SD card once timer is started
      state = STATE_PRIMARY;
    }
    }

}

bool isPrimaryStatePlaying = false;
bool aromaOn = false;
long startedPlayingAt = -1;
int primaryStateDuration = 1000 * 30;
int aromaStartTime = -1;
int aromaTime = 1000 * 10;

void doPrimaryState(){
  pirSense = digitalRead(pirState);
  Serial.println("primarystate");
  Serial.println(millis()-aromaStartTime);
  yellowcolor();
  if (primaryStateOn == TRUE and isPrimaryStatePlaying == FALSE)
    {
      Serial.println("2nd loop");
      startedPlayingAt = millis();
      aromaStartTime = millis();
      aromaOn = true;
      execute_CMD(0x01,0,1);   //Plays the next track in SD card once timer is started
      digitalWrite(aromapin,HIGH);
      isPrimaryStatePlaying = true;
      Serial.println("aroma on");
    }
  if (aromaOn)
    {
      if (aromaStartTime + aromaTime < millis())
      {
        digitalWrite(aromapin, LOW);
        aromaOn = false;
        Serial.println("aroma off");
      }
    }
  else
    //Serial.println("it reached!");
    if ( aromaStartTime + 20000 < millis())
    {
      digitalWrite(aromapin,HIGH);
      Serial.println("aroma on");
      aromaStartTime = millis();
    }
  if( isPrimaryStatePlaying && startedPlayingAt + primaryStateDuration < millis() )
    {
      primaryStateOn = FALSE;
      isPrimaryStatePlaying = FALSE;
      changeColor(ring.Color(10,160,0,0));
      Serial.println("3rdloop");
      digitalWrite(aromapin, LOW);
      Serial.println("aroma off");
      Serial.println("listeningstate");
      aromaStartTime = -1;
      startedPlayingAt = -1;
      state = STATE_LISTENING;
    }
  else
    {
      //return; //
    }

  if (analogRead(onSwitch) > 100){
      off();
      state  = STATE_OFF;
      }
  else if (lastDebounceTime + debounceDelay < millis())
  {
    if (pirSense == 1)
    {
      Serial.println("The Pir break");
      lastDebounceTime = millis();
      execute_CMD(0x16,0,1);
      primaryStateOn = FALSE;
      isPrimaryStatePlaying = FALSE;
      digitalWrite(aromapin, LOW);
      Serial.println("aroma off");
      changeColor(ring.Color(10,160,0,0));
      state = STATE_LISTENING;

    }
  }

}

bool isSecondaryStatePlaying = false;
long startedSecondaryPlayingAt = -1;
int secondaryStateDuration = 1000 * 30;

void doSecondaryState(){
  pirSense = digitalRead(pirState);
  Serial.println("secondary state");
  Serial.println(millis()-aromaStartTime);
  greencolor();
  if (secondaryStateOn == TRUE and isSecondaryStatePlaying == FALSE)
    {
      Serial.println("2nd loop");
      startedSecondaryPlayingAt = millis();
      aromaStartTime = millis();
      aromaOn = true;
      execute_CMD(0x01,0,1);   //Plays the next track in SD card once timer is started
      digitalWrite(aromapin,HIGH);
      isSecondaryStatePlaying = true;
      Serial.println("aroma on");
    }
  if (aromaOn)
    {
      if (aromaStartTime + aromaTime < millis())
      {
        digitalWrite(aromapin, LOW);
        aromaOn = false;
        Serial.println("aroma off");
      }
    }
  else
    //Serial.println("it reached!");
    if ( aromaStartTime + 20000 < millis())
    {
      digitalWrite(aromapin,HIGH);
      Serial.println("aroma on");
      aromaStartTime = millis();
    }
  if( isSecondaryStatePlaying && startedSecondaryPlayingAt + secondaryStateDuration < millis() )
    {
      secondaryStateOn = FALSE;
      isSecondaryStatePlaying = FALSE;
      changeColor(ring.Color(10,160,0,0));
      Serial.println("3rdloop");
      digitalWrite(aromapin, LOW);
      Serial.println("aroma off");
      Serial.println("listeningstate");
      aromaStartTime = -1;
      startedSecondaryPlayingAt = -1;
      state = STATE_LISTENING;
    }
  else
    {
      //return; //
    }

  if (analogRead(onSwitch) > 100){
      off();
      state  = STATE_OFF;
      }
  else if (lastDebounceTime + debounceDelay < millis())
  {
    if (pirSense == 1)
    {
      Serial.println("The Pir break");
      lastDebounceTime = millis();
      execute_CMD(0x16,0,1);
      secondaryStateOn = FALSE;
      isSecondaryStatePlaying = FALSE;
      digitalWrite(aromapin, LOW);
      Serial.println("aroma off");
      changeColor(ring.Color(10,160,0,0));
      state = STATE_LISTENING;

    }
  }

}




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

void yellowcolor(){
  for(int i = 0; i <= 10; i += 5) {
    changeColor(ring.Color(i,i*13,0,0));
    delay(50);
  }
  delay(500);
  for(int i = 10; i >= 0; i -= 5) {
    changeColor(ring.Color(i,i*13,0,0));
    delay(50);
  }
}

void greencolor(){
  for(int i = 0; i <= 10; i += 5) {
    changeColor(ring.Color(i,i*10,0,0));
    delay(50);
  }
  delay(500);
  for(int i = 10; i >= 0; i -= 5) {
    changeColor(ring.Color(i,i*10,0,0));
    delay(50);
  }
}

void hueChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<5; j++) {
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < ring.numPixels(); i=i+3) {
        ring.setPixelColor(i+q, c);
        delay(1);
      }
      ring.show();
      delay(wait);

      for (uint16_t i=0; i < ring.numPixels(); i=i+3) {
        ring.setPixelColor(i+q, 0);
        delay(1);
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
  if (data == "yes"){
  moving();
  }
}

void moving()
{
  if ( lastMovementCalled + 20000 < millis() )
  {
  lastMovementCalled = millis();
  movement == TRUE;
  }
}

uint32_t color = 0x00ff08;      // 'On' color (starts red)

void star(){
  ring.setPixelColor(head, color); // 'On' pixel at head
  ring.setPixelColor(tail, 0);     // 'Off' pixel at tail
  ring.show();                     // Refresh strip
  delay(5);                        // Pause 20 milliseconds (~50 FPS)

  if(++head >= ring.numPixels()) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
    /*if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
      color = 0xFF0000;             //   Yes, reset to red*/
  }
  if(++tail >= ring.numPixels()) tail = 0; // Increment, reset tail index
}
