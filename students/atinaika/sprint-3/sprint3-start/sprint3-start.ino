#include "neopixelstrip.h"
#include "math.h"

# define STATE_WELCOME 0
# define STATE_WAITING 1
# define STATE_SELECTION 2
# define STATE_CONFIRMATION 3
# define STATE_MEDITATING 4
# define STATE_COMPLETED 5

# define MODE_MEDITATION 10
# define MODE_YOGA 11

// we also need a variable to store the state...

int state = 0;
int matMode;
int yogaButton= D0;
int meditationButton= D5;
int notifVibPin = D2;
int yogaLED = D3;
int matDetectionPin = D4;
int meditLED = D6;
int matContactLedPin = D7;
// We know we have a few inputs and output so
// set them up

//Defining the pins
int touchPin = A0;
int heartPin = A2;
int fsrPin = A3;
int meditVibPin = A4;

int softPotReading,fsrReading; //The sensor readings
int start,mid,end; //The start, mid and end period for the vibration
float vibVal;
int lastContactVal=LOW;
int volumeLevel=50;

//Byte values for the MP3 players
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D1
#define PIXEL_COUNT 5 //16
#define PIXEL_TYPE SK6812RGBW
#define BRIGHTNESS 50 // 0 - 255

Adafruit_NeoPixel timerStrip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {

  Serial.begin(9600);
  Serial.println("Setup complete");

  Serial1.begin(9600);//Serial 1 used to communicate with MP3 Player

  //Initialises the MP3 player
  sendMP3Command(0x3F, 0, 0);
  //Sets volume of MP3 player to 75
  sendMP3Command(0x06, 0, volumeLevel);
  //Stops a track if it is currently running
  sendMP3Command(0x16, 0, 1);

  matMode=10;

  pinMode(touchPin,INPUT_PULLUP);
  pinMode(heartPin,INPUT_PULLUP);
  pinMode(yogaButton,INPUT_PULLUP);
  pinMode(meditationButton,INPUT_PULLUP);
  pinMode(matDetectionPin, INPUT_PULLUP);

  pinMode(notifVibPin, OUTPUT);
  pinMode(meditVibPin, OUTPUT);
  pinMode(yogaLED, OUTPUT);
  pinMode(meditLED, OUTPUT);
  pinMode(matContactLedPin, OUTPUT);

  Particle.subscribe("advait/matopening",doMatOpening);
  Particle.subscribe("advait/matclosing",doMatClosing);

  // add the neopixels
  timerStrip.begin();
  timerStrip.show();
  timerStrip.setBrightness( BRIGHTNESS );
}

void loop() {

  // get the current reading
  checkMatState();
  sampleFromSoftPotentiometer();
  sampleFromFSR();
  updateModeBasedOnSensors();
  updateStatesBasedOnSensors();

  switch ( matMode ){
    case MODE_YOGA: doYogaMode(); break;
    case MODE_MEDITATION: doMeditationMode(); break;
  }

	// Our loop becomes a place to decide which state is shown
	// And nothing more.
	// Each separate function controls output and input independently

  switch( state ) {
   case STATE_WELCOME:      doWelcomeState(); break; //Cycles up and down the LEDs
   case STATE_WAITING:      doWaitingState(); break; //Breathes the LEDs
   case STATE_SELECTION:    doSelectingState(); break; //While touchput is being touched
   case STATE_CONFIRMATION: doConfirmationState(); break; //Start the timer and confirm it
   case STATE_MEDITATING:   doMeditatingState(); break; //Once meditation has started
   case STATE_COMPLETED:    doCompletedState(); break; //Once meditation has been completed
  }

  delay( 100 );
}

void checkMatState() {
  int currentVal = digitalRead(matDetectionPin);
  Serial.printf("The mat detection value is: %d\n",currentVal);

  if(currentVal==LOW and lastContactVal==HIGH)
  {
    Particle.publish("advait/matclosing");
    //Sleep Particle
    /*Serial.println("Mat closing.");*/
  }
  else if(currentVal==HIGH and lastContactVal==LOW)
  {
    Particle.publish("advait/matopening");
    //Wake Particle
    /*Serial.println("Mat opening.");*/
  }

  lastContactVal=currentVal;
}

