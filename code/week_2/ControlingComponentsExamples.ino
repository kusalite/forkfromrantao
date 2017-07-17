
int lastBlink = 0;
int blinkAfter = 200;
bool blinkOn = false;

void loop() {

	int f = readFromSensor();
	
  //float value = breathe();
  //delay( 50 );
	
	if( lastBlink + blinkAfter < millis() ){
		
		if( blinkOn ){
			digitalWrite( D0, HIGH); 
		}else{
			digitalWrite( D0, LOW); 
		}

		lastBlink = millis();
		blinkOn = !blinkOn;
		
	}
	
	
}


int fadeValue = 0;
int fadeDirection = 1; 



void fadeUpAndDown(){
	
	analogWrite( D0, fadeValue );
	
	if( fadeDirection == 1){
		fadeValue++;
		if( fadeValue >= 255) fadeDirection = -1;		
	}else{
		fadeValue--;		
		if( fadeValue <= 0) fadeDirection = +1;		
	}
	
	
	
}

int readFromSensor(){
	
	// x , y, z,
	int xVal = analogRead( A0 );
	int yVal = analogRead( A1 );
	int zVal = analogRead( A2 );
	
	int force = sqrt(xVal * xVal + yVal * yVal + zVal * zVal) ;
	
	return force; 
	
}
