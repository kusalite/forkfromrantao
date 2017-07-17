/*  MyGlobe V0.4
What it does:
  1. Magnet trigger hall effect sensor every round of rotation;
  2. Hall effect sensor triggers the led to lightup after delay
  3. Compute motor speed
  4. PID control of motor speed
  5. Light up a pixel and change it is location

*/
//Motor PID Variables-----------------------------------------------------------
#include "pid.h"

//Define Variables we'll be connecting to
double Setpoint = 600, Input = 0, Output = 7000;

//Define the aggressive and conservative Tuning Parameters
double aggKp=75, aggKi=0.15, aggKd=0.05;
double consKp=75, consKi=0.15, consKd=0.05;

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
int led_new1 = A5;
int led_new2 = D5;
int led_new3 = A5;

/*int display [20] =
{0,0,0,0,0,32767,32767,32767,32767,32767,0,0,0,0,0,16384,16384,16384,16384,16384};

int display2 [20] =
{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1};*/

//Display button----------------------------------------------------------------
//To change light-up pixel position
int button1 = A5;
int button2 = A5;
volatile int vertical = 0;
volatile int horizontal = 0;
volatile long lastPress = 0;
//--------------------------------------------------------------------------------
void setup() {

  pinMode(hallSensor, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  pinMode(PWM, OUTPUT);
  //pinMode(STBY, OUTPUT);
  //digitalWrite(STBY, HIGH); //send constant signal to activate motor control board
  pinMode(Ain2, OUTPUT);
  digitalWrite(Ain2, HIGH); //send constant sigal to set motor direction
  pinMode(Ain1, OUTPUT);
  digitalWrite(Ain1, LOW); //send constant sigal to set motor direction

  attachInterrupt( hallSensor, roundTime, RISING );//ISR to trigger time logging when hall sensor triggered

  //just a system status feedback
  digitalWrite(led_pin, HIGH);
  delay(1000);
  digitalWrite(led_pin, LOW);

  //below are old way to trigger led by hall effect sensor and timer. now serve as system status (D7 led blinking)
  timerOn.start();
  timerOff.start();

  analogWriteResolution(PWM, 14); //incrase motor PWM control resolution for better accuracy
  analogWrite(PWM,Output);
  //turn the PID on
  myPID.SetSampleTime(30);
  myPID.SetOutputLimits(0, 16383);
  myPID.SetMode(PID::AUTOMATIC);

  //lighting-----------------------------
  pinMode(led_new1,OUTPUT);
  //analogWriteResolution(led_new, 15);
  pinMode(led_new2,OUTPUT);
  pinMode(led_new3,OUTPUT);
  //button--------------------------------
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  attachInterrupt( button1, buttonVertical, FALLING );
  attachInterrupt( button2, buttonHorizontal, FALLING );

}

void loop() {

  if(processed == false) { //this mark make sure one motor speed data from hall effect will not be double processed
    //adaptive motor speed PID control
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
    processed = true; //reset marker
    analogWrite(PWM, Output);  // send PWM to motor
    //serial output of motor speed and control to allow monitoring
    Serial.print(Input);
    Serial.print(" ");
    Serial.println(Output);
  }

  //led display
  if(triggered == true){
    /*for (int i=0; i<20;i++){
        digitalWrite(led_new1, display2[i]);
        digitalWrite(led_new2, display2[i]);
        digitalWrite(led_new3, display2[i]);
        delayMicroseconds(4800);
      }*/
      delayMicroseconds(4800*horizontal); //control longitude display position
      //switching between 3 latitude leds
      if(vertical == 0){
        digitalWrite(led_new1, HIGH);
        delayMicroseconds(4800);
        digitalWrite(led_new1, LOW);
      }
      else if(vertical == 1){
        digitalWrite(led_new2, HIGH);
        delayMicroseconds(4800);
        digitalWrite(led_new2, LOW);
      }
      else {
        digitalWrite(led_new3, HIGH);
        delayMicroseconds(4800);
        digitalWrite(led_new3, LOW);
      }
    triggered = false;
  }
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

//switching botton altitude
void buttonVertical(){
  if (millis()>lastPress+200){
    if (vertical < 2){
      vertical ++;
    }
    else {
      vertical =0;
    }
  }
  lastPress = millis();
}
//switching button longitude
void buttonHorizontal(){
  if (millis()>lastPress+200){
    if (horizontal < 20){
      horizontal ++;
    }
    else {
      horizontal =0;
    }
  }
  lastPress = millis();
}

//old PID code
/*int updatePid(int command, float targetValue, float currentValue)   {             // compute PWM value
  float pidTerm = 0;                                                            // PID correction
  float error=0;
  static float last_error=0;
  error = abs(targetValue) - abs(currentValue);
  pidTerm = (Kp * error) + (Kd * (error - last_error));
  last_error = error;
  return constrain(command + int(pidTerm), 0, 16384);
}*/
