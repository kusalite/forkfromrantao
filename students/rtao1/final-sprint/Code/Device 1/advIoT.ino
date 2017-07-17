//This code is for the Particle Photon that connects with sensors and motors to monitor and take care of plant. The Photon connects to a liquid level sensor, analog light sensor, soil moisture sensor, DHT22 temperature and humidity sensor, and a water pump motor.
#include "Adafruit_DHT.h"

/*#define liquidLevelRESISTOR 560 //liquid level sensor resistor
#define liquidLevelPIN A1 //liquid level sensor*/
#define photoCellPin A0 //analog light sensor
#define soilmoisture A2 //soil moisture sensor
#define DHTPIN D0
#define DHTTYPE DHT22		// DHT 22 (AM2302)
#define waterPump1 D1 //water pump motor

int photoCell;
int humidity;
int moisture;
int tempF;

int waterbyweb(String command); //cloud function

DHT dht(DHTPIN, DHTTYPE); //DHT init setting

void setup()
{
  pinMode(photoCellPin, INPUT);
  /*pinMode(liquidLevelPIN, INPUT);*/
  pinMode(soilmoisture, INPUT);
  pinMode(waterPump1, OUTPUT);

  Particle.variable("photoCell", &photoCell, INT);
  Particle.variable("humidity", &humidity, INT);
  Particle.variable("moisture", &moisture, INT);
  Particle.variable("temp", &tempF, INT);
  /*Particle.variable("motorStatus", &motorStatus, INT);*/

  Particle.function("waterbyweb", waterbyweb);

  Particle.subscribe("waterplant", waterPlant, "57002b001451353432393433");

  dht.begin(); //DHT init
  Serial.begin( 9600 );
}

void loop()
{
  /*int liquidLevel = analogRead(liquidLevelPIN); //0-4095 full to empty
  String liquidLevelOutput = String(liquidLevel); //int to string for webhook*/

  photoCell = analogRead(photoCellPin);
  String photoCellOutput = String(photoCell); //0-4095, dark - light

  humidity = dht.getHumidity();
  String humidityOutput = String(humidity); //0-100%

  moisture = analogRead(soilmoisture);;
  String moistureOutput = String(moisture);

  int tempC = dht.getTempCelcius();
  String tempCOutput = String(tempC);
  tempF = dht.getTempFarenheit();
  String tempFOutput = String(tempF);

  /*Particle.publish("liquidLevel", liquidLevelOutput); //send data Particle Cloud for accessibility
  Serial.print("liquid level ");
  Serial.println(liquidLevel);
  delay(2000);*/
  Particle.publish("photoCell", photoCellOutput);
  Serial.print("light");
  Serial.println(photoCell);
  delay(2000);
  Particle.publish("humidity", humidityOutput);
  Serial.print("Humid: ");
	Serial.println(humidity);
  delay(2000);
  Particle.publish("tempC", tempCOutput);
  Serial.print("TempC: ");
	Serial.println(tempC);
  delay(2000);
  Particle.publish("tempF", tempFOutput);
  Serial.print("TempF: ");
  Serial.println(tempF);
  delay(2000);
  Particle.publish("moisture", moistureOutput);
  Serial.print("Soil Moisture: ");
  Serial.println(moisture);
  delay(1000);
}

int waterbyweb(String command) {
  if(command == "waterit") {
    digitalWrite(D1, HIGH);
    delay(3000);
    return 1;
  }
  else {
    digitalWrite(D1, LOW);
    return -1;
  }
}

void waterPlant(const char *event, const char *data) {
  digitalWrite(D1, HIGH);
  Particle.publish("eventsucceed"); //give a signal of successful watering
  delay(5000); //pump water for 10 seconds
  digitalWrite(D1, LOW);
}
