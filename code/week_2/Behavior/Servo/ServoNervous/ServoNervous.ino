int servoPin = A4;
float servoPosition = 0.0;
int servoTarget = 0;
float speed = 0.025;
Servo servo;

void setup()
{
  Serial.begin( 9600 );

  Particle.function( "pos", setPosition );
  Particle.function( "speed", setSpeed );
  Particle.function( "hello", sayHello );
  servo.attach( servoPin );
  servo.write( servoPosition );

}

void loop()
{



	if( servoPosition > ( servoTarget * 0.95 ) && servoTarget > 0 ){
      servoPosition = servoTarget =  0 ;
      servo.write( 0 );
	}

  if( servoPosition != servoTarget ){
        servoPosition = servoPosition + (servoTarget - servoPosition) * speed;
        Serial.println( servoPosition );
        servoPosition = constrain( servoPosition, 0, 180 );
        servo.write( (int)servoPosition );
  }

  delay(50);
}



int sayHello( String command ){
  servoTarget = random( 90, 180 );
  return 1;
}


int setSpeed( String command){
  Serial.println( "setSpeed: " + command );

  float value = command.toFloat();
  if( value < 0 ) return -1;
  if( value > 1 ) return -1;

  speed = value;

  return 1;

}

int setPosition( String command ){

  Serial.println( "setPosition: " + command );

  int value = command.toInt();
  if( value < 0 ) return -1;
  if( value > 180 ) return -1;

  servoTarget = constrain( value, 0, 180 );
  return 1;

}