# Sprint 2: Adding Intelligence

### Sprint Catalog

Before this sprint, I have completed assembling and using water level sensor, analog light sensor, and DHT22 temperature and humidity sensor to monitor the status of the plant.
In this sprint, I need to implement the soil moisture sensor and use another Photon to communicate with the first Photon that is hooked up with sensors.
The second Photon needs to connect with 10-segment LED bar, LM3914 driver, buttons and LED so that it can work as a control terminal.


### Sprint Review  

I have spent most of my time in figuring out how to use the LM3914 driver to drive the 10-segment LED bar. The input from the sensor is 0-4095 while the analog output from Photon is 0-255. Therefore, I need to map the sensor value within the pin output range. Another challenge is that the output signal from the pin is using PWM which does not compatible with the LM3914. Therefore, I need to add a lowpass filter circuit which contains a resistor and a capacitor. I also need to use analogwrite with maximum frequency instead of the default one. That's the biggest challenge in this sprint.

#### Play with HomeKit and Thingspeak

I have also spent some time in researching on how to acquire data remotely. I have tried thingspeak.com, which can get sensor value every 30 second from Particle cloud and visualize it. I also tried to connect Particle with HomeKit because I want to use Siri to control the device. 

### End of Sprint Prototype

[Code: MonitorSensor](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/sprint-2/MonitorSensor.ino)

[Code: RemoteControl](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/sprint-2/RemoteControl.ino)

### Sprint Retrospective 

I have learned a lot from this sprint, both hardware and software. For hardware, I learned the knowledge of analog output. For software, I have learned some skills relates webhook and homebridge. However, the homebridge has a lot of limitation and the thingspeak.com can only update data every 30 second. I need to consider another way to make a customized web app for the device.


### Next

For the next sprint, I want to spend some time in using jQuery to get Particle cloud data and using those data to make a web app.
