// Define a pin that we'll place the FSR on
// Remember to add a 10K Ohm pull-down resistor too.
int fsrPin = A0;

// Create a variable to hold the FSR reading
int fsrReading = 0;

// Define a pin we'll place an LED on
int ledPin = D7;

// Create a variable to store the LED brightness.
int ledBrightness = 0;

void setup()
{
  Serial.begin( 9600 );
  // Set up the LED for output
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  // Use analogRead to read the photo cell reading
  // This gives us a value from 0 to 4095
  fsrReading = analogRead(fsrPin);
  Serial.println( fsrReading );

  if( fsrReading > 2000 ){
    // Map this value into the PWM range (0-255)
    // and store as the led brightness
    ledBrightness = map(fsrReading, 0, 4095, 0, 255);

    // fade the LED to the desired brightness
    analogWrite(ledPin, ledBrightness);

    // wait 1/10th of a second and then loop
    tryPublish();
  }


  delay(100);
}

long lastPublish = -1;
int publishAfter = 10000;
String webhookEvent = "sendMessageToDioTSlack";
void tryPublish(){

  if( lastPublish + publishAfter < millis() ){
    String data = "Squeezed to " + String( fsrReading );
    Particle.publish( webhookEvent , data );
    lastPublish = millis();
  }

}
