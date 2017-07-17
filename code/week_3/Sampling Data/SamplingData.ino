#include "math.h"


#define sensorPin     A1
#define buttonPin      D0

int sensorReading = 0;
int buttonReading = LOW;

void setup()
{
  Serial.begin( 9600 );

	// setup a time zone, which is part of the ISO6801 format
	// currently EST!
	Time.zone(-5);  

}

void loop()
{

  sensorReading = analogRead(sensorPin);
  buttonReading = digtalRead(buttonPin);

	dumpDataToSerial();

}

void dumpData(){
  // Start by outputting the time
  // Thur Apr 6 07:08:47 2016 
	time_t time = Time.now();
	String tStr = Time.format(time, TIME_FORMAT_ISO8601_FULL); 
	// 2017-04-05T07:08:47-05:00
	Serial.print( tStr );
	
	// each value must be followed by a comma
	Serial.print( ",");
	// write out each sensor value you
	// want to keep a log of 
	Serial.print( sensorReading );
	Serial.print( ",");
	Serial.print( buttonReading );
	// the last one doesn’t need a comma after it
	// but you do need to start a new line
	Serial.println("");
}

