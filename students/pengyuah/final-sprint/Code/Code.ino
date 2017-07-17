/*  MyGlobe V0.4
What it does:
  1. Magnet trigger hall effect sensor every round of rotation;
  2. Hall effect sensor triggers the led to lightup after delay
  3. Compute motor speed
  4. PID control of motor speed
  5. Light up a pixel and change it is location

*/
#include "math.h"
#include "application.h"
#include "dotstar.h"

//Motor PID Variables-----------------------------------------------------------
#include "pid.h"

//Define Variables we'll be connecting to
double Setpoint = 600, Input = 0, Output = 13300;

//Define the aggressive and conservative Tuning Parameters
double aggKp=100, aggKi=12, aggKd=0.05;
double consKp=80, consKi=9, consKd=0;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, PID::DIRECT);

//Hall effect variables---------------------------------------------------------
int hallSensor = D1;
int led_pin = D7;
int PWM = A4;
int STBY = A2;
int Ain1 = A2;
int Ain2 = A3;

volatile float lastRoundTime;
volatile float timePerRound = 10000000;
volatile long roundCounter = 0;
volatile bool processed = false;
volatile bool triggered = false;

//For dislay--------------------------------------------------------------------
#include "picture.h"
#define NUMPIXELS 72
#define DATAPIN   D3
#define CLOCKPIN  D4

#define STATE_BLANK 1
#define STATE_COLORMAP 2
#define STATE_WHITEMAP 3
#define STATE_JOURNEY 4

int state = 1;

Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN);

int onPeriod = 0;
int offset = -5;
int numColumns = 96;
int numRowsColor = 0;
int colorCounter = 0;
uint32_t displayArray [36][100];
bool toUpdateGraphic = false;
int locationSwitch = 0;
Timer timer (5000, subTasks, false);
Timer offColorTimer (3000, offColor, true);
int brightness = 50;
int subState = 0;
int overlap = 50;
bool offColorOn = false;

