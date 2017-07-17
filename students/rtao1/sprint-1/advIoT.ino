#include "Adafruit_DHT.h"

#define liquidLevelRESISTOR 560 //liquid level sensor resistor
#define liquidLevelPIN A1
#define photoCellPin A0
#define soilmoisture A2
#define DHTPIN D0
#define DHTTYPE DHT22		// DHT 22 (AM2302)
#define waterPump1 D1
#define waterPump2 D2

Servo myServo1;
Servo myServo2;
int servoPos = 0;

DHT dht(DHTPIN, DHTTYPE); //DHT init setting

void setup()
{
  pinMode(photoCellPin, INPUT);
  pinMode(liquidLevelPIN, INPUT);
  pinMode(soilmoisture, INPUT);
  pinMode(waterPump1, OUTPUT);
  pinMode(waterPump2, OUTPUT);
  myServo1.attach(A3);
  myServo2.attach(A4);
  Particle.variable("servoPos", &servoPos, INT);
  Particle.subscribe("hook-response/water_plant", waterPlant, "57002b001451353432393433"); //trigger water plant from webhook
  Particle.subscribe("hook-response/spray_water", sprayWater, "57002b001451353432393433"); //trigger spray water from webhook
  Particle.subscribe("hook-response/close_blinds", closeBlinds, "57002b001451353432393433"); //trigger close blinds from webhook
  Particle.subscribe("hook-response/open_blinds", openBlinds, "57002b001451353432393433"); //trigger open blinds from webhook
  dht.begin(); //DHT init
  Serial.begin( 9600 );
}

void loop()
{
  int liquidLevel = analogRead(liquidLevelPIN); //3500-4095, full - empty
  String liquidLevelOutput = String(liquidLevel); //int to string for webhook
  int photoCell = analogRead(photoCellPin);
  String photoCellOutput = String(photoCell); //0-4095, dark - light
  int humidity = dht.getHumidity();
  String humidityOutput = String(humidity); //0-100%
  int moisture = 0; //========================================wait till get the sensor
  String moistureOutput = String(moisture);
  int tempC = dht.getTempCelcius();
  String tempCOutput = String(tempC);
  int tempF = dht.getTempFarenheit();
  String tempFOutput = String(tempF);

  Particle.publish("liquidLevel", liquidLevelOutput, PRIVATE); //send data to webhook
  Serial.print("liquid level ");
  Serial.println(liquidLevel);
  delay(30000);
  Particle.publish("photoCell", photoCellOutput, PRIVATE);
  Serial.print("light");
  Serial.println(photoCell);
  delay(30000);
  Particle.publish("humidity", humidityOutput, PRIVATE);
  Serial.print("Humid: ");
	Serial.println(humidity);
  delay(30000);
  Particle.publish("tempC", tempCOutput, PRIVATE);
  Serial.print("TempC: ");
	Serial.println(tempC);
  delay(30000);
  Particle.publish("tempF", tempFOutput, PRIVATE);
  Serial.print("TempF: ");
  Serial.println(tempF);
  delay(30000);
  Particle.publish("moisture", moistureOutput, PRIVATE);
  Serial.print("Soil Moisture: ");
  Serial.println(moisture);
  delay(30000);

}

void waterPlant(const char *event, const char *data) {
  digitalWrite(waterPump1, HIGH);
  Particle.publish("pumpstatus", "1", PRIVATE); //give a signal of successful watering
  delay(3000); //pump water for 3 seconds
}

void sprayWater(const char *event, const char *data) {
  digitalWrite(waterPump2, HIGH);
  Particle.publish("spraystatus", "1", PRIVATE); //give a signal of successful spraying
  delay(3000); //spray water for 3 seconds
}

void closeBlinds(const char *event, const char *data) {
  servoPos = 0;
  myServo1.write(servoPos);
  myServo2.write(servoPos);
  delay(1000);
}

void openBlinds(const char *event, const char *data) {
  servoPos = 180;
  myServo1.write(servoPos);
  myServo2.write(servoPos);
  delay(1000);
}
