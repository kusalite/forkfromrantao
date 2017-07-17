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

//int prevPos = 0;
volatile int prevTime = 0;
volatile long lastPeriod;
int countPerRound = 420;


float Kp =   0.01;                         // PID proportional control Gain
float Kd =    0.1;                         // PID Derivitave control gain
float speed_req = 300;                     // speed (Set Point)
volatile double speed_act = 0;                       // speed (actual value)
volatile int PWM_val = 9000;



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
  analogWrite (PWM, PWM_val);
}

void loop() {

}
//----------------------------------------------------------------

void doEncoderA(){
  if( digitalRead(encoderA) != A_set ) {  // debounce once more
    A_set = !A_set;
    // adjust counter + if A leads B
    if ( A_set != B_set ){
      //encoderPos += 1;
      lastPeriod = micros()-prevTime;
      prevTime = micros();
      speed_act = (142857.143/lastPeriod);
      PWM_val= updatePid(PWM_val, speed_req, float(speed_act));
      analogWrite (PWM, PWM_val);
      Serial.print(lastPeriod);
      Serial.print(" ");
      Serial.print(speed_act);
      Serial.print(" ");
      Serial.println(PWM_val);
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

int updatePid(int command, float targetValue, float currentValue)   {             // compute PWM value
  float pidTerm = 0;                                                            // PID correction
  float error=0;
  static float last_error=0;
  error = abs(targetValue) - abs(currentValue);
  pidTerm = (Kp * error) + (Kd * (error - last_error));
  last_error = error;
  return constrain(command + int(pidTerm), 0, 16384);
}
