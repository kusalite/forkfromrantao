#include "math.h"

/*Hardware Setup:
Wind Sensor Signals    Arduino
GND                    GND
+V                     5V
RV                     A1    // modify the definitions below to use other pins
TMP                    A0    // modify the definitions below to use other pins
*/

#define windPin     A2
#define ledPin      D0

#define CALIBRATION_TIME 5000


int wind = 0;
int minWindReading = 4095;
int maxWindReading = 0;

void setup()
{
  Serial.begin( 9600 );
  Serial.println("start");

  pinMode(ledPin, OUTPUT);

  doCalibration();

}

void loop()
{

  int reading = analogRead(windPin);
  //Serial.println( value );
  if( reading > maxWindReading )
    maxWindReading = reading;

  //int brightness = map( value, 0, 4095, 0, 255 ); // previously ...
  int brightness = map( reading, minWindReading, maxWindReading, 0, 255 );

  Serial.println( brightness );

  analogWrite(ledPin, brightness);

}


void doCalibration(){
  int startTime = millis();
  Serial.println("Beginning Calibration");

  // This is using the absolutely minimum ...

  /*while( millis() < startTime + CALIBRATION_TIME ){
    int reading = analogRead(windPin);

    // if we get a lower reading
    // update the baseline
    if( reading < minWindReading )
      minWindReading = reading;
  }*/

  int samples = 0;
  long sampleTotal = 0;
  while( millis() < startTime + CALIBRATION_TIME ){
    int reading = analogRead(windPin);

    // if we get a lower reading
    // update the baseline
    sampleTotal += reading;
    samples++;

    if( reading > maxWindReading )
      maxWindReading = reading;
  }

  minWindReading = sampleTotal / samples;

  Serial.println("Calbration complete");
  Serial.println("Baseline reading found to be: ");
  Serial.println( minWindReading );

}
