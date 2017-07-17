/*
ADXL335
note:vcc-->5v ,but ADXL335 Vs is 3.3V
The circuit:
      5V: VCC
analog 1: x-axis
analog 2: y-axis
analog 3: z-axis
*/
const int xpin = 3;                  // x-axis of the accelerometer
const int ypin = 2;                  // y-axis
const int zpin = 1;                  // z-axis (only on 3-axis models)
const int numReadings = 10;

int xreadings[numReadings];      // the readings from the analog input
int xreadIndex = 0;              // the index of the current reading
int xtotal = 0;                  // the running total
int xaverage = 0;                // the average
int readingX = 0;
int prevreadingX = 0;
int changeX = 0;

int yreadings[numReadings];      // the readings from the analog input
int yreadIndex = 0;              // the index of the current reading
int ytotal = 0;                  // the running total
int yaverage = 0;                // the average
int readingY = 0;
int prevreadingY = 0;
int changeY = 0;

int zreadings[numReadings];      // the readings from the analog input
int zreadIndex = 0;              // the index of the current reading
int ztotal = 0;                  // the running total
int zaverage = 0;                // the average
int readingZ = 0;
int prevreadingZ = 0;
int changeZ = 0;
//https://anasdalintakam.blogspot.in/
//this code is for sensing ambient light using sparkfuns temt6000 ambient light sensor and arduino


void setup()
{
 // initialize the serial communications:
 Serial.begin(9600);
 for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    xreadings[thisReading] = 0;
  }
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
     yreadings[thisReading] = 0;
  }
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
     zreadings[thisReading] = 0;
   }

 //Particle.variable("light", &light_value, INT);
}
void loop()
{
  int x = analogRead(xpin);  //read from xpin

  int y = analogRead(ypin);  //read from ypin

  int z = analogRead(zpin);  //read from zpin

  float zero_G = 512.0; //ADC is 0~1023  the zero g output equal to Vs/2
                        //ADXL335 power supply by Vs 3.3V
  float scale = 102.3;  //ADXL335330 Sensitivity is 330mv/g
                         //330 * 1024/3.3/1000
 prevreadingX = readingX;
 prevreadingY = readingY;
 prevreadingZ = readingZ;
 readingX = ((float)x - 331.5)/65*9.8;
 readingY = ((float)y - 329.5)/68.5*9.8;
 readingZ = ((float)z - 340)/68*9.8;
 /*Serial.print(x);
 Serial.print("\t");
 Serial.print(y);
 Serial.print("\t");
 Serial.print(z);
 Serial.print("\n");*/
 Serial.print( Time.timeStr());
 Serial.print(",");
 Serial.print(xaverage);  //print x value on serial monitor
 Serial.print(",");
 Serial.print(yaverage);  //print y value on serial monitor
 Serial.print(",");
 Serial.print(zaverage);  //print z value on serial monitor
 Serial.println("");

 changeX = readingX - prevreadingX;
 changeY = readingY - prevreadingY;
 changeZ = readingZ - prevreadingZ;
 //light = light_value * 0.0976;// percentage calculation
 // x readings
 xtotal = xtotal - xreadings[xreadIndex]; // subtract the last reading:
 xreadings[xreadIndex] = changeX; // read from the sensor:
 xtotal = xtotal + xreadings[xreadIndex]; // add the reading to the total:
 xreadIndex = xreadIndex + 1; // advance to the next position in the array:

 if (xreadIndex >= numReadings) {  // if we're at the end of the array...
  xreadIndex = 0; // ...wrap around to the beginning:
 }

 xaverage = xtotal / numReadings; // calculate the average:

 // y readings
 ytotal = ytotal - yreadings[yreadIndex]; // subtract the last reading:
 yreadings[yreadIndex] = changeY; // read from the sensor:
 ytotal = ytotal + yreadings[yreadIndex]; // add the reading to the total:
 yreadIndex = yreadIndex + 1; // advance to the next position in the array:

 if (yreadIndex >= numReadings) {  // if we're at the end of the array...
  yreadIndex = 0; // ...wrap around to the beginning:
 }

 yaverage = ytotal / numReadings; // calculate the average:

 // z readings
 ztotal = ztotal - zreadings[zreadIndex]; // subtract the last reading:
 zreadings[zreadIndex] = changeZ; // read from the sensor:
 ztotal = ztotal + zreadings[zreadIndex]; // add the reading to the total:
 zreadIndex = zreadIndex + 1; // advance to the next position in the array:

 if (zreadIndex >= numReadings) {  // if we're at the end of the array...
  zreadIndex = 0; // ...wrap around to the beginning:
 }

 zaverage = ztotal / numReadings; // calculate the average:
 if (xaverage > 5 or yaverage > 5 or zaverage > 5)
 {

   Particle.publish("ammani/movement");
 }
 delay(50);

}
