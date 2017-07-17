Timer timer(30000, triggerPublish);

volatile bool itsTime = false;

void setup()
{
    Serial.begin(9600);
    timer.start();
}

void loop(){

	if( itsTime == true ){
		doIt();
		itsTime = false;
	}
	
	//.... 
}

void triggerPublish()
{
    static int count = 0;
    Serial.println(count++);
		
		itsTime = true;
		
		
}