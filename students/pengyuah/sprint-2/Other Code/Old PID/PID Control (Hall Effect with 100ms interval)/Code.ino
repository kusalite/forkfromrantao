/*  MyGlobe V0.3
What it does:
  1. Magnet trigger hall effect sensor every round of rotation;
  2. Hall effect sensor triggers the led to lightup after delay
  3. Compute RPM
  4. PID control of motor speed

*/

#define LOOPTIME 100                     // PID loop time
float Kp =   0.1;                         // PID proportional control Gain
float Kd =    0.3;                         // PID Derivitave control gain
float speed_req = 500;                     // speed (Set Point)
float speed_act = 0;                       // speed (actual value)
int PWM_val = 4500;
int lastPID;

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
}

void loop() {

  if((millis()-lastPID) >= LOOPTIME)   {                                    // enter tmed loop
    lastPID = millis();
    PWM_val= updatePid(PWM_val, speed_req, speed_act);    // compute PWM value
    Serial.print(speed_act);
    Serial.print(" ");
    Serial.println(PWM_val);
    analogWrite(PWM, PWM_val);  // send PWM to motor
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
  speed_act = 1000000/timePerRound*60;
  timerOn.resetFromISR();
  timerOff.resetFromISR();
}

int updatePid(int command, float targetValue, float currentValue)   {             // compute PWM value
  float pidTerm = 0;                                                            // PID correction
  float error=0;
  static float last_error=0;
  error = abs(targetValue) - abs(currentValue);
  pidTerm = (Kp * error) + (Kd * (error - last_error));
  last_error = error;
  return constrain(command + int(pidTerm), 0, 16384);
}
