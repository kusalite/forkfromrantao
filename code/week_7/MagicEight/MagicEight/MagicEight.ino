/*
Recoil Viewer designed by AB9VH Electronics, James Douglas III - 2012
Sparkfun ADXL193 single axis accelerometer, 5v reference

X axis analog pin 0
Ground, black wire
+5v, red wire  (Vin: voltage input 5v)
ZERO G = 2048  (calibration data)
*/

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <math.h>

// EEPROM Struct for storing application settings

int eeprom_address = 10;
struct MagicEightSettings {
  uint8_t version;
  int waitTimeFromShake;
  char last_selection [256];
  char sheet_name[256];
};

MagicEightSettings settings; // stores the main settings


// OLED SETUP

#define OLED_DC     D3
#define OLED_CS     D4
#define OLED_RESET  D5
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

// SINGLE AXIS ACCEL

const int accelPin = A0;
int currentAccelX = 0;
int currentAccelXSmoothed = 0;
int currentRecoil = 0;  // recoil reading in g force
int baselineX = 0; // store a calibrated baseline X.
int minX = 2048;
int maxX = 0;

// Weighted Average Filter
const int numSamples = 7;
int sampleArray[numSamples];

bool isShaking = false;
unsigned long shakeTimeStart = 0;
unsigned long shakeDuration = 0;
//unsigned long requiredShakeTime = 3000; // this is superseeded by the settings.

bool chooseNew = false;

void setup() {
  Serial.begin(9600);            // opens serial port for LCD shield

  Serial.println( "Starting up... ");

  // Smoothening array
  for(int i=0; i<numSamples; i++) sampleArray[i]= 0;

  Serial.println( "Loading settings. ");
  loadSettingsFromMemory();

  display.begin(SSD1306_SWITCHCAPVCC);

  Serial.println( "Registering functions ");
  Particle.function( "setWaitTime", updateWaitTime );
  Particle.function( "shake", triggerManualShake );
  Particle.function( "setList", changeDataSourceTo );

  Serial.println( "Registering events ");
  Particle.subscribe( "hook-response/magic8_list_sheets", gotSheetData, MY_DEVICES);
  Particle.subscribe( "hook-response/magic8_list_items", gotSheetItemData, MY_DEVICES);

  Serial.println( "Requesting sheets ");
  Particle.publish("magic8_list_sheets");

  Serial.println( "Starting calibration ");
  doZeroCalibration( );


}

int numSheets = 0;
String sheets [255];
String sheetNames [255];

int numItems = 0;
String eightBallItems[255];

void gotSheetData(const char *name, const char *data) {
    Serial.print("Running magic8_list_sheets function");

    Serial.println( data );
    Serial.println( "-----------");

    String dataString = String( data );
    int len = dataString.length();

    int index = 0;
    numSheets = 0;

    while( dataString.indexOf(',', index) > 0 && index < len )
    {
      int nextIndex = dataString.indexOf(',', index);
      String part = dataString.substring( index, nextIndex  );
      String name = part.substring( 0, part.indexOf( ":" ) );
      String urlID = part.substring( part.lastIndexOf( "/" ) + 1 );

      sheets[ numSheets ] = urlID;
      sheetNames[ numSheets ] = name;

      Serial.print( "index: " );
      Serial.print( numSheets );
      Serial.print( "\turlID: " );
      Serial.print( urlID );
      Serial.print( "\tname:" );
      Serial.println( name );

      index = nextIndex+1;
      numSheets = numSheets + 1 ;
    }

    Serial.print( "NUmber of Sheets = ");
    Serial.println( numSheets );

    Serial.print( "Calling data for " );
    Serial.println( sheets[ 0 ] );

    loadPreferedOrDefaultEightBallData( sheets[ 0 ] );

}

void loadPreferedOrDefaultEightBallData( String defaultSheet )
{
    Serial.println( "loadPreferedOrDefaultEightBallData" );

    String preferred = String( settings.sheet_name );

    Serial.print( "prefered is " );
    Serial.println( preferred );

    if( preferred.length() > 1 )
    {
      for( int i = 0; i < numSheets; i++ ){
        Serial.print( "\t " + sheets[i] );
        if( preferred.equals( sheets[i] )  ){
          Serial.println( "\t loading preferred" );
          loadNewEightBallData( preferred );
          return;
        }

      }
    }
    Serial.println( "\t loading default" );
    loadNewEightBallData( defaultSheet );

}

void loadNewEightBallData( String sheetName )
{
    Serial.print( "loadNewEightBallData for"  );
    Serial.println( sheetName );

    Particle.publish("magic8_list_items", sheetName );

    numItems = 0;

    char charS[256];
    sheetName.toCharArray( charS, 256 );
    //settings.last_selection = charS;
    strncpy( settings.sheet_name , charS , 256 );

    saveSettingsToMemory();
}






