# Resources for Sensors and Signal Processing

Two great resources for finding solutions to these problems are

1. Arduino Playground has a section for [Sketches](http://playground.arduino.cc/Main/SketchList#Math). Scroll to the Math section and you'll find a bunch of useful functions that are pretty much instantly usable on Particle. 

2. The [function Library](http://playground.arduino.cc/Main/FunctionLibrary) also has some of the same content and some different content too. 



## Averaging

- [Averaging](https://github.com/MajenkoLibraries/Average) - A simple Arduino library for analysis of number based arrays

## Smoothing

A starting point: [Arduino Tutorial: Simple High-pass, Band-pass and Band-stop Filtering](https://www.norwegiancreations.com/2016/03/arduino-tutorial-simple-high-pass-band-pass-and-band-stop-filtering/)

- A [basic smoothing tutorial](https://www.arduino.cc/en/Tutorial/Smoothing) for Arduino.
- Simple Digital Low Pass filter examples by Paul Badger for Arduino: [1](http://playground.arduino.cc/Main/Smooth) and [2](http://playground.arduino.cc/Main/DigitalSmooth)

- [Microsmooth](https://github.com/AsheeshR/Microsmooth) - A lightweight and fast signal smoothing library for the Arduino platform. This library provides implementations of signal processing algorithms like: Simple Moving Average (SMA) Cumulative Moving Average (CMA) Exponential Moving Average (EMA) Savitzky Golay Filter (SGA) Ramer Douglas Peucker Algorithm (RDP) and Kolmogorov Zurbenko Algorithm (KZA). Immediately useful for Particle too. 

- LibSimpleFilters - [A library of simple filters for Arduino](https://github.com/arc12/LibSimpleFilters)

- MedianFilter - [MedianFilter](https://github.com/daPhoosa/MedianFilter)

## Peak to Peak Analysis

- A primer on the code and math: [Lecture 2: Peak Finding](https://courses.csail.mit.edu/6.006/spring11/lectures/lec02.pdf). Prof. Erik Demaine

- [The code](http://www.geeksforgeeks.org/find-a-peak-in-a-given-array/)

## Simple Gesture Analysis

Before thinking about gestures learn a little more about accelerometers by reading this guide: [Sensing your orientation: how to use an accelerometer](http://physics.rutgers.edu/~aatish/teach/srr/workshop3.pdf). Also contains the trigonometry behind gestures - pitch and roll - which will give you two really useful methods to get a lot of value from your accelerometer.

- Seeed Technology has [a great library](https://github.com/Seeed-Studio/Gesture_Recognition) that should work immediately with Particle for recognizing up to 15 simple gestures using a 3-Axis Digital 16g Accelerometer using the ADXL345. See also the [Magic Braclet](https://www.hackster.io/lawliet-zou/magic-bracelet-941d88) an example project using the Library

- [Detecting Falls](http://www.analog.com/en/analog-dialogue/articles/detecting-falls-3-axis-digital-accelerometer.html) - a detailed breakdown of detecting falls or sudden impact using a 3-axis accelerometer. This is a technique used in a range of scenarios, including protecting harddrives from drops. 

When you want to do a little more like doing classification of long term data. This is when the Particle board will start to be challenged. Storing lots of information and doing advanced computation just aren't in its wheel house. For example this project that uses [Machine learning to distinguish walking and running](https://www.hackster.io/Blue_jack/distinguish-walking-and-running-using-machine-learning-ad7eea). It gathers the data first, stores it on an SD card, and then does the classification after the fact. Not ideal... so... 

## Going Further

If you need to go a lot further and do way more advanced things, you might need to move beyond doing everything on the Particle board. That's where cloud services come in. A platform like [Microsoft Azure](https://azure.microsoft.com/en-us/suites/iot-suite/)'s IoT Suite is probably the way to go. 


Take a look at these two intro videos:

- [Introducing the Microsoft Azure IoT Suite](https://www.youtube.com/watch?v=1RmUO3xWqJE)
- [Microsoft Azure Internet of Things Demo - ”Data Dreams” Realized](https://www.youtube.com/watch?v=1RmUO3xWqJE)

Particle has a tutorial on connecting your Photon and [it's data to Azure](https://docs.particle.io/tutorials/integrations/azure-iot-hub/#example-use-cases) and Microsoft provides a [getting started guide](https://github.com/Azure/connectthedots/blob/master/GettingStarted.md) for IoT devices to talk to Azure. There's also a couple of Particle Libraries [for Azure](https://github.com/dxhackers/azuremobilespark) too!