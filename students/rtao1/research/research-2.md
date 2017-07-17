# Research Sprint 2
## Algorithm and Sensor Research

_Prompt: Identify 3-5 advanced technical approaches, code implementations, algorithms, software or sensors that are relevant to your project and that could help you make your implementation more robust_

### Summary

As the sensors help to monitor the status of the plant, a key feature for my project is to visualize the values of the sensors. Therefore, I want to use the 10-segment LED bar to reflect the values. However, 10-segment LED bar needs to be driven by an IC that is designed to show the magnitude of an anolog signal. I, then, looked into LM3914 which is designed by National Semiconductor and used to operate displays.

### Findings
#### LM3914 Integrated Circuit
![alt tag](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/research/LM3914.jpg)

This LM3914 driver is easy to use - simply connect it with the 10-segment LED bar and connect the analog-in pin with the sensor output pin. It will automatically drive the LED bar based on the output of the sensor. However, I need to connect it with Particle Photon so that user can see the value remotely.

#### Using LM3914 with Particle Photon
LM3914 drives LED bar based on the sensor output which is ranged from 0 to 4095. The Particle Photon analog output is ranged from 0 to 255. Therefore, a map function is needed to re-map a number from one range to another. That is, a value of fromLow would get mapped to toLow, a value of fromHigh to toHigh, values in-between to values in-between, etc. However, a new problem comes out, the output of the analog pin cannot be recognized by the driver because the output from the analog pin is PWM. 

#### LOW Pass Filter
![alt tag](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/research/Low%20pass%20filter.png)

The analog output rapidly switches from OFF to ON and back to OFF again. The analog value is the ration of OFF time to ON time, known as the Duty Cycle. Therefore, I need to convert that rapid switching to a real voltage by passing the signal through a low pass filter. A simple way to build a low-pass filter is shown above, which will be used a resistor and a capacitor. After using the low-pass filter, the LM3914 successfully drives the 10-segment LED bar and visualized the value of the sensor remotely via another Particle Photon.

### Relevance

These researches helped me successfully integrate the 10-segment LED bar to achieve the function I need. Beyond that, it also gave me a better understanding about the analog output feature of Particle Photon - It will help me deal with analog output on other sensors in the future.
