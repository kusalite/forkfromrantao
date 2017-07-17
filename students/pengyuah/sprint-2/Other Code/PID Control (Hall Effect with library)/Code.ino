/*  MyGlobe V0.3
What it does:
  1. Magnet trigger hall effect sensor every round of rotation;
  2. Hall effect sensor triggers the led to lightup after delay
  3. Compute RPM
  4. PID control of motor speed

*/
//------------------------------------------------------------------------------
#include "pid.h"

//Define Variables we'll be connecting to
double Setpoint = 600, Input = 0, Output = 7000;

//Define the aggressive and conservative Tuning Parameters
double aggKp=80, aggKi=0.2, aggKd=0.05;
double consKp=80, consKi=0.2, consKd=0.05;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, PID::DIRECT);

//------------------------------------------------------------------------------
int hallSensor = D1;
int led_pin = D7;
int PWM = A4;
int STBY = D5;
int Ain1 = D4;
int Ain2 = D3;

volatile int state = LOW; //for system to switch led on/off by sensor trigger
volatile float lastRoundTime;
volatile float timePerRound = 10000000;
volatile long roundCounter = 0;
volatile bool processed = false;

int n = 30;

Timer timerOn (n, ledOn, true);
Timer timerOff (n+1, ledOff, true);

void setup() {

  pinMode(hallSensor, INPUT_PULLUP);

  pinMode(led_pin, OUTPUT);

  pinMode(PWM, OUTPUT);
  //digitalWrite(PWM, HIGH);

  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);

  pinMode(Ain2, OUTPUT);
  digitalWrite(Ain2, HIGH);

  pinMode(Ain1, OUTPUT);
  digitalWrite(Ain1, LOW);

  //attachInterrupt( hallSensor, ledChange, CHANGE ); //use interrupt function to ensure realtime trigger under fast rotation.
  //hall sensor is triggered twice in a round: 1.when magnet moves close to the sensor; 2. when magnet move pass the sensor and polarity turns.
  attachInterrupt( hallSensor, roundTime, RISING );//count time per round
  digitalWrite(led_pin, HIGH);
  delay(1000);
  digitalWrite(led_pin, LOW);
  timerOn.start();
  timerOff.start();
  analogWriteResolution(PWM, 14);
  analogWrite(PWM,Output);
  //turn the PID on
  myPID.SetSampleTime(30);
  myPID.SetOutputLimits(0, 16383);
  myPID.SetMode(PID::AUTOMATIC);
}

void loop() {

  if(processed == false) {

    double gap = abs(Setpoint-Input); //distance away from setpoint
    if(gap<5)
    {  //we're close to setpoint, use conservative tuning parameters
      myPID.SetTunings(consKp, consKi, consKd);
    }
    else
    {
       //we're far from setpoint, use aggressive tuning parameters
       myPID.SetTunings(aggKp, aggKi, aggKd);
    }
    myPID.Compute();
    processed = true;
    analogWrite(PWM, Output);  // send PWM to motor
    Serial.print(Input);
    Serial.print(" ");
    Serial.println(Output);
  }
}

void ledChange() {
  //led will switch betwwen on/off when triggered
  state = ! state;
  digitalWrite (led_pin, state);
}

void ledOn() {
  digitalWrite (led_pin, HIGH);
}

void ledOff() {
  digitalWrite (led_pin, LOW);
}

void roundTime(){
  timePerRound = micros()-lastRoundTime;
  lastRoundTime = micros();
  roundCounter ++;
  Input = 1000000/timePerRound*60;
  processed = false;
  timerOn.resetFromISR();
  timerOff.resetFromISR();
}

/*int updatePid(int command, float targetValue, float currentValue)   {             // compute PWM value
  float pidTerm = 0;                                                            // PID correction
  float error=0;
  static float last_error=0;
  error = abs(targetValue) - abs(currentValue);
  pidTerm = (Kp * error) + (Kd * (error - last_error));
  last_error = error;
  return constrain(command + int(pidTerm), 0, 16384);
}*/
