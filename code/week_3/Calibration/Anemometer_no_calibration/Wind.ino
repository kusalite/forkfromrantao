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

void setup()
{
  Serial.begin( 9600 );
  pinMode(ledPin, OUTPUT);
}

void loop()
{

  int value = analogRead(windPin);
  Serial.println( value );
  int brightness = map( value, 0, 4095, 0, 255 );

  analogWrite(ledPin, brightness);

}