/***************************
  PRACTISE TIME SELECTION STATE
***************************/

void updateStatesBasedOnSensors(){

  // If the user is touching then
  // update the state to
  // show the user selection
  if((softPotReading > 50) && state!=STATE_CONFIRMATION)
  {
    state = STATE_SELECTION;
  }
}

/***************************
  YOGA/MEDITATION SELECTION STATE
***************************/

void updateModeBasedOnSensors(){

  if(digitalRead(yogaButton)==LOW)
  {
    matMode = MODE_YOGA;
    Serial.println("Yoga Mode Selected");
  }
  else if(digitalRead(meditationButton)==LOW)
  {
    matMode = MODE_MEDITATION;
    Serial.println("Meditation Mode Selected.");
  }
  //If neither button pressed the same mode continues
}

void doYogaMode(){
  //Remember to play yoga music
  digitalWrite(yogaLED, HIGH);
  digitalWrite(meditLED, LOW);
}

void doMeditationMode(){
  //Remember to play meditation music
  digitalWrite(yogaLED, LOW);
  digitalWrite(meditLED, HIGH);
}

/***************************
  WELCOME STATE
***************************/

void doWelcomeState(){

  // blink the leds 3 times
  cycleUpLeds();
  // pulse vibration
  notifyWithVibration( 2 );
  // now move to the waiting state...
  state = STATE_WAITING;
}

/***************************
  WAITING STATE
  No activity until
  the user makes a selection
***************************/

void doWaitingState(){
  breathe();
}

/***************************
  SELECTION STATE
  Map the user input to
  visual read out
***************************/

// Selection is a range from
// 1 - 5
// i.e. the number of pixels on
// the neopixel
int currentSelection = 0;
int lastSelection = 0;

// wait for n seconds before
// moving to the next state
// so you know the user's actually
// confirmed
int delayBeforeSelection = 2000;//User must press the strip for 2 seconds to activate
long lastSelectionUpdate = -1;

const unsigned long DURATION = 5*60*1000;

unsigned long timerDuration = -1;
unsigned long timerStartedAt = -1;
unsigned long timerEndAt = -1;
unsigned long timePressed;
bool timerRunning = false;

void doSelectingState(){

  // Update the selection
  if(softPotReading>50)
  {
    // the user is still selecting
    currentSelection = softPotReading/400+1;
    /*map( softPotReading, 0, 4000, 1, timerStrip.numPixels() ); //converts touch readings to value between 1-5*/
    currentSelection = constrain( currentSelection, 0, timerStrip.numPixels() ); // ensure it's in the range

    displaySelectedLEDs(currentSelection);

    if(currentSelection!=lastSelection)
    {
      timePressed=millis();
      Serial.println("Last not equal to current.");
    }

    if(millis() > timePressed + delayBeforeSelection)
    {
      state = STATE_CONFIRMATION;
      Serial.println("Time to confirm.");
    }

    lastSelection = currentSelection;
  }
  else
  {
    state = STATE_WAITING;
  }
}

void doConfirmationState()
{
  // finished selecting
  // and we should start
  // the timer
  Serial.println("Doing confirmation state.");

  blinkSelectedLEDs(currentSelection);

  timerRunning = true;
  timerDuration = currentSelection * DURATION;
  timerStartedAt = millis();
  timerEndAt = timerStartedAt+timerDuration;
  Serial.println("Timer has started!");

  // confirm timer has started
  notifyWithVibration(2);

  // update the states
  if( currentSelection > 0 ){

    // blinkLEDs
    /*blinkSelectedLEDs(currentSelection);*/

    //Plays the next track in SD card once timer is started
    sendMP3Command(0x01,0,1);
    start = millis();

    //Reset the volume level
    volumeLevel = 50;
    sendMP3Command(0x06, 0, volumeLevel);

    //Move to the next state
    state = STATE_MEDITATING;

    //Send SMS
    int meditationEndTime = Time.local()+timerDuration/1000;
    int meditationEndHour = Time.hourFormat12(meditationEndTime);
    int meditationEndMinutes = Time.minute(meditationEndTime);
    String meditationEndAmPm = Time.isAM(meditationEndTime) ? "AM" : "PM";
    String sms_message = "Advait is meditating for " + String(timerDuration/1000) + " seconds.";
    /*Particle.publish("advait/timerStarted",sms_message);*/
    Serial.println(sms_message);

  }else{
    state = STATE_WAITING;
  }
}

