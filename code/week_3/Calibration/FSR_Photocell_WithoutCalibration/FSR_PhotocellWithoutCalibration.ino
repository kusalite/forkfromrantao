
// This example connects the FSR and photocell without calibrating it.

int fsrPin = A0;
int fsrValue = 0;

int photoCellPin = A1;
int photoCellValue = 0;

void setup()
{
  Serial.println( 9600 );

}

void loop()
{
  fsrValue = analogRead( fsrPin );
  photoCellValue = analogRead( photoCellPin );

  Serial.print( "fsr: " );
  Serial.print( fsrValue );
  Serial.print( "; photo: " );
  Serial.println( photoCellValue );

  delay( 50 );
}
