int motorPin = D0;
int motorSpeed = 255;

void setup()
{
  Serial.begin( 9600 );
  Particle.function( "speed", setSpeed );
  pinMode(motorPin, OUTPUT);
}

void loop()
{
  Serial.println( motorSpeed );

  analogWrite( motorPin, motorSpeed );
  delay( 100 ) ;
}

int setSpeed( String command ){

  Serial.println( "setSpeed: " + command );

  int value = command.toInt();
  if( value < 0 ) return -1;
  if( value > 255 ) return -1;

  motorSpeed = constrain( value, 0, 255 );

  return 1;

}
