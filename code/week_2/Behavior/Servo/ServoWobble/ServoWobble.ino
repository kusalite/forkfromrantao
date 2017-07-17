int servoPin = A4;
int servoPosition = 0;
Servo servo;

bool shouldWobble = false;

void setup()
{
  Serial.begin( 9600 );
  Particle.function( "wobble", doWobble );
  servo.attach( servoPin );
  servo.write(90);

}

void loop()
{
  if( shouldWobble ){

	  shouldWobble = false ;
		wobble();
  }

  delay(100);
}


void wobble(){

  for(int i = 0; i < 10; i++ )  // goes from 0 degrees to 180 degrees
  {                                  // in steps of 1 degree
    servo.write(70);
    delay(100);
    servo.write(110);
    delay(100);
  }

}


int doWobble( String command ){

  shouldWobble = true ;

  return 1;

}
