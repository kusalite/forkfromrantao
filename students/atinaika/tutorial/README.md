# Tutorial: Creating audio outputs

This tutorial will teach you how to use a DFMini player to output songs via a speaker. This is an extremeley powerful tool because providing high fidelity and context relevant audio output is great way to give feedback to a user. Also the ability to play different kinds of music, using an SD card, can make the experience of your IoT product extremely delightful.

## Why a tutorial on this?

While the DF player is a fantastic device, most of the information online talks about using it with an Arduino, not Particle. This led to a lot of challenges, code searching and soul searching during my IoT project. Even the manual on the official product website is technically verbose. So I'd like to make it easy for anyone using a Particle device to work with these great tools.

## Hardware

### Components required

The components I used to output sounds using a Particle Photon were:

|Component Name|Functionality|Specs|Image|Link|
|--------------|:-----------:|:---:|:---:|:--:|
|DF Mini Player|The microcontroller that manages audio output to the speaker and amplifier. <br>The DF Player has a micro SD card slot, connects to Particle Photon and can play, pause, stop and control all your audio files.|Can decode WAV, MP3 and WMA files<br>Supports at max a 32GB micro SD or U card|![alt text](https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint1/students/atinaika/files/tutorial/dfplayer.jpg)|[Buy here](https://www.amazon.com/Industry-Park-Player-Module-Arduino/dp/B01MQ0GFZV/ref=sr_1_3?ie=UTF8&qid=1491680415&sr=8-3&keywords=dfplayer+mini+mp3+player)|
|Audio Amplifier|Mono amplifier able to provide standard gain to incoming audio signal from the DF PLayer|Output Power: 2.5W at 4Ω<br>Fixed 24dB gain<br> onboard trim potentiometer for adjusting input volume.|![alt text](https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint1/students/atinaika/files/tutorial/amp.jpg)|[Buy here](https://www.adafruit.com/products/2130?gclid=CKWr2I7RldMCFcKLswod99cKuQ)|
|Speakers|Mid fidelity 3W speaker set with woofer for playing the audio tracks from the DF Player|Dimensions: 4.5 x 1.1 x 2.5 inches<br>3W, 4 ohm full range stereo speakers|![alt text](https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint1/students/atinaika/files/tutorial/speakers.jpg)|[Buy here](https://www.amazon.com/Gikfun-Speaker-Stereo-Loudspeaker-Arduino/dp/B01CHYIU26/ref=pd_sim_147_1?_encoding=UTF8&pd_rd_i=B01CHYIU26&pd_rd_r=2XKK61WFZC2S8A87E7JQ&pd_rd_w=u1sPO&pd_rd_wg=onzRy&psc=1&refRID=2XKK61WFZC2S8A87E7JQ)|

### Wiring
For starters, below is a schematic of the DF Mini player and its various pins.

![alt text](https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint1/students/atinaika/files/fritzing-diagram.jpg)

Important points to note:
1. The DFMini Player communicates with the Particle using RX/TX pins. <i>RX pin on the Particle connects to the TX pin on the DFPlayer</i>
2. The amplifier connects to the DAC pins and not the Speaker_1/2 pins on the DF Player.
3. The amplifier also connects to 5V power supply, GND and 
4. The speaker connects to the slots in the amplifier

![alt text](https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint1/students/atinaika/files/tutorial/mp3_bb.jpg)

## Configuring SD card
1. Store all audio files in preferably an MP3 format
2. Place all audio files in a folder name in "mp3" in the card's root directory
3. Name all the files "001.mp3","002.mp3"...
4. For Mac users: OSX adds additional hidden directories to the card, like .trash. To solve this go to terminal and run the following command: dot_clean/Volumes/[Name of SD Card]

## Firmware code
Using the Particle IDE, we can set up a communication line between the DF Player and the Photon using Serial1.
Communication is done using byte code viz. a short hex code string is passed through the serial to the DFPLayer which then reads it. 

The byte code passed to the DF Player combines the following: a start byte, end byte, version byte, acknowledge byte, command length, command byte, and 2 parameter bytes. <i>Barring the last 2 mentioned byte, all others (viz. start,end,version,acknowledge and command) remain the same through the code.</i>

For a detailed list of commands, [click here](https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint1/students/atinaika/sprint-1/mp3player/mp3player.ino).

### Steps to writing the code
1. Create a function that will communicate with the serial.
```
void execute_CMD(command, parameter1, parameter2){}
```

2. Calculate the sum of the individual bytes
```
int16_t checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2)
```

3. Build the command line code which will be sent to the DF Player
```
byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge, Par1, Par2, checksum >> 8, checksum & 0xFF, End_Byte}
```

4. Send the byte code to the DF Player
```
for (byte k=0; k<10; k++)
 {
   Serial1.write( Command_line[k]);
 }
```

### Full Example code

> After connecting the circuit as mentioned above and inserting the SD card, run the below example code in your Particle IDE. The code takes command inputs from Particle's serial monitor, so open your Serial monitor. Type "1" in your serial monitor. This will play the next track in the SD card.

```
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

void setup ()
{
 Serial.begin(9600);
 Serial1.begin(9600);

 execute_CMD(0x3F, 0, 0); // Send request for initialization parameters

 while (Serial1.available()<10) // Wait until initialization parameters are received (10 bytes)
 delay(30); // Pretty long delays between succesive commands needed (not always the same)

 // Initialize sound to very low volume. Adapt according used speaker and wanted volume
 execute_CMD(0x06, 0, 50); // Set the volume (0x00~0x30)
}
void loop ()
{
 if (Serial.available())
 {
  // Input in the Serial monitor: Command and the two parameters in decimal numbers (NOT HEX)
  // E.g. 3,0,1 (or 3 0 1 or 3;0;1) will play first track on the TF-card
  byte Command = Serial.parseInt();
  byte Parameter1 = Serial.parseInt();
  byte Parameter2 = Serial.parseInt();

  // Excecute the entered command and parameters
  execute_CMD(Command, Parameter1, Parameter2);

 }

 if (Serial1.available()>=10) // There is at least 1 returned message (10 bytes each)
 {
  // Read the returned code
  byte Returned[10];
  for (byte k=0; k<10; k++)
  	Returned[k] = Serial1.read();
 }
}


void execute_CMD(byte CMD, byte Par1, byte Par2) // Excecute the command and parameters
{
 // Calculate the checksum (2 bytes)
 int16_t checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

 // Build the command line
 byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge, Par1, Par2, checksum >> 8, checksum & 0xFF, End_Byte};

 //Send the command line to the module
 for (byte k=0; k<10; k++)
   Serial1.write( Command_line[k]);

}
```