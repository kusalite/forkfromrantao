//this goes to Ran's photon
#define moistureSensor D0
#define lightSensor A1
/*#define waterlevel D2*/
#define button1 D3
#define LED D6

void setup() {
  pinMode(moistureSensor, OUTPUT);
  pinMode(lightSensor, OUTPUT);
  /*pinMode(waterlevel, OUTPUT);*/
  pinMode(LED, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  /*Particle.subscribe("liquidLevel", liquidoutput, "DEVICE_ID"); //momo's photon*/
  Particle.subscribe("photoCell", lightoutput, "DEVICE_ID");
  Particle.subscribe("moisture", soiloutput, "DEVICE_ID");
  Particle.subscribe("eventsucceed", eventsucceed, "DEVICE_ID");
  Serial.begin(9600);
}

void loop() {
  int buttonState1 = digitalRead(button1);
  if(buttonState1 == 0) { //pushed
    Particle.publish("waterplant");
    delay(1000);
  }
}

/*void liquidoutput(const char *event, const char *data) {
  int liquid = atof(data);
  int liquidvalue = map(liquid, 2000, 4095, 255, 0);
  analogWrite(waterlevel, liquidvalue, analogWriteMaxFrequency(waterlevel));
  Serial.print("liquidvalue=");
  Serial.println(liquidvalue);
  delay(500);
}*/

void lightoutput(const char *event, const char *data) {
  int light = atof(data);
  int lightvalue = map(light, 0, 4095, 0, 255);
  analogWrite(lightSensor, lightvalue, analogWriteMaxFrequency(lightSensor));
  Serial.print("lightvalue=");
  Serial.println(lightvalue);
  delay(500);
}

void soiloutput(const char *event, const char *data) {
  int moisture = atof(data);
  int moisturevalue = map(moisture, 0, 4095, 0, 255);
  analogWrite(moistureSensor, moisturevalue, analogWriteMaxFrequency(moistureSensor));
  Serial.print("moisturevalue=");
  Serial.println(moisturevalue);
  delay(500);
}

void eventsucceed(const char *event, const char *data) {
  digitalWrite(LED, HIGH);
  delay(3000);
  digitalWrite(LED, LOW);
  delay(500);
}