//--------------------------------------------------------------------------------
void setup() {

  pinMode(hallSensor, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(Ain2, OUTPUT);
  digitalWrite(Ain2, LOW); //send constant sigal to set motor direction
  pinMode(Ain1, OUTPUT);
  digitalWrite(Ain1, HIGH); //send constant sigal to set motor direction

  attachInterrupt( hallSensor, roundTime, RISING );//ISR to trigger time logging when hall sensor triggered

  //just a system status feedback
  digitalWrite(led_pin, HIGH);
  delay(1000);
  digitalWrite(led_pin, LOW);

  analogWriteResolution(PWM, 14); //incrase motor PWM control resolution for better accuracy
  for (int i = 10; i<100; i++){
  analogWrite(PWM,i*Output/100);
  delay(20);
  }
  //turn the PID on
  myPID.SetSampleTime(30);
  myPID.SetOutputLimits(0, 16383);
  myPID.SetMode(PID::AUTOMATIC);

  //Display-----------------------------
  pinMode(DATAPIN, OUTPUT);
  pinMode(CLOCKPIN,OUTPUT);
  strip.begin(); // Initialize pins for output
  strip.setBrightness(brightness);
  strip.show();  // Turn all LEDs off ASAP

  Particle.function("onOff",onOff);
  //Particle.function("ledDelay",ledDelay);
  Particle.function("overlap",changeOffset);
  Particle.function("changeColumn",changeColumn);
  Particle.function("changeState",changeState);
  //Particle.variable("subState",subState);
  //Particle.variable("Output",Output);

}

void loop() {

  if(processed == false && Input< 630) { //this mark make sure one motor speed data from hall effect will not be double processed
    //adaptive motor speed PID control
    double gap = abs(Setpoint-Input); //distance away from setpoint
    if(gap<1)
    {  //we're close to setpoint, use conservative tuning parameters
      myPID.SetTunings(consKp, consKi, consKd);
    }
    else
    {
       //we're far from setpoint, use aggressive tuning parameters
       myPID.SetTunings(aggKp, aggKi, aggKd);
    }
    myPID.Compute();
    processed = true; //reset marker
    analogWrite(PWM, Output);  // send PWM to motor
    //serial output of motor speed and control to allow monitoring
    //Serial.print(Input);
    //Serial.print(" ");
    //Serial.println(Output);
  }

  switch (state){
    case STATE_BLANK:
    break;

    /*case STATE_WELCOME:
    if (toUpdateGraphic){
      for (int i = 0; i < 36; i ++){
        for (int j = 0; j < 100; j ++){
          if (hi[i][j] == 0){
            displayArray[i][j]= palette[0][0];
          }
          else {
            displayArray[i][j]= 0xffffff;
          }
        }
      }
      toUpdateGraphic = false;
    }*/

    //led display
    if(triggered == true){
      for (int lon = 0; lon< numColumns; lon++){
        updateDisplay(lon);
        delayMicroseconds(onPeriod);
      }
      strip.clear();
      strip.show();
      triggered = false;
    }
    break;

    case STATE_COLORMAP:
    if (toUpdateGraphic){
      colorCounter = 0;
      numRowsColor = 0;
      for (int i = 0; i < 36; i ++){
        for (int j = 0; j < 100; j ++){
          if (zoneMap [i][j] == 0){
            displayArray[i][j]= palette[0][0];
          }
          else {
            displayArray[i][j] = colorMap [i][j];
          }
        }
      }
      toUpdateGraphic = false;
    }

    //led display
    if(triggered == true){
      for (int lon = 0; lon< numColumns; lon++){
        updateDisplayColor(lon);
        delayMicroseconds(onPeriod);
      }
      strip.clear();
      strip.show();
      triggered = false;
    }
    if (numRowsColor < 36 && colorCounter%5 == 0 && colorCounter >10){
      numRowsColor ++;
    }
    else if (numRowsColor == 36 && offColorOn == false){
      offColorTimer.start();
      offColorOn = true;
    }
    colorCounter ++;
    break;

    case STATE_WHITEMAP:
    if (toUpdateGraphic){
      for (int i = 0; i < 36; i ++){
        for (int j = 0; j < 100; j ++){
          if (zoneMap [i][j] == 0){
            displayArray[i][j]= palette[0][0];
          }
          else {
            displayArray[i][j]= 0xffffff;
          }
        }
      }
      toUpdateGraphic = false;
    }

    //led display
    if(triggered == true){
      for (int lon = 0; lon< numColumns; lon++){
        updateDisplay(lon);
        delayMicroseconds(onPeriod);
      }
      strip.clear();
      strip.show();
      triggered = false;
    }
    break;

    case STATE_JOURNEY:
      if (toUpdateGraphic){
        locationSwitch = 0;
        for (int i = palette[locationSwitch][8]-1; i<palette[locationSwitch][8]+2; i++){
          displayArray[i][palette[locationSwitch][9]] = 0xff0000;
        }
        for (int j = palette[locationSwitch][9]-1; j<palette[locationSwitch][9]+2; j++){
          displayArray[palette[locationSwitch][8]][j] = 0xff0000;
        }
        displayArray[palette[locationSwitch][8]][palette[locationSwitch][9]] = 0xffffff;
        subState = 1;
        timer.start();

      }
      toUpdateGraphic = false;

      //led display
      if(triggered == true){
        for (int lon = 0; lon< numColumns; lon++){
          updateDisplay(lon);
          delayMicroseconds(onPeriod);
        }
        strip.clear();
        strip.show();
        triggered = false;
      }
    break;

  }
}

void updateDisplay(int j){
  int shift = (j+offset) % 100;
  for (int i=36; i<72;i++){
    strip.setPixelColor(i,displayArray[71-i][shift]);
  }

  int mirror = (j + offset +overlap) % 100;
  for (int i=0; i<36; i++){
    strip.setPixelColor(i,displayArray[i][mirror]);
  }
  delayMicroseconds(30);
  strip.show();
}

void updateDisplayColor(int j){
  int shift = (j+offset) % 100;
  int Ri = 72-numRowsColor;
  for (int i=72; i>Ri ;i--){
    strip.setPixelColor(i,displayArray[71-i][shift]);
  }

  int mirror = (j + offset +overlap) % 100;
  for (int i=0; i<numRowsColor; i++){
    strip.setPixelColor(i,displayArray[i][mirror]);
  }
  delayMicroseconds(40);
  strip.show();
}

void subTasks (){
  if (subState == 0){
    pointing();
    subState = 1;
  }
  else if (subState == 1){
    paintMap();
    subState = 0;
  }
  else{
    offDisplay();
    subState = 0;
  }
}

void pointing (){
  for (int i=strip.getBrightness(); i>-1; i--){
    strip.setBrightness(i);
    delay(5);
  }
  for (int i = 0; i < 36; i ++){
    for (int j = 0; j < 100; j ++){
      if (zoneMap [i][j] == 0){
        displayArray[i][j]= palette[0][0];
      }
      else {
        displayArray[i][j]= 0xffffff;
      }
    }
  }
  for (int i = palette[locationSwitch][8]-1; i<palette[locationSwitch][8]+2; i++){
    displayArray[i][palette[locationSwitch][9]] = 0xff0000;
  }
  for (int j = palette[locationSwitch][9]-1; j<palette[locationSwitch][9]+2; j++){
    displayArray[palette[locationSwitch][8]][j] = 0xff0000;
  }
  displayArray[palette[locationSwitch][8]][palette[locationSwitch][9]] = 0xffffff;
  for (int i=0; i<brightness+1; i++){
    strip.setBrightness(i);
    delay(5);
  }
}
void paintMap (){
  for (int i=brightness+1; i>-1; i--){
    strip.setBrightness(i);
    delay(5);
  }
  for (int i = 0; i < 36; i ++){
    for (int j = 0; j < 100; j ++){
      if (zoneMap [i][j] == 0){
        displayArray[i][j]= palette[locationSwitch][0];
      }
      else if (zoneMap [i][j] == 1){
        displayArray[i][j]= palette[locationSwitch][1];
      }
      else if (zoneMap [i][j] == 2){
        displayArray[i][j]= palette[locationSwitch][2];
      }
      else if (zoneMap [i][j] == 3){
        displayArray[i][j]= palette[locationSwitch][3];
      }
      else if (zoneMap [i][j] == 4){
        displayArray[i][j]= palette[locationSwitch][4];
      }
      else if (zoneMap [i][j] == 5){
        displayArray[i][j]= palette[locationSwitch][5];
      }
      else if (zoneMap [i][j] == 6){
        displayArray[i][j]= palette[locationSwitch][6];
      }
      else if (zoneMap [i][j] == 7){
        displayArray[i][j]= palette[locationSwitch][7];
      }
    }
  }
  for (int i = palette[locationSwitch][8]-1; i<palette[locationSwitch][8]+2; i++){
    displayArray[i][palette[locationSwitch][9]] = 0xff0000;
  }
  for (int j = palette[locationSwitch][9]-1; j<palette[locationSwitch][9]+2; j++){
    displayArray[palette[locationSwitch][8]][j] = 0xff0000;
  }
  displayArray[palette[locationSwitch][8]][palette[locationSwitch][9]] = 0xffffff;
  for (int i=0; i<brightness+1; i++){
    strip.setBrightness(i);
    delay(5);
  }
  locationSwitch = (locationSwitch + 1)%4;
}
void offDisplay(){
  for (int i=brightness+1; i>-1; i--){
    strip.setBrightness(i);
    delay(5);
  }
  strip.clear();
  locationSwitch = (locationSwitch + 1)%4;
}

void offColor (){
  /*for (int i=brightness; i>-1; i--){
    strip.setBrightness(i);
    delay(5);
  }*/
  state = 3;
  toUpdateGraphic = true;
  offColorOn = false;
  timer.stop();
}

//triggered by interrupt, this function computes motor cycle time
void roundTime(){
  timePerRound = micros()-lastRoundTime;
  lastRoundTime = micros();
  roundCounter ++;
  Input = 1000000/timePerRound*60;
  processed = false;
  triggered = true;
}

int onOff(String motor){
  if (motor == "on"){
    digitalWrite(Ain1, HIGH);
    for (int i = 10; i<100; i++){
    analogWrite(PWM,i*Output/100);
    delay(20);
    }
  }
  else{
    digitalWrite(Ain1, LOW);
  }
}

int changeState (String nextState){
  if (nextState.toInt() == 0){
    state = (state + 1) % 5;
  }
  else{
    state = nextState.toInt();
  }
  toUpdateGraphic = true;
  timer.stop();
  return state;
}

int ledDelay (String period){
  onPeriod = period.toInt();
  return onPeriod;
}

int changeOffset (String newOffset){
  overlap = newOffset.toInt();
  return overlap;
}

int changeColumn (String newColumn){
  numColumns = newColumn.toInt();
  return numColumns;
}
