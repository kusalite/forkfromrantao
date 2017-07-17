# Final Sprint

## Sprint Catalog

The features that were finally implemented in the Mindful Mat were:
1. Setting a Timer
2. Playing meditative music
3. Sending a DND message to close relatives when practise has started
4. Pausing timer if user gets up from mat

## Outcome

### Final Images

![alt text](https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint3/students/atinaika/files/final-sprint/Mat/MindfulMat.png)

<!-- <img src="https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint3/students/atinaika/files/final-sprint/Mat/MindfulMat.png"> -->

### Final circuit diagram

![alt text](https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint3/students/atinaika/files/Final-Circuit.jpg)

![alt text](https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint3/students/atinaika/files/fritzing-diagram.jpg)

### Interactions
The user first slides his or hand over the touch sensitive slider on the mat. The LEDs on the mat light up in response to the finger movement. Each LED represents a unit of time (viz. 10 mins. So 3 LEDs equate to a timer of 30 mins.)

A representation of the user's interaction with the touch sensor and the LED output is shown below.

<!-- <img src="https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint3/students/atinaika/files/final-sprint/Interactions/Interactions-collage.jpg" height="600"> -->
![alt text](https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint3/students/atinaika/files/final-sprint/Interactions/Interactions-collage.jpg)

Once the time is set, the user receives a vibratory notification at the feet and music from a playlist will start playing. Additionally  an SMS goes out to selected people informing them to not disturb the user for the meditation period.
If the user gets up from the mat, the timer and the music will pause. If they sit back on it, they (timer and music) will restart

Below is a demo of the product given at Demo Day:

https://youtu.be/3u5ix2Y5_8s

### Final Bill of Materials

|Sr. No.|Product Name|Qty|Specs|Cost / piece|Link|
|-------|------------|:-:|:---:|:----------:|:--:|
|1|Yoga Mats|1|Dimensions: 24" x 68" Weight: 2.4 lbs|$8.9|[Travel Yoga Mat (1mm)](https://www.yogaoutlet.com/p/sporti-studio-1mm-travel-yoga-mat-8132006/?utm_source=google&utm_medium=cpc&utm_campaign=google-shopping&color=36908&gclid=Cj0KEQjwqtjGBRD8yfi9h42H9YUBEiQAmki5OpnciI_w8VSi7583NAwe8MKHXEc0gunNXAE8INZCwhkaAprP8P8HAQ)|
|2|Square FSR|1|PRODUCT ID: 1075<br>Square FSR Interlink 406,Length: 88mm,Width: 43.7mm|$7.95|[Adafruit FSR](https://www.adafruit.com/products/1075)|
|3|DF Mini Player|2|Grove - GSR sensor,SKU 101020052,3.3V and 5V dual mode|$9.9|[Grove GSR Sensor](http://wiki.seeed.cc/Grove-GSR_Sensor/)|
|4|Piezo vibrator|1|PRODUCT ID: 1740<br>Max Rated Current: 3.0mA,Rated Voltage: 9V,External Diameter: 14mm|$0.95|[Piezo vibrator](https://www.adafruit.com/products/1740)|
|5|Stereo Amplifier|1|PRODUCT ID: 2341<br>Dimensions: 1.5" x 0.9”,16MB flash storage|$19.95|[Adafuit Class D Amplifier](https://www.adafruit.com/product/3006)|
|6|Neopixel strip|1|PRODUCT ID: 1426<br>NeoPixel stick - 8 x 5050 RGB LED with Integrated Driver Chip|$5.95|[Adafruit Neopixel strip](https://www.adafruit.com/products/1426)|
|7|Linear Touchpout|1|PRODUCT ID: 1071|$17.96|[SoftPot Membrane potentiometer](https://www.newegg.com/Product/Product.aspx?Item=9SIA53G23T6388&ignorebbr=1&nm_mc=KNC-GoogleMKP-PC&cm_mmc=KNC-GoogleMKP-PC-_-pla-_-EC+-+Passive+Components-_-9SIA53G23T6388&gclid=CjwKEAjw3drIBRCOwfC-_qqyjQ8SJADvoWQpX3owyQb-Rbt5OroAHUONnhaiJgGvJcYSyzKV1VMo0hoCjI3w_wcB&gclsrc=aw.ds)|
|8|AAA Batteries|4|AmazonBasics AAA Rechargeable Batteries|$3.99|[AmazonBasics Battery](https://www.amazon.com/AmazonBasics-AAA-Rechargeable-Batteries-12-Pack/dp/B007B9NXAC)|
|9|Resistors|2|1k ohm 1/2W resistor|$1.12|[Pack of 1k Ohm Resistors](https://www.amazon.com/1K-Ohm-Flameproof-Resistor-Pcs/dp/B000AYIQRA)|

## Product Review  

In the final sprint and especially over the last 7 weeks, a number of features were implemented and tested to make an average yoga mat more useful. Overall people found the product useful but expressed concerns about messages being sent out to people. Instead of push notifications, pull notifications (when people contact the person meditating) would be more useful.

While the fidelity of the prototype could have been higher, the conceptual model told the story of the product's usefulness. 

## Product Retrospective 

The building of the mat was a gruelling experience. Personally, deciding on the concept and what features to put and remove was one of the biggest challenges. There was a lot of back and forth which led me to reconsider my concept many times. Insights from users was useful and directly informed some of the decision making. If I had to go back, I would have finalised the feature list and tested it with user a lot earlier than I did do.

The engineering challenges were less demanding. However building a form for the mat and embedding components into the mat to make it seem seamless was hard. A yoga mat's fabric is unique and it required me to explore different types of fastening mechanisms (acrylic glue, epoxy glue, pins) to embed the sensors and actuators. I could have started with the form building a little prior to ensure I knew what I was working with and to achieve a better finish.


## Future Work

My long term vision is to create a connected yoga mat experience. While technology is trying to replace humans, I believe it is more powerful when it can connect people.

In the future, each yoga mat can be linked to a set of other mats, creating a connected classroom. There can be a master mat, which belongs to a teacher and slave mats which belong to students. The teacher could speak instructions into their mat, which would then be translated to the student's mat. This could solve a lot of problems currently faced by yoga practitioners (namely lack of time and ability to go to a yoga center as well as inability to find good content as a replacement to a teacher.)



