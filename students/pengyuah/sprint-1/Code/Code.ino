/*  MyGlobe V0.1
What it does:
  1. Magnet trigger hall effect sensor every round of rotation;
  2. hall effect sensor triggers the led to lightup
*/

int hallSensor = D1;
int led_pin = D7;

volatile int state = LOW; //for system to switch led on/off by sensor trigger

void setup() {

    pinMode(hallSensor, INPUT_PULLUP);

    pinMode(led_pin, OUTPUT);

    attachInterrupt( hallSensor , ledOn, CHANGE ); //use interrupt function to ensure realtime trigger under fast rotation.
    //hall sensor is triggered twice in a round: 1.when magnet moves close to the sensor; 2. when magnet move pass the sensor and polarity turns.
}

void loop() {

//noting here since all function triggered by interrupt

}

void ledOn() {

    //led will switch betwwen on/off when triggered
    state = ! state;
    digitalWrite (led_pin, state);

}