void gotSheetItemData(const char *name, const char *data) {
    Serial.print("Running magic8_list_items function");

    Serial.println( data );
    Serial.println( "-----------");

    String dataString = String( data );
    int len = dataString.length();

    int index = 0;
    numItems = 0;
    while( dataString.indexOf(',', index) > 0 && index < len )
    {
      int nextIndex = dataString.indexOf(',', index);
      String part = dataString.substring( index, nextIndex );
      eightBallItems[ numItems ] = part;

      Serial.print( "eightball item: " );
      Serial.println( part );

      index = nextIndex+1;
      numItems = numItems + 1 ;
    }

    Serial.print( "NUmber of items = ");
    Serial.println( numItems );

    chooseNew = true;

}



void loop() {

  updateAccelerometer();

  if( numItems < 1 )
  {
    showWaitingForData( );
    delay( 100 );
    return;
  }

  // was moving and has now stopped...
  if( chooseNew )
  {
    selectRandom();

    wipeAndShowNewSelection();

    chooseNew = false;

  }

  // is being shaken ....
  if( isShaking == true )
  {
    showShakeAnimation();
  }else{
    showSelectionOnScreen( true, true );
  }

  delay( 100 );

}

void showShakeAnimation(){

  // draw a circle, 10 pixel radius
  int numCircles = map( currentAccelX , 0, 2047, 0, 5 );
  for( int i = 0 ; i < numCircles; i++ ){

    int x = random( display.width() );
    int y = random( display.height() );

    display.fillCircle( x, y , 2, WHITE);
    display.display();
    delay( 50 );
  }

}

void wipeAndShowNewSelection(){

  for( int i = 0; i < display.height(); i++ )
  {
    display.drawFastHLine( 0, i, display.width(), WHITE );
    display.display();
    delay( 5 );
  }

  for( int i = 0; i < display.height(); i++ )
  {
    display.clearDisplay();
    showSelectionOnScreen( false, false );
    display.fillRect( 0, 0, display.width(), display.height() - i , WHITE );
    display.display();
    delay( 5 );
  }

  showSelectionOnScreen( true, true );


}

void showSelectionOnScreen( bool clearDisplay, bool displayImmediately )
{
  // display the last item
  if( clearDisplay )
    display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println( settings.last_selection );

  if( displayImmediately )
    display.display();

}

void showWaitingForData(  )
{
  // display the last item
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println( "Loading data..." );

  display.display();

}


/* ============================================================
 * ============================================================
 * SAMPLE ACCEL
 * ============================================================
 * ============================================================ */

void updateAccelerometer()
{
  int reading = analogRead( accelPin );
  // convert it to absolute force reading based on the baseline
  currentAccelX = abs( reading - baselineX );
  if (currentAccelX < minX) minX = currentAccelX;
  if (currentAccelX > maxX) maxX = currentAccelX;

  //currentAccelXSmoothed = weightedAverage(  currentAccelX, sampleArray, 0.4 );
  currentAccelXSmoothed = easeToNewReading(  currentAccelX, 0.2 );

  int movingThreshold = max( 100, maxX / 10 );

  /*
  Serial.print( "currentAccelX =  ");
  Serial.print( currentAccelX );
  Serial.print( "\t currentAccelX =  ");
  Serial.print( currentAccelXSmoothed );
  Serial.print( "\t movingThreshold = ");
  Serial.println( movingThreshold );
  */

  if( currentAccelXSmoothed > movingThreshold ){
      isShaking = true;
      if( shakeTimeStart < 1 ){
        shakeTimeStart = millis();
        display.clearDisplay();
        Serial.println( "Starting shake ");
      }
      Serial.println( "...shaking ");

  }else{
      if( isShaking )
      {
        Serial.println( "Stopped Shaking ");
        shakeDuration = millis() - shakeTimeStart;
        if( shakeDuration > settings.waitTimeFromShake )
        {
          chooseNew = true;
        }
      }

      shakeTimeStart = 0;
      isShaking = false;

  }

  //currentRecoil = (currentAccelX-2047)*.25;
  //Serial.print("Current recoil = ");
  //Serial.print(currentRecoil);
  //Serial.println("g");


}

int previousMax = 0 ;

float easeToNewReading( int rawValue, float easing )
{
  if( rawValue > previousMax ){
    previousMax = rawValue;
    return rawValue;
  }

  // if its below this we take the difference pluce
  int diff = abs( rawValue - previousMax );

  float result = previousMax - (diff*easing);

  /*
  Serial.print( "Easing to: " );
  Serial.print( rawValue );
  Serial.print( "\t previousMax = " );
  Serial.print( previousMax );
  Serial.print( "\t diff = " );
  Serial.print( diff );
  Serial.print( "\t result = " );
  Serial.print( result );
  */

  if( rawValue + 5 > result )
    result = 0.0f;

  previousMax = result;


  return result;
}

