/*  MyGlobe V0.4
What it does:
  1. Magnet trigger hall effect sensor every round of rotation;
  2. Hall effect sensor triggers the led to lightup after delay
  3. Compute motor speed
  4. PID control of motor speed
  5. Light up a pixel and change it is location

*/

#include "application.h"
#include "dotstar.h"

//Motor PID Variables-----------------------------------------------------------
#include "pid.h"

//Define Variables we'll be connecting to
double Setpoint = 600, Input = 0, Output = 13200;

//Define the aggressive and conservative Tuning Parameters
double aggKp=105, aggKi=12, aggKd=0.05;
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

volatile int state = LOW; //for system to switch led on/off by sensor trigger
volatile float lastRoundTime;
volatile float timePerRound = 10000000;
volatile long roundCounter = 0;
volatile bool processed = false;
volatile bool triggered = false;

//old way to set delay for led, used for D7 led only to show status
int n = 30;
Timer timerOn (n, ledOn, true);
Timer timerOff (n+1, ledOff, true);

//For dislay--------------------------------------------------------------------
#include "picture.h"
#define NUMPIXELS 72
#define DATAPIN   D3
#define CLOCKPIN  D4
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN);

int halfRound = 47000;

int counter = 0;

int onPeriod = 20;
int offset = -5;
int numColumns = 97;

//--------------------------------------------------------------------------------
void setup() {

  pinMode(hallSensor, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  pinMode(PWM, OUTPUT);
  //pinMode(STBY, OUTPUT);
  //digitalWrite(STBY, HIGH); //send constant signal to activate motor control board
  pinMode(Ain2, OUTPUT);
  digitalWrite(Ain2, LOW); //send constant sigal to set motor direction
  pinMode(Ain1, OUTPUT);
  digitalWrite(Ain1, HIGH); //send constant sigal to set motor direction

  attachInterrupt( hallSensor, roundTime, RISING );//ISR to trigger time logging when hall sensor triggered

  //just a system status feedback
  digitalWrite(led_pin, HIGH);
  delay(1000);
  digitalWrite(led_pin, LOW);

  //below are old way to trigger led by hall effect sensor and timer. now serve as system status (D7 led blinking)
  timerOn.start();
  timerOff.start();

  analogWriteResolution(PWM, 14); //incrase motor PWM control resolution for better accuracy
  for (int i = 10; i<100; i++){
  analogWrite(PWM,i*Output/100);
  delay(20);
  }
  //turn the PID on
  myPID.SetSampleTime(30);
  myPID.SetOutputLimits(0, 16383);
  myPID.SetMode(PID::AUTOMATIC);

  //lighting-----------------------------
  pinMode(DATAPIN, OUTPUT);
  pinMode(CLOCKPIN,OUTPUT);
  strip.begin(); // Initialize pins for output
  strip.setBrightness(255);
  strip.show();  // Turn all LEDs off ASAP

  Particle.function("onOff",onOff);
  Particle.function("ledDelay",ledDelay);
  Particle.function("changeOffset",changeOffset);
  Particle.function("changeColumn",changeColumn);

}

void loop() {

  if(processed == false && Input< 700) { //this mark make sure one motor speed data from hall effect will not be double processed
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

  //led display
  if(triggered == true){
    //delayMicroseconds(4800*5);
    for (int lon = 0; lon< numColumns; lon++){
      updateDisplay1(lon);
      delayMicroseconds(onPeriod);
    }
    strip.clear();
    strip.show();
    triggered = false;
  }
  //Serial.println(counter);
}

void updateDisplay1(int j){
  int shift = j+offset % 100;
  for (int i=36; i<72;i++){
    strip.setPixelColor(i,daragh[71-i][shift]);
  }

  int mirror = (j + offset +49) % 100;
  for (int i=0; i<36; i++){
    strip.setPixelColor(i,daragh[i][mirror]);
  }
  strip.show();

}


/*void ledChange() {
  //led will switch betwwen on/off when triggered
  state = ! state;
  digitalWrite (led_pin, state);
}*/

//for D7 led as status
void ledOn() {
  digitalWrite (led_pin, HIGH);
}
//for D7 led as status
void ledOff() {
  digitalWrite (led_pin, LOW);
}

//triggered by interrupt, this function computes motor cycle time
void roundTime(){
  timePerRound = micros()-lastRoundTime;
  lastRoundTime = micros();
  roundCounter ++;
  Input = 1000000/timePerRound*60;
  processed = false;
  triggered = true;
  timerOn.resetFromISR();//only for D7 Led
  timerOff.resetFromISR();//only for D7 Led
}

int half (String inputPeriod){
  halfRound = inputPeriod.toInt();
  return halfRound;
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

int ledDelay (String period){
  onPeriod = period.toInt();
  return onPeriod;
}

int changeOffset (String newOffset){
  offset = newOffset.toInt();
  return offset;
}

int changeColumn (String newColumn){
  numColumns = newColumn.toInt();
  return numColumns;
}
