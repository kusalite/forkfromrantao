
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

// use 10 samples for smoothing
const int numSamples = 10;
// and store them in an array
int photoCellSamples[numSamples];
// and hold them in a new variable
// so we don't overwrite the raw value
int photoCellSmoothedValue = 0;

void setup()
{
  Serial.println( 9600 );

  // init the array
  for(int i=0; i< numSamples; i++) photoCellSamples[i]= 0;

}

void loop()
{
  fsrValue = analogRead( fsrPin );
  calibrateFsr();
  photoCellValue = analogRead( photoCellPin );
  smoothPhotoCell();
  calibratePhotoCell();

  Serial.print( "fsr: \t" );
  Serial.print( fsrValue );
  Serial.print( "\tc-fsr: \t" );
  Serial.print( fsrCalibratedValue );
  Serial.print( "; \t\tphoto: \t" );
  Serial.print( photoCellValue );
  Serial.print( "\ts-photo: \t" );
  Serial.print( photoCellSmoothedValue );
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

// Let's do a basic average smoothing
void smoothPhotoCell(){

	int avg = 0;
	for( int i = 1; i < numSamples; i++ )
	{
		photoCellSamples[i-1] = photoCellSamples[i];
		avg += photoCellSamples[i];
	}
  photoCellSamples[numSamples-1] = photoCellValue;
  avg += photoCellSamples[numSamples-1];

	photoCellSmoothedValue = avg / numSamples;

}


void calibratePhotoCell()
{
  if( photoCellSmoothedValue > photoCellMax ) photoCellMax = photoCellSmoothedValue;
  if( photoCellSmoothedValue < photoCellMin ) photoCellMin = photoCellSmoothedValue;
  if( photoCellMin == photoCellMax )
    photoCellCalibratedValue = photoCellSmoothedValue;
  else
    photoCellCalibratedValue = map( photoCellSmoothedValue, photoCellMin, photoCellMax, 0, 4095 );
}
