
// This example connects the FSR and photocell without calibrating it.

int fsrPin = A0;
int fsrValue = 0;
int fsrMin = 4095;
int fsrMax = 0;
int fsrCalibrated = 0;

int photoCellPin = A1;

int photoCellMin = 4095;
int photoCellMax = 0;
int photoCellCalibrated = 0;

// the number of samples to capture
// filterSamples should  be an odd number, no smaller than 3
#define filterSamples   13
int photoCellSampleArray [filterSamples];   // array for holding raw sensor values for sensor2

int photoCellRawValue = 0;
int photoCellSmoothedValue = 0;

void setup()
{
  Serial.println( 9600 );

  // init the array
  for(int i=0; i<filterSamples; i++) photoCellSampleArray[i]= 0;
}

void loop()
{
  fsrValue = analogRead( fsrPin );

  // read and smooth the photo cell
  photoCellRawValue = analogRead( photoCellPin );
  photoCellSmoothedValue = digitalSmooth( photoCellRawValue , photoCellSampleArray );
  // finally calibrate it
  calibratePhotoCell();

  Serial.print( "fsr: \t" );
  Serial.print( fsrValue );
  Serial.print( "\tc-fsr: \t" );
  Serial.print( fsrCalibrated );
  Serial.print( "; \t\tphoto: \t" );
  Serial.print( photoCellRawValue );
  Serial.print( "; \t\ts-photo: \t" );
  Serial.print( photoCellSmoothedValue );
  Serial.print( "\tc-photo: \t" );
  Serial.println( photoCellCalibrated );

  delay( 1000 );
}

void calibrateFsr()
{
  if( fsrValue > fsrMax ) fsrMax = fsrValue;
  if( fsrValue < fsrMin ) fsrMin = fsrValue;
  if( fsrMin == fsrMax )
    fsrCalibrated = fsrValue;
  else
    fsrCalibrated = map( fsrValue, fsrMin, fsrMax, 0, 1000 );
}

void calibratePhotoCell()
{
  if( photoCellSmoothedValue > photoCellMax ) photoCellMax = photoCellSmoothedValue;
  if( photoCellSmoothedValue < photoCellMin ) photoCellMin = photoCellSmoothedValue;
  if( photoCellMax == photoCellMin )
    photoCellCalibrated = photoCellSmoothedValue;
  else
    photoCellCalibrated = map( photoCellSmoothedValue, photoCellMin, photoCellMax, 0, 4095 );
}


/* digitalSmooth
 a digital low-pass filter smoothing function, useful for removing sensor jitter, and glitches
 Paul Badger 2007
 Function from http://playground.arduino.cc/Main/CodeLib

 A digital smoothing filter for smoothing sensor jitter
 This filter accepts one new piece of data each time through a loop, which the
 filter inputs into a rolling array, replacing the oldest data with the latest reading.
 The array is then transferred to another array, and that array is sorted from low to high.
 Then the highest and lowest %15 of samples are thrown out. The remaining data is averaged
 and the result is returned.

 Every sensor used with the digitalSmooth function needs to have its own array to hold
 the raw sensor values. This array is then passed to the function, for it's use.
 This is done with the name of the array associated with the particular sensor.

 int dataValue is the current sensor reading
 int *sensorSampleArray" passes an array to the function
	- the dataValue indicates the array name is a pointer
 */


int digitalSmooth(int dataValue, int * sensorSampleArray ){
	int j, k, temp, top, bottom;
	long total;
	static int i;
	static int sorted[filterSamples];
	boolean done;

	// increment counter and roll over if necc. -  % (modulo operator) rolls over variable
	i = (i + 1) % filterSamples;
	sensorSampleArray[i] = dataValue;                 // input new data into the oldest slot

	for (j=0; j<filterSamples; j++){     // transfer data array into anther array for sorting and averaging
		sorted[j] = sensorSampleArray[j];
	}

	// flag to know when we're done sorting
	done = 0;
	// simple swap sort, sorts numbers from lowest to highest
	while(done != 1){
		done = 1;
		for (j = 0; j < (filterSamples - 1); j++){
			if (sorted[j] > sorted[j + 1]){
				// numbers are out of order - swap
				temp = sorted[j + 1];
				sorted [j+1] =  sorted[j] ;
				sorted [j] = temp;
				done = 0;
			}
		}
	}

	// throw out top and bottom 15% of samples - limit to throw out at least one from top and bottom
	bottom = max(((filterSamples * 15)  / 100), 1);
	top = min((((filterSamples * 85) / 100) + 1  ), (filterSamples - 1));
	// the + 1 is to make up for asymmetry caused by integer rounding

	k = 0;
	total = 0;
	for ( j = bottom; j< top; j++){
		// total remaining indices
		total += sorted[j];
		k++;
	}

	// divide by number of samples
	return total / k;
}
