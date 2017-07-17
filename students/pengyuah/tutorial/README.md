# Tutorial - Rescue your particle
Pengyuan Huang

Usually when we compile the code, syntax error pops in IDE and we have to modify the code before the IDE allows firmware update. But sometimes, the syntax is perfect but some logical (or even random) errors will cause the particle to fail. The error mode varies. The check the device mode by LED color, you may refer to this page:
[Device Modes](https://docs.particle.io/guide/getting-started/modes/photon/)

Of course you will try to amend the code and refresh the firmware again. However, in many of these cases, the Photon is not responding or disconnected from the Particle server due to the error. So what to do?

## Entering Safe Mode

* Hold down BOTH buttons
* Release only the RESET button, while holding down the SETUP button.
* Wait for the LED to start blinking magenta
* Release the SETUP button

[![Alt text](https://v.cdn.vine.co/r/videos/15309F79DD1207875152528998400_34e0e2c865d.3.1.3232358711895501281.mp4.jpg?versionId=BDjb_qEMhVJXvYi8doHhp8ZMepn0.opD)](https://vine.co/v/eZUF2ilvLxJ/embed/simple)

## Particle.process()

Runs the background loop and during `delay()` function, `Particle.process()` checks the Wi-Fi module for incoming messages from the Cloud, and processes any messages that have come in. It also sends keep-alive pings to the Cloud, so if it's not called frequently, the connection to the Cloud may be lost.

In practise, if a `loop()` needs more than 10s to run, high chance the device will be disconnected. Below loop function is an example:

````
loop(){
  currentTime = millis();
  //below while function will cause cause one loop to take more than 15s
  While (millis() < currentTime + 15000){ 
    doSomething();
  }
}
````
  
You will observed the device status LED as: Breathing cyan for 10s as normal then switch to solid green (disconnected). 

How to fix? 

The best practise is always to consider change the logic of loops to have very short loop. This is will make the program efficient and always responsive. 

Only in the extreme condition, below is the last resort: manually add Particle.process() into the where the long pause happens:

````
loop(){
  currentTime = millis();
  //below while function will cause cause one loop to take more than 15s
  While (millis() < currentTime + 15000){ 
    doSomething();
    Particle.process();
  }
}
````

## Application Watchdog

How about a safe guard to save you from resetting the Photon manually? We can use `ApplicationWatchdog wd(timeout_milli_seconds, timeout_function_to_call);`

Application watchdog is a software watchdog (timer) that calls a function when program does not check-in (likely stucked in a loop). We can use this to do a system reset.

````
// EXAMPLE USAGE
// reset the system after 60 seconds if the application is unresponsive
ApplicationWatchdog wd(60000, System.reset);
````

if you want to set a long loop to be exempted from the watchdog, add `Particle.process()` or `wd.checkin()' to the loop:

````
void loop() {
  while (some_long_process_within_loop) {
    wd.checkin(); // resets the AWDT count
  }
}
// AWDT count reset automatically after loop() end
````



