# Sprint 2: Adding Intelligence

### Sprint Catalog

For system, the key is to syncronise LED with motor so that the LED can produce a sequence of pulse with presice delay to create POV effect. Two possible solutions:
  1. Precisly control motor speed and use delay to control LED
    1.1 Monitoring motor speed with hall effect sensor or motor encorder
    1.2 Use PID to control motor speed
    1.3 Start timing for LED when hall effect sensor is triggered (every round)
    
  2. Sync led with motor position (encorder data)
  
 For hardware, this round will search for proper motor, controller and prepared for the 2nd build
  

### Sprint Review  

Two motor PID control is achieved with need to further fine tune the PID parameters on the final build
 1. Using hall effect input (10Hz) and calculate RPM based on time of each round (currently used)
 2. Using encorder (4200Hz) and compute PID based on rounds per period (100ms) (as back up as the high frequency of ISR may require             saperate controller 

20*3 pixel display is achieved by usind simple delay() in main loop. A flag is set by the Hall Effect ISR to inform the loop to trigger timer. This may lost 0.5-1ms accuracy but so far it works as expected.

### End of Sprint Prototype

Codes uploaded to the folder

### Sprint Retrospective 

I spent over time on the PID control. I should be focus on the effor to build MVP instead of too many iterations to refind the details.


### Next

Hardware dvelopment for 2nd build with smoother rotation and neopixel dotstart led strip integration 

Push limit of display resolution

Start to create simple app to read photo gps data and send to particle (considering store data in AWS)
