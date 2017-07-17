int solPin = D0;

int times = 1;
int d1 = 100;
int d2 = 100;

bool shouldDoIt = false;

void setup()
{
  Serial.begin( 9600 );

  Particle.variable( "times", &times, INT );
  Particle.variable( "d1", &d1, INT );
  Particle.variable( "d2", &d2, INT );

  Particle.function( "setTimes", setTimes );
  Particle.function( "setD1", setDelayOne );
  Particle.function( "setD2", setDelayTwo );
  Particle.function( "test", testSolenoid );

  pinMode(solPin, OUTPUT);
}

void loop()
{
  if( shouldDoIt ){
    doIt( times, d1, d2 );
    shouldDoIt = false;

  }
  delay( 100 );

}

void doIt( int times, int d1, int d2 ){
  for( int i = 0; i < times; i++ )
  {
    digitalWrite(solPin, HIGH);
    delay( d1 ) ;
    digitalWrite(solPin, LOW);
    delay( d2 );
  }
}


int testSolenoid( String command ){
  shouldDoIt = true;
  return 1;

}

int setTimes( String command ){

  Serial.println( "setTimes: " + command );
  int value = command.toInt();
  if( value < 0 ) return -1;
  if( value > 20 ) return -1;
  times = constrain( value, 0, 20 );
  return 1;

}

int setDelayOne( String command ){

  Serial.println( "setDelayOne: " + command );
  int value = command.toInt();
  if( value < 10 ) return -1;
  if( value > 20000 ) return -1;
  d1 = constrain( value, 0, 20000 );
  return 1;

}

int setDelayTwo( String command ){

  Serial.println( "setDelayTwo: " + command );
  int value = command.toInt();
  if( value < 10 ) return -1;
  if( value > 20000 ) return -1;
  d2 = constrain( value, 0, 20000 );
  return 1;

}
