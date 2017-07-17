# Sprint 3: Connectivity

### Sprint Catalog

- Find a way to pair device and access sensor value remotely

### Sprint Review  

This is an exploratory sprint as I have looked into different ways to connect Particle Photon with a website. Before this sprint, I have integrated 10-segment LED bar with LM3914 to visualize the values of the sensor but that's not enough for me. Therefore, I want to try the webhook and IOS HomeKit to see if they are helpful.

I successfully connect my data with thingspeak.com by creating cloud event and transform sensor value to string. Thingspeak.com provides good data visualization as it allows user to customize the graphs and charts. However, it can only receive and updata every 30 seconds, which makes the process quite slow. Therefore, I also tried the iPhone HomeKit by using the Particle version of Homebridge. Then, I found out that the homebridge currently only supported temperature sensor, humidity sensor and LED light. It does not support the soil moisture sensor. Moreover, homebridge gets updated recently and is not stable, sometimes the Siri does not work and the sensor cannot get updated.

In the next sprint, I am going to try to use JavaScript and HTML/CSS to build a website to access the values of the sensors and control the water pump.


### End of Sprint Prototype

[Code for device 1](https://github.com/daraghbyrne/advancediot2017/tree/master/students/rtao1/sprint-3/Code/Device%201)

[Code for device 2](https://github.com/daraghbyrne/advancediot2017/tree/master/students/rtao1/sprint-3/Code/Device%202)

### Sprint Retrospective 

This sprint generally went well - I successfully connect the device with thingspeak.com using webhooks and iPhone via homebridge. The problem is neither of the solutions is satisfied:
- Using thingspeak.com is slow (update every 30s) and does not support water pump control
- Homebridge is not stable due to recent update (changed the structure)

### Next

- Use HTML/CSS and JavaScript to access the values of the sensors and control the water pump
- Test the device to achieve a better user experience
