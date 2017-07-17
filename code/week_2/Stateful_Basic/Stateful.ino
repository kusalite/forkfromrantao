/*

	THIS IS A QUICK EXAMPLE OF A PROJECT THAT INVOLVES 
	A SERIES OF STATES
	
	Imagine we're making a Pomodoro timer
	You'll have a few different states
  Like this https://blog.particle.io/2016/06/28/neopixels/

	The Pomodoro Technique is simple–to keep yourself alert and productive, 
	work in 25 minute intervals then give yourself a 5 minute break. 
	A 25 minute work period and 5 minute rest period constitutes one “pomodoro”. 
	After four cycles, you should give yourself a longer break of 15-30 minutes. 
	Four cycles of work and rest is called a “cycle” or “set”.

  We would have 
	- A neopixel ring
	- A a button to start/stop
	- A piezo to make a beep in between intervals

	Simple. 

	First we're going to have a few states
	- We'll want to show that the device is started up and ready to roll
	- We'll want a waiting to start state (i.e. nothing's happening)
	- We'll want a state for the main interval
	- We'll want a state for the 5 minute reset state

	Each of these will have different behaviors and actions.

	First let's define the states that we want...

*/

# define STATE_WELCOME 0
# define STATE_WAITING 1
# define STATE_INTERVAL 2
# define STATE_INTERVAL_COMPLETED 3
# define STATE_RESTING 4
# define STATE_RESTING_COMPLETED 5

// we also need a variable to store the state...

int state = 0;

// We know we have a few inputs so
// set them up

int buttonPin = D0;
int buttonValue = LOW;



void setup() {

 Serial.begin(9600);
 Serial.println("setup complete");
 
 // add the button with a pull up resistor
 pinMode( buttonPin, INPUT_PULLUP );
 
 

}


void loop() {

	// Our loop becomes a place to decide which state is shown 
	// And nothing more.
	// Each separate function controls output and input indepedently
	

 switch( state ){
   case STATE_WELCOME:
     doWelcomeState();
     break;
   case STATE_WAITING:
     doWaitingState();
     break;
   case STATE_INTERVAL:
     doIntervalState();
     break;
   case STATE_INTERVAL_COMPLETED:
		 doIntervalCompletedState();
     break;
   case STATE_RESTING:
		 doRestingState();
     break;
   case STATE_RESTING_COMPLETED:
		 doRestingState();
     break;

 }


}




void getButtonValue()
{
 buttonState = digitalRead(buttonPin);

}

