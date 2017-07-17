/*  MyGlobe V0.2
What it does:
  1. Magnet trigger hall effect sensor every round of rotation;
  2. Hall effect sensor triggers the led to lightup after delay
  3. Compute RPM
  4. Output PWM value to control motor driver
*/

int hallSensor = D1;
int led_pin = D7;
int PWM = A4;
int STBY = D5;
int Ain1 = D4;
int Ain2 = D3;

volatile int state = LOW; //for system to switch led on/off by sensor trigger
volatile double lastRoundTime;
volatile double timePerRound = 10000000;

double RPM = 0;
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
}

void loop() {

//noting here since all function triggered by interrupt
RPM = 1000000/timePerRound*60;
delay(50);
Serial.println(RPM);
//timerOn.changePeriod(1000);
//timerOff.changePeriod(1000);
analogWrite (PWM, 150);

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
//timerOn.changePeriodFromISR(int(0.25*timePerRound/1000));
//timerOff.changePeriodFromISR(int(0.25*timePerRound/1000)+1);
timerOn.resetFromISR();
timerOff.resetFromISR();

}
