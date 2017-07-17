int motorPin = D2;

void setup()
{
  pinMode(motorPin, OUTPUT);
  //Serial.begin(9600);
  //while (! Serial);
  //Serial.println("Speed 0 to 255");
}


void loop()
{

    int speed = 100;

    for( int i =0 ; i < 256; i++ )
    {
      analogWrite(motorPin, i);
      delay(200);
    }
    delay(5000);


    for( int i = 0; i < 3 ; i++ ){
      analogWrite(motorPin, speed);
      //digitalWrite( motorPin, HIGH );
      delay(200);
      analogWrite(motorPin, 0);
      delay(200);
    }
    delay(5000);

    for( int i = 0; i < 3 ; i++ ){
      analogWrite(motorPin, speed);
      delay(1000);
      analogWrite(motorPin, 0);
      delay(200);
    }
    delay(5000);

}
