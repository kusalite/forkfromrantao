
// This example connects the FSR and photocell without calibrating it.

int fsrPin = A0;
int fsrValue = 0;
int fsrMax = 0;
int fsrMin = 4095;
int fsrCalibratedValue = 0;

int photoCellPin = A1;
int photoCellValue = 0;
int photoCellMax = 0;
int photoCellMin = 4095;
int photoCellCalibratedValue = 0;


void setup()
{
  Serial.println( 9600 );

}

void loop()
{
  fsrValue = analogRead( fsrPin );
  calibrateFsr();
  photoCellValue = analogRead( photoCellPin );
  calibratePhotoCell();

  Serial.print( "fsr: \t" );
  Serial.print( fsrValue );
  Serial.print( "\tc-fsr: \t" );
  Serial.print( fsrCalibratedValue );
  Serial.print( "; \t\tphoto: \t" );
  Serial.print( photoCellValue );
  Serial.print( "\tc-photo: \t" );
  Serial.println( photoCellCalibratedValue );

  delay( 1000 );
}

void calibrateFsr()
{
  if( fsrValue > fsrMax ) fsrMax = fsrValue;
  if( fsrValue < fsrMin ) fsrMin = fsrValue;
  if( fsrMin == fsrMax )
    fsrCalibratedValue = fsrValue;
  else
    fsrCalibratedValue = map( fsrValue, fsrMin, fsrMax, 0, 1000 );
}


void calibratePhotoCell()
{
  if( photoCellValue > photoCellMax ) photoCellMax = photoCellValue;
  if( photoCellValue < photoCellMin ) photoCellMin = photoCellValue;
  if( fsrMin == fsrMax )
    photoCellCalibratedValue = photoCellValue;
  else
    photoCellCalibratedValue = map( photoCellValue, photoCellMin, photoCellMax, 0, 4095 );
}