/***************************
  MEDITATING STATE
  VIbrate in time with breathing
  Slowly track down the
  indicators
***************************/

void doMeditatingState(){

  // work out the number of LEDs to display
  int elapsed = millis() - timerStartedAt;
  Serial.printf("Time elapsed is %d\n",elapsed);
  float percentElapsed = (float(elapsed))/timerDuration;
  /*Serial.printf("Percent time elapsed is %d\n",percentElapsed);*/
  int numLeds = map( timerDuration - elapsed, 0, timerDuration, 0 , timerStrip.numPixels() );
  Serial.printf("Meditation started with %d LEDs \n",numLeds);
  displaySelectedLEDs( numLeds - 1);

  if(fsrReading>100)
  {
    vibrate();
  }
  else
  {
    stopVibration();
  }

  if( numLeds == 1){

    volumeLevel--;
    sendMP3Command(0x06, 0, volumeLevel);

  }
  else if( numLeds == 0 ){
    // when finished move to the
    // next state
    Particle.publish("advait/timerCompleted");
    state = STATE_COMPLETED;
  }
}

/***************************
  COMPLETED STATE
  VIbrate once to indicate
  completion
  Then return to
  waiting
***************************/

void doCompletedState(){

  Serial.println("Completed countdown");

  //Stops current track
  sendMP3Command(0x16,0,1);

  notifyWithVibration(2);

  stopVibration();

  state = STATE_WAITING;
}

void doMatOpening(const char *event,const char *data)
{
  Serial.println("Mat Opening.");
  blinkContactLed(2);
}

void doMatClosing(const char *event,const char *data)
{
  Serial.println("Mat Closing.");
  blinkContactLed(4);
}

/***************************
   SOFT POT METHOD
***************************/
void sampleFromSoftPotentiometer(){
  softPotReading = 4095;
  // sample 6 times...
  for( int j = 0 ; j < 6; j++ ){
    int val = analogRead(touchPin);
    if( val < softPotReading )
      softPotReading = val;
    delay(20);
  }
  /*int i = analogRead(touchPin);*/
  Serial.printf("The touch value is: %d \n",softPotReading);
}

/***************************
   FSR METHOD
***************************/
void sampleFromFSR(){
  fsrReading = 4095;
  // sample 6 times...
  for( int j = 0 ; j < 6; j++ ){
    int val = analogRead(fsrPin);
    if( val < fsrReading )
      fsrReading = val;
    delay(20);
  }
  /*int i = analogRead(touchPin);*/
  /*Serial.printf("The fsr value is: %d \n",fsrReading);*/
}

/***************************
   VIBRATION MOTOR METHODS
***************************/
void stopVibration(){
  analogWrite(meditVibPin, 0.0);
}

void notifyWithVibration( int times ){
  for( int i = 0 ; i < times; i++ ){
    delay(200);
    digitalWrite(notifVibPin, HIGH);
    delay( 200 );
    analogWrite(notifVibPin, LOW);
  }
}

