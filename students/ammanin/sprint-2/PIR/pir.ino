int inputPin = D0;              // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int pirSwitch = 0;
int calibrateTime = 10000;      // wait for the thingy to calibrate

void setup()
{
  pinMode(inputPin, INPUT);     // declare sensor as input
  Particle.variable("Hand", &pirSwitch, INT);
}

void loop()
{

  // if the sensor is calibrated
  if ( calibrated() )
  {
  // get the data from the sensor
    readTheSensor();

  // report it out, if the state has changed
    reportTheData();
  }
}

void readTheSensor() {
  val = digitalRead(inputPin);
}

bool calibrated() {
  return millis() - calibrateTime > 0;
}

void reportTheData() {

  // if the sensor reads high
  // or there is now motion
  if (val == HIGH) {

    // the current state is no motion
    // i.e. it's just changed
    // announce this change by publishing an eent
    if (pirState == LOW) {
      // we have just turned on
      // Update the current state
      pirState = HIGH;
      pirSwitch = 1;
    }
  } else {
    if (pirState == HIGH) {
      // we have just turned of
      // Update the current state
      pirState = LOW;
      pirSwitch = 0;
    }
  }
}
