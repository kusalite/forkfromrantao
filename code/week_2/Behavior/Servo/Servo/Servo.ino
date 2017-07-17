int servoPin = A4;
int servoPosition = 0;
Servo servo;

void setup()
{
  Serial.begin( 9600 );
  Particle.function( "pos", setPosition );
  servo.attach( servoPin );
}

void loop()
{
  delay(100);
}

int setPosition( String command ){

  Serial.println( "setSpeed: " + command );

  int value = command.toInt();
  if( value < 0 ) return -1;
  if( value > 180 ) return -1;

  servoPosition = constrain( value, 0, 180 );

  //pinMode( servoPin, OUTPUT );
  servo.write( servoPosition );
  //delay( 1000 );
  //pinMode( servoPin, INPUT );
  return 1;

}