void vibrate(){
  mid = start + DURATION;//mid is the point where the sine curve becomes a cos curve
  end = mid + 2*DURATION;
  int diff=0; //diff is the time elapsed since the vibration started

  if( (millis() > start) && (millis() < mid) )
  {
    diff = millis() - start;
    /*Serial.printf("The diff is %d\n",diff);*/
    vibVal = abs(200*sin(float(diff)/(2*DURATION)*3.1415926));
    /*Serial.println("Inside sine curve.");*/
  }
  else if( (millis() >= mid) && (millis() < end) )
  {
    diff = millis() - mid;
    /*Serial.printf("The diff is %d\n",diff);*/
    vibVal = abs(200*cos(float(diff)/(4*DURATION)*3.1415926));
    /*Serial.println("Inside cos curve.");*/
  }
  else
  {
    start = millis();
  }

  Serial.printf("The vibrator value is: %f\n",vibVal);
  analogWrite(meditVibPin, vibVal);
}

/***************************
  NEOPIXEL HELPERS
***************************/
//Breathing lights indicate a functional mat
void breathe(){
  /*Serial.println("Breathing!");*/
  /*float brightness=abs(float(sin(float(millis())/3000 * 3.14159)*75));*/
  //First setting pixel color of all pixels to green
  for(int i=0; i< timerStrip.numPixels(); i++)
  {
    timerStrip.setPixelColor(i,0,0,255,255);
  }

  int x = 1;
  for (int ii = 1 ; ii <80 ; ii = ii + x){
    timerStrip.setBrightness(ii);
    timerStrip.show();
    delay(10);
   }
  x = 1;
  for (int ii = 80 ; ii > 3 ; ii = ii - x){
    timerStrip.setBrightness(ii);
    timerStrip.show();
    delay(10);
    }
  delay(2);
  x = 1;
  for (int ii = 1 ; ii <80 ; ii = ii + x){
    timerStrip.setBrightness(ii);
    timerStrip.show();
    delay(10);
    }
  x = 1;
  for (int ii = 80 ; ii > 1 ; ii = ii - x){
    timerStrip.setBrightness(ii);
    timerStrip.show();
    delay(10);
  }
  delay (100);

  timerStrip.show();
}

void blinkLEDs( int times ){
  // blink n times
  for( int i = 0 ; i < times; i++ ){
    allNeopixelsOn();
    delay( 150);
    allNeopixelsOff();
    delay( 150);
  }
}

void cycleUpLeds(  ){
  allNeopixelsOff();

  // wipe up
  for (int i=0; i < timerStrip.numPixels(); i++) {
    timerStrip.setPixelColor(i,0,0,255,255);  // turn all pixels on
    timerStrip.show();
    delay( 200 );
  }

  // wipe down
  for (int i= timerStrip.numPixels() - 1 ; i >= 0 ; i-- ) {
    timerStrip.setPixelColor(i,0,0,0,0);  // turn all pixels off
    timerStrip.show();
    delay( 200 );
  }
}

void blinkContactLed(int num)
{
  for(int i=0;i<num;i++)
  {
    digitalWrite(matContactLedPin, HIGH); //D7 led blinks
    delay(100);
    digitalWrite(matContactLedPin, LOW); //D7 led blinks
    delay(100);
  }
}

void displaySelectedLEDs( int num ){

  // wipe up
  for (int i=0; i < timerStrip.numPixels(); i++) {
    if( i < num ){
      timerStrip.setPixelColor(i,0,0,255,255);
    }
    else{
      timerStrip.setPixelColor(i,0,0,0,0);
    }
  }
  timerStrip.show();
}

void blinkSelectedLEDs( int num ){
  for(int i=0;i<3;i++)
  {
    displaySelectedLEDs(num);
    delay(100);
    displaySelectedLEDs(0);
    delay(100);
  }
}

void allNeopixelsOn(){
  for (int i=0; i < timerStrip.numPixels(); i++) {
    timerStrip.setPixelColor(i,0,0,255,255);  // turn all pixels on
  }
  timerStrip.show();
}

void allNeopixelsOff(){
  for (int i=0; i < timerStrip.numPixels(); i++) {
    timerStrip.setPixelColor(i,0,0,0,0);  // turn all pixels off
  }
  timerStrip.show();
}

/***************************
  SOUND HELPERS
***************************/

//Passes byte code to the MP3 Player via TX pins and serial module
void sendMP3Command(byte CMD, byte Par1, byte Par2) // Execute the command and parameters
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
