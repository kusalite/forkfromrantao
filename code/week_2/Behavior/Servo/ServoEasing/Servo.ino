int servoPin = A4;
int servoPosition = 0;
int servoTarget = 0;
Servo servo;

void setup()
{
  Serial.begin( 9600 );
  Particle.function( "pos", setPosition );
  servo.attach( servoPin );
  servo.write( servoPosition );
}

void loop()
{
  if( servoPosition != servoTarget )
  {
      if( servoPosition > servoTarget ){
          servoPosition--;
      }else{
        servoPosition++;
      }
      servoPosition = constrain( servoPosition, 0, 255 );

      servo.write( servoPosition );
  }

  delay(75);
}

int setPosition( String command ){

  Serial.println( "setSpeed: " + command );

  int value = command.toInt();
  if( value < 0 ) return -1;
  if( value > 180 ) return -1;

  servoTarget = constrain( value, 0, 180 );
  return 1;

}
