# Tutorial: Advanced Inputs: Attaching Interrupts

Interrupts are really useful. You can use them to really quickly detect user input or changing values from some sensors, without having to wait for a loop to happen. They happen *automatically and fast!*

When we want to use interrupts, we start by attaching them (i.e. saying we want to listen for interrupt signals or a change in value from low to high) on a particular pin. This happens in our setup. As part of this definition, we also tell it what function to call. Then when you push a button, flick a switch, or anything like that, you can have the code automatically run a series of actions to deal with it really really fast. 

Really fast is the key. As part of an interrupt function you can’t use delay() or Serial.println(). You also won’t be able to read from slower processes like I2C, TCP, etc. 

You can add an interrupt on any of pins with the exception of D0 and A5 (there are some other [caveats](https://docs.particle.io/reference/firmware/photon/#interrupts))

### How it works: What is an interrupt

> *"An Interrupt's job is to make sure that the processor responds quickly to important events. When a certain signal is detected, an Interrupt (as the name suggests) interrupts whatever the processor is doing, and executes some code designed to react to whatever external stimulus is being fed to the Arduino. Once that code has wrapped up, the processor goes back to whatever it was originally doing as if nothing happened!*

> *What's awesome about this is that it structures your system to react quickly and efficiently to important events that aren't easy to anticipate in software. Best of all, it frees up your processor for doing other stuff while it's waiting on an event to show up…."*

> [From Using Interrupts On Arduino](http://www.allaboutcircuits.com/technical-articles/using-interrupts-on-arduino/)

### Setting up an interrupt

This goes in the setup()

````
attachInterrupt ( pin , function , mode );
````

Where ‘pin’ is the pin number you want to attach an interrupt on, and  ‘function’ is the function to call when the interrupt occurs and ’mode’  defines when the interrupt should be triggered:

* CHANGE to trigger the interrupt whenever the pin changes value,

* RISING to trigger when the pin goes from low to high,

* FALLING for when the pin goes from high to low.

And then you need to add a matching function name in your code. This function should return nothing (i.e. have a void type) and have no parameters

__Note:__   pinMode() MUST be called prior to calling attachInterrupt() to set the desired mode for the interrupt pin (INPUT, INPUT_PULLUP or INPUT_PULLDOWN)

### Your Interrupt Function

It’s not a standard function, it’s limited. Because again, they’ve got to run F.A.S.T.

That means, inside the attached function, <code>delay()</code> won't work and the value returned by <code>millis()</code> will not increment. Serial data received while in the function may be lost. 

Typically global variables are used to pass data between this function and the main program. To make sure variables are updated correctly, declare them as *volatile i.e. add the word ‘volatile’ as a prefix to the variable definition*.

You should also write your interrupt function to be as SHORT and as FAST as possible. Less really is more here. 

If it’s going to take extensive code to do what you’d like to, put this code in the loop(). The interrupt function should only do what’s absolutely essential. 


### A caveat

You can't use D0 or A5 for Interrupts. This is because it's already used in the background to support the Mode button's external interrupt line. Additionally, some pins have shared internals for interrupts so you can only attach an interrupt to: 

- D1 or A4
- D2 or A0 or A3
- D3 or DAC
- D4 or A1


### A really simple example

*Notice that this looks a little different - there’s almost nothing in the loop! *

````
int button_pin = D1;

int led_pin = D0;

volatile int state = LOW;

void setup() {

    pinMode(button_pin, INPUT);

    pinMode(led_pin, OUTPUT);

    attachInterrupt( button_pin , blink, CHANGE);

}

void loop() {

    // Nothing here … 

}

void blink() {

    state = !state;
    digitalWrite(pin, state);

}
````

### Why use them?

Well now your Particle can multitask. Isn’t that great? 

And… 

... you don’t need to write loop code to continuously check for the high priority external events like button pushes. You can handle them when they happen; and only then.

> "Interrupts are a simple way to make your system more responsive to time sensitive tasks. They also have the added benefit of freeing up your main `loop()` to focus on some primary task in the system."

You don’t have to worry about missing button pushes because of long or slow loops!

### Read more:

* [https://docs.particle.io/reference/firmware/photon/#interrupts](https://docs.particle.io/reference/firmware/photon/#interrupts) 

* [https://learn.adafruit.com/multi-tasking-the-arduino-part-2/external-interrupts](https://learn.adafruit.com/multi-tasking-the-arduino-part-2/external-interrupts)

* [http://www.allaboutcircuits.com/technical-articles/using-interrupts-on-arduino/](http://www.allaboutcircuits.com/technical-articles/using-interrupts-on-arduino/) 

* https://www.arduino.cc/en/Reference/AttachInterrupt

