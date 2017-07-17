
/*
Project: Sleepy Hi
Discription: This device will create a soothing environment to help those that suffer from insomnia and night anxiety, to fall asleep
Author: Ammani
Date: 4/4/2017
Version: 1.1

*/

// Currently, I think this is what is sent to the serial as output verification data. Haven't deleted it because I'm sure
// To understand more about this, look at DFplayer_basic_sample.ino in the audio folder
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]
# define STATE_WELCOME 0 // When you switch on device
# define STATE_LISTENING 1 // When the device is monitering your movement and light
# define STATE_PRIMARY 2 // When the device is putting you to sleep
# define STATE_SECONDARY 3 //  When the device detects you might be waking up and responds minimally to put you back to sleep

int aromapin = D0; // Output to diffuser
int state = 0; // State variable
int ambilight = A0;// This is the input from the ambient light sensor
int movementx = A1;// This is the x input from the accelerometer
int movementy = A2;// This is the y input from the accelerometer
int movementz = A3;// This is the z input from the accelerometer
int Command; // Input for the DF Player
int Parameter1; // Input for the DF Player
int Parameter2; // Input for the DF Player
volatile int state = 0;    // This is for the backround interut task, WHICH ISN'T WORKING
boolean
//attachInterrupt( buttonPin, handleChangeState, RISING);

void setup()
{
  pinMode(aromapin, OUTPUT);   //smell number 1 control pin
  pinMode(ambilight, INPUT);
  pinMode(movementx, INPUT);
  pinMode(movementy, INPUT);
  pinMode(movementz, INPUT);

  execute_CMD(0x3F, 0, 0); // Send request for initialization parameters for the DFplayer

  delay(30); // Pretty long delays between succesive commands needed (not always the same)
  attachInterrupt( buttonPin, handleChangeState, RISING);// if someone waves their hand in front of the device, it will interrupt any state and move to the alternative
  // Initialize sound to very low volume. Adapt according used speaker and wanted volume
  execute_CMD(0x05, 0, 1); // Set the volume (0x00~0x30)

}

void loop()
{
  doWelcomeState();
}

void handleChangeState()
{
  switch( state )
  {
    case STATE_WELCOME:
      // Start pulsing Light
      // It checks if the light is out
      state = STATE_PRIMARY;
      break;
    case STATE_LISTENING:
      // It checks if the light is out and if you're moving to see if you're coming out of sleep
      state = STATE_SECONDARY;
      break;
    case STATE_PRIMARY:
      //Durin this state, the device is actuating the light, aroma and music. The state changes after a set period of time
      state = STATE_LISTENING;
      break;
    case STATE_SECONDARY:
      // During this state, only the aroma and music is actuated. The sound will be softer and the diffuser will be set off less frequently
      state = STATE_LISTENING;
      break;
  }

}

void doWelcomeState()
{
  if (ambilight = LOW)
  {
    state = STATE_PRIMARY;
  }
}

void doListeningState()
{
  // if (ambilight = LOW) && movement is minimal
  state = STATE_SECONDARY;
}

void doPrimaryState()
{
  // In future I will code out the intervals and timings.
  digitalWrite(aromapin, HIGH); //turns smell 1 on the smell release
  // E.g. 3,0,1 (or 3 0 1 or 3;0;1) will play first track on the TF-card
  // Excecute the entered command and parameters
  execute_CMD(Command, Parameter1, Parameter2);
  // At the End
  state = STATE_LISTENING;
}

void doSecondaryState()
{
  // In future I will code out the intervals and timings.
  digitalWrite(aromapin, HIGH); //turns smell 1 on the smell release
  // E.g. 3,0,1 (or 3 0 1 or 3;0;1) will play first track on the TF-card
  // Excecute the entered command and parameters
  execute_CMD(Command, Parameter1, Parameter2);
  // At the End
  state = STATE_LISTENING;
}

/*void moving( movementx, movementy, movementz)
{
  using the variables from the accelerometer, check if the person is moving enough to suggest they are waking up or awake
}*/

/*void lightsOut()
{
  check if there is light in the room
}*/

// Code used for the DFplayer
void execute_CMD(byte CMD, byte Par1, byte Par2) // Excecute the command and parameters
{
 // Calculate the checksum (2 bytes)
 int16_t checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

 // Build the command line
 byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge, Par1, Par2, checksum >> 8, checksum & 0xFF, End_Byte};

 //Send the command line to the module
 for (byte k=0; k<10; k++)
 {
  Serial1.write( Command_line[k]);
 }
}
