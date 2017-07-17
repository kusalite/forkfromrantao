#include <math.h>

int meditVibPin = A4;
unsigned long start, mid, end;
float vibVal;

# define DURATION 3500

void setup() {
  Serial.begin(9600);
  Serial.println("Setup complete");

  pinMode(meditVibPin, OUTPUT);
  start = millis();
}

void loop() {
  vibrate();
  delay(500);
}

void vibrate() {
  mid = start + DURATION;
  end = mid + 2*DURATION;
  /*int time_dur = 2*DURATION;
  int time_period = millis()%time_dur;*/
  int diff=0;

  if( (millis() > start) && (millis() < mid) )
  {
    diff = millis() - start;
    Serial.printf("The diff is %d\n",diff);
    vibVal = abs(200*sin(float(diff)/(2*DURATION)*PI));
    Serial.println("Inside sine curve.");
  }
  else if( (millis() >= mid) && (millis() < end) )
  {
    diff = millis() - mid;
    Serial.printf("The diff is %d\n",diff);
    vibVal = abs(200*cos(float(diff)/(4*DURATION)*PI));
    Serial.println("Inside cos curve.");
  }
  else
  {
    start = millis();
  }

  /*if(time_period<(time_dur/3))
  {
    vibAngVel=float(millis())/(time_dur/3) * PI;
  }
  else
  {
    vibAngVel=(float(millis())/(time_dur*2/3) * PI)+PI/2;
  }*/

  /*float vibVal = abs(sin(vibAngVel)*200);*/

  Serial.printf("The vibrator value is: %f\n",vibVal);
  analogWrite(meditVibPin, vibVal);
}
