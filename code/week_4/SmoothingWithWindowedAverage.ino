// Taken From: https://www.arduino.cc/en/tutorial/smoothing

const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int inputPin = A0;

void setup() {
 Serial.begin(9600);
 for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  total = total - readings[readIndex]; // subtract the last reading:
  readings[readIndex] = analogRead(inputPin); // read from the sensor:
  total = total + readings[readIndex]; // add the reading to the total:
  readIndex = readIndex + 1; // advance to the next position in the array:

  if (readIndex >= numReadings) {  // if we're at the end of the array...
   readIndex = 0; // ...wrap around to the beginning:
  }

  average = total / numReadings; // calculate the average:
  delay(50);        // delay in between reads for stability
}