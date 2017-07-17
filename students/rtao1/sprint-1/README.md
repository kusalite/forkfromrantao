# Sprint 1: MVP



### Sprint Catalog
##### -Finished
1. Monitor the plant through sensors
2. Movable blinds controlled by servo motor
3. Establish webhooks
##### -To-do
1. Neopixel as a status indicator
2. Start building the web application
3. Second Photon with 10 segment LED bar to show value of sensors(once LM3914 arrived)

### Sprint Review  
1. Currently monitor the plant through DHT22 temperature humidity sensor, soil moisture sensor, and analog light sensor. Monitor the water level in the water tank by liquid level sensor. 
2. Establish webhooks between thingspeak.com and Particle Photon. Now, there are five hooks including tempC(Celcius Temperature), tempF(Fahrenheit Temperature), liquidLevel(liquid level), humidity(humidity), photoCell(light). These data will be further integrated into website.


### End of Sprint Prototype
![alt text](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/sprint-1/sprint-1%20photo.jpg "Sprint-1 Photo")
[Code](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/sprint-1/advIoT.ino)


### Sprint Retrospective 

Setting up webhooks is new to me but, luckily, thingspeak.com is very user-friendly and has a good integration with particle cloud. This is a start for developing the website.


### Next
For the next sprint, I nned to prototype a website to utilize the webhooks and control the device. 

