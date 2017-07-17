# Sprint 1: MVP

### Sprint Catalog

The features implemented in this sprint:
1. Building an adjustable timer
2. Providing tactile feedback through soothing vibrations
3. Giving audio output when timer is switched on

Why were these features chosen?
The tactile feedback and adjustable timer are features that are unique to the Mindful Mat and essential to understanding its value. To display the interactions that these


### Sprint Review  
The primary feature of tactile feedback and adjustable timer have been implemented. Additionally the speaker works during the timer implementation. Interactions need to be reviewed along with additional functions. 

### End of Sprint Prototype
Code for each individual module (timer, vibration and mp3 player) have been included in the folder. The final code has been included in folder "sprint1-final"

![alt text](https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint1/students/atinaika/files/sprint1/Sprint1%20prototype.jpg)

![alt text](https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint1/students/atinaika/files/sprint1/Sprint1%20prototype%202.jpg)

### Sprint Retrospective 
During the sprint cycle, I was able to quickly implement the timer functionality and vibration mechanism. This was because of the fact that I had a clear interaction in mind.

However working with the speaker proved challenging. The reason for the same was because the circuitry and implementation shown online was primarily for Arduino, and not Particle. Also the manual and documentation for the DFPlayer was error prone which led to a loss of man hours.
As learnings, I could have leveraged others' expertise in working with this device earlier to have solved the problem. Additionally there were problems with reading the music from the SD card, due to some hidden files being included into the SD card by Mac OSX.

### Next
Next steps (in priority order):
1. Refine tactile feedback to provide a more soothing vibration
2. Incorporate code to close the timer
3. Build a button/control switch to change between yoga and meditation mode
4. Refine the interaction to set the timer (possibly use double tap)
5. Enable users to change volume and add tracks to the meditation playlist
6. Incorporate a mechanism which can detect if and when the mat has been opened or closed
