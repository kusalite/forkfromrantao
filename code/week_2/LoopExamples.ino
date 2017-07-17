// FOr loops

void loop()
{
  doSomething();
  doSomethingElse();

  for( int i = 0; i < 100; i++ )
  {
    tone( 1)
    delay( 100);

  }


}


// While loops

int i = 0;
while( i < 5 ){

  i++;
}


void loop()
{
  while( digitalRead(D0) == HIGH){
    delay( 100 );
  }
  // now do the stuff i really want...
}




void doSomething()
{

}

void doSomethingElse()
{

}


