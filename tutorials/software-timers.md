# Advanced Control: Adding Software Timers 

Not only can you listen for external interrupt events - buttons being pressed - and respond to them, but you can also create interrupts based on time. 

Up until now we’ve used millis() to check how much time is elapsed in our loop() and see if something should happen based on that. However, you can also create timers to make stuff happen after a fixed amount of time.

## The nuts and bolts

* You can have up to 10 timers in your code.

* These can fire as fast as every 1 milliseconds; but that’s generally not good practice!

* If several timers fire at the same time, they’ll be processed in sequence, not together. 

* You can start, stop or reset a timer at any point

    * You can have a timer continuously run (no stopping point), or

    * You can have a timer run once

* For timers that run only once, you can use them again at any point by resetting them

## Setting up a timer

A timer is like a variable (it’s really an object). You declare it at the top of your code. 

````

// SYNTAX
Timer timer(period, callback, one_shot)

````

* period is the period of the timer in milliseconds (unsigned int)

* callback is the callback function which gets called when the timer expires.

* one_shot when true, the timer is fired once and then stopped automatically. The default is false - a repeating timer.

````

Once it’s set up, you can use the following functions to control it: 

timer.start(); // starts timer if stopped or resets it if started.

timer.stop(); // stops a running timer.

timer.changePeriod(1000); // Reset period of timer to 1000ms.

timer.reset(); // reset timer if running, or start timer if stopped.

````

## Why use a timer / When to use a timer?

* You have background information you’d like to gather or a webhook you’d like to fire at a particular time. 

* You’d like to move a servo every minute 

* You’d like to run a countdown clock or update a screen every once in a while

* And much much more… 

**Remember: Your interrupt functions should be lightning fast to execute. Slow/long code will block other code from happening.**

## Example Code

````

Timer timer(1000, print_every_second);

void setup()
{
    Serial.begin(9600);
    timer.start();
}

void print_every_second()
{
    static int count = 0;
    Serial.println(count++);
}

````


## Read more:

* [https://docs.particle.io/reference/firmware/photon/#software-timers](https://docs.particle.io/reference/firmware/photon/#software-timers) 

* [https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers](https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers) 