float weightedAverage( int rawValue, int * sensorSampleArray , float weight )
{

  int avg = 0;
  int max = 0;
  for (int j=0; j< numSamples - 1; j++){
		avg += sensorSampleArray[j];
    if( sensorSampleArray[j] > 0 ) max = sensorSampleArray[j];
	}
  avg = avg / numSamples;

  // creat a weighted filter
  float result = (weight * rawValue) + (1.0-weight)*avg;
  //float result = (weight * rawValue) + (1.0-weight)*max;

  // finally get ready for the next round...

  // move the samples down 1
  for (int j=1; j< numSamples - 1; j++){
		sensorSampleArray[j-1] = sensorSampleArray[j];
	}
  // assign the raw sample into the sample array
  sensorSampleArray[ numSamples-1 ] = rawValue;


  // return the result:
  return result;

}

/* ============================================================
 * ============================================================
 * SELECTION OF OBJECTS...
 * ============================================================
 * ============================================================ */

// Data for testing replaced with eightBallItems[255]
//String selectionData [] = { "Daisey Crays","Petra Heitkamp","Winnifred Dymond","Valery Gladstone","Afton Rueda","Soila Fluke","Shirely Nottingham","Bobby Dalessio","Kyla Taitt","Imogene Renzi" };

String selectRandom()
{
  // This should become more sophisticated with a random hat draw.
  int r = random( numItems );

  // update the last pick in the settings
  String currentSelection = eightBallItems[ r ];

  char charS[256];
  currentSelection.toCharArray( charS, 256 );
  //settings.last_selection = charS;
  strncpy( settings.last_selection , charS , 256 );

  saveSettingsToMemory();

  announceNewSelection( currentSelection );

  return currentSelection;

}

void announceNewSelection( String s )
{
  Serial.print( "new selection = " );
  Serial.println( s );
  Particle.publish("com.db/8ball/selection", s );
}

/* ============================================================
 * ============================================================
 * FUNCTIONS TO UPDATE THE UI
 * ============================================================
 * ============================================================ */

int updateWaitTime( String command )
{
  Serial.print( "updateWaitTime received: " );
  Serial.println( command );

  int waitTimeInSeconds = command.toInt();

  if( waitTimeInSeconds > 0 )
  {
    //waitTimeFromShake = waitTimeInSeconds * 1000;
    settings.waitTimeFromShake = waitTimeInSeconds * 1000;
    saveSettingsToMemory();

    return 0;
  }
  return -1;
}

int triggerManualShake( String command )
{
  //selectRandom();
  chooseNew = true;
  return 0;
}

int changeDataSourceTo( String command )
{
  Serial.print( "changeDataSourceTo received: " );
  Serial.println( command );

  int sheetSource = command.toInt();

  if( sheetSource > 0 && sheetSource < numSheets +1 )
  {
    // sheet iD
    String sheetID = sheets[sheetSource-1];
    //Particle.publish("magic8_list_items", sheetID );
    loadNewEightBallData( sheetID );
    return 1;
  }
  //selectRandom();
  //chooseNew = true;
  return 0;


}





/* ============================================================
 * ============================================================
 * INITIAL CALIBRATION OF SINGLE AXIS ACCEL.
 * ============================================================
 * ============================================================ */

void doZeroCalibration()
{
  // take 10 samples 1/2 second apart and get the average
  int numSamples = 10;
  int avgSample = 0 ;

  for( int i = 0; i < numSamples; i++ )
  {
    avgSample += analogRead( accelPin );             // read analog input

    display.clearDisplay();   // clears the screen and buffer
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.setTextSize(1);
    display.println("Calibrating");
    display.setTextSize(4);
    display.println( String( numSamples - i ) );
    display.display();
    delay(500);

  }

  display.clearDisplay();   // clears the screen and buffer
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Calibrating");
  display.setTextSize(4);
  display.println( String( 0 ) );
  display.display();

  baselineX = avgSample / numSamples;
  Serial.println( "Calibration Complete" );
  Serial.print( "Baseline X = " );
  Serial.println( baselineX );

}


/* ============================================================
 * ============================================================
 * HANDLE EEPROM STORAGE OF SETTINGS
 * ============================================================
 * ============================================================ */

void loadSettingsFromMemory()
{
  EEPROM.get( eeprom_address, settings );
  if( settings.version != 2) {
    // EEPROM was empty -> initialize with defaults
    Serial.println( "Setting Defaults" );

    settings = getDefaultSettings();
  }

  Serial.println( "Settings Loaded" );
  Serial.print( "version = " );
  Serial.println( settings.version );
  Serial.print( "waitTimeFromShake = " );
  Serial.println( settings.waitTimeFromShake );
  Serial.print( "last_selection = " );
  Serial.println( settings.last_selection );
  Serial.print( "sheet_name = " );
  Serial.println( settings.sheet_name );

}

struct MagicEightSettings getDefaultSettings(){

  MagicEightSettings defaults = { 2, 1000, "bob", "" };
  return defaults;

}

void saveSettingsToMemory()
{
  EEPROM.put( eeprom_address , settings );
  Serial.println( "Settings Saved to memory" );

}
