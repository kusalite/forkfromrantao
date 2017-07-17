//This code is for the remote controller of the device. This device listen to another Particle Photon which monitored plant through sensors. It has three 10-segment LED bars drived by LM3914, which will show the value of three sensors - the moisture sensor, the light sensor, and the water level sensor. Three buttons are used to control water pump and a servo that connected with another Particle Photon. A LED is used to indicate the successful triggering of buttons.
//The LM3914 has an analog input pin that can transform the input data to voltage. The 10-segment LED bar can therefore indicate the voltage by turning on certain number of segments.
#define moistureSensor D0 //To LM3914 that reflects the value of moisture sensor
#define lightSensor D1 //To LM3914 that reflects the value of light sensor
#define waterlevel D2 //To LM3914 that reflects the value of water level sensor
#define button1 D3 //To tigger water pump event
#define button2 D4 //To trigger open blind event
#define button3 D5 //To trigger close blind event
#define LED D6

void setup() {
  pinMode(moistureSensor, OUTPUT);
  pinMode(lightSensor, OUTPUT);
  pinMode(waterlevel, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  Particle.subscribe("liquidLevel", liquidoutput, "310039000f51353338363333"); //subscribe to the sensors from another Photon
  Particle.subscribe("photoCell", lightoutput, "310039000f51353338363333"); //subscribe to the sensors from another Photon
  Particle.subscribe("moisture", soiloutput, "310039000f51353338363333"); //subscribe to the sensors from another Photon
  Particle.subscribe("eventsucceed", eventsucceed, "310039000f51353338363333"); //subscribe to the event from another Photon
}

void loop() {
  int buttonState1 = digitalRead(button1);
  int buttonState2 = digitalRead(button2);
  int buttonState3 = digitalRead(button3);
  if(buttonState1 == 0) { //pushed
    Particle.publish("waterplant");
    delay(1000);
  }
  if(buttonState2 == 0) { //pushed
    Particle.publish("closeblinds");
    delay(1000);
  }
  if(buttonState3 == 0) { //pushed
    Particle.publish("openblinds");
    delay(1000);
  }
}

void liquidoutput(const char *event, const char *data) {
  int liquid = atof(data);
  int liquidvalue = map(liquid, 3700, 4095, 255, 0); //This threshold is set based on the water level sensor. The value input from the sensor is from 3700 to 4095, where 3700 is full and 4095 is empty. The analogwrite can output value from 0 to 255. Therefore, this 'map' function map the value 3700-4095 to 255-0, to indicate if the water tank is full or empty
  analogWrite(waterlevel, liquidvalue, analogWriteMaxFrequency(waterlevel));
  Serial.print("liquidvalue=");
  Serial.println(liquidvalue);
  delay(500);
}

void lightoutput(const char *event, const char *data) {
  int light = atof(data);
  int lightvalue = map(light, 2200, 3500, 0, 255); //This is the analog light sensor
  analogWrite(lightSensor, lightvalue, analogWriteMaxFrequency(lightSensor));
  Serial.print("lightvalue=");
  Serial.println(lightvalue);
  delay(500);
}

void soiloutput(const char *event, const char *data) {
  int moisture = atof(data);
  int moisturevalue = map(moisture, 0, 4095, 0, 255); //This is the soil moisture sensor
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
