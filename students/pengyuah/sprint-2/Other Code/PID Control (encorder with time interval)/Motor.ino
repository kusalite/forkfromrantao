//PID varialbes-------------------------------------------------------
#include "pid.h"

//Define Variables we'll be connecting to
double setpoint = 300, input = 0, output = 11400;

//Define the aggressive and conservative Tuning Parameters
double aggKp=100, aggKi=0, aggKd=0;
double consKp=50, consKi=0, consKd=0;

//Specify the links and initial tuning parameters
PID myPID(&input, &output, &setpoint, consKp, consKi, consKd, PID::DIRECT);

//encoder Variables---------------------------------------------------
void doEncoderA();
void doEncoderB();

int encoderA = A3;
int encoderB = A2;
int PWM = A4;
int STBY = D5;
int Ain1 = D4;
int Ain2 = D3;

volatile bool A_set = false;
volatile bool B_set = false;
volatile int encoderPos = 0;

int prevPos = 0;
int prevTime = 1000;
long lastPeriod=0;
int countPerRound = 420;
int countOfPeriod = 1000;


void setup() {
  Serial.begin(9600);
  //delay(1000);
  //Serial.println(encoderPos);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);
  pinMode(Ain2, OUTPUT);
  digitalWrite(Ain2, HIGH);
  pinMode(Ain1, OUTPUT);
  digitalWrite(Ain1, LOW);
  pinMode(encoderA, INPUT_PULLUP);
  pinMode(encoderB, INPUT_PULLUP);
  attachInterrupt(encoderA, doEncoderA, CHANGE);
  //attachInterrupt(encoderB, doEncoderB, CHANGE);
  pinMode(PWM, OUTPUT);
  analogWriteResolution(PWM, 14);
  analogWrite (PWM, output);
  delay(500);
  //turn the PID on
  myPID.SetOutputLimits(0, 16383);
  myPID.SetMode(PID::AUTOMATIC);
}

void loop() {
  //compute RPM
  lastPeriod = micros()-prevTime;
  if (lastPeriod >= 100000){
    countOfPeriod = encoderPos - prevPos;
    prevTime = micros();
    prevPos = encoderPos;
    input = 142857.142857*double(countOfPeriod)/double(lastPeriod);

    //PID control
    double gap = abs(setpoint-input); //distance away from setpoint
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

    //Output
    analogWrite (PWM, int(output));
    Serial.print(lastPeriod);
    Serial.print(" ");
    Serial.print(countOfPeriod);
    Serial.print(" ");
    Serial.print(input);
    Serial.print(" ");
    Serial.println(output);
  }
}
//Encoder Interrupt-------------------------------------------------------------


void doEncoderA(){
  if( digitalRead(encoderA) != A_set ) {  // debounce once more
    A_set = !A_set;
    // adjust counter + if A leads B
    if ( A_set != B_set ){
      encoderPos += 1;
    }
  }
}

/*// Interrupt on B changing state, same as A above
void doEncoderB(){
   if( digitalRead(encoderB) != B_set ) {
    B_set = !B_set;
    //  adjust counter - 1 if B leads A
    if( B_set != A_set )
      encoderPos -= 1;
  }
}*/
//Old PID Code------------------------------------------------------------------
/*int updatePid(int command, float targetValue, float currentValue)   {             // compute PWM value
  float pidTerm = 0;                                                            // PID correction
  float error=0;
  static float last_error=0;
  error = abs(targetValue) - abs(currentValue);
  pidTerm = (Kp * error) + (Kd * (error - last_error));
  last_error = error;
  return constrain(command + int(pidTerm), 0, 16384);
}*/
