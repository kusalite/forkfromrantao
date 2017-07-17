# Final Sprint

<img src="https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/final-sprint/Img/Final%20demo.jpg" alt="alt text">

### Sprint Catalog

- Write a website to access the values of the sensors and control water pump
- Finish physical prototypes such as assemble sensors and motors
- Test device and get feedback

### Outcome 

Finally, the website works pretty well, not only achieved all the purposed functions, but also stable and powerful. The only problem is that the liquid level sensor does not work normally (this sensor was bended before I borrowed from the lab). Also, the prototype leaks water although I have tried to use two hot glue sticks to seal it. But when I do the user tests, I managed to add some water to show the effect of the water pump and how to control it remotely.

The physical model contains three blocks - the plant block, the electronics block, and the water tank block. Everything fits well except the water leaking. I also connect the controller to the prototype to use as a on-device data displayer.

### Product Review  

The product works fine except the water tank and the liquid level sensor. As the liquid level sensor works just like the soil moisture sensor, it is not hard to add it to the website once I get a good one. Here are what the final prototpe can do:
- Monitor the environment temperature, humidity, light level , and soil moisture.
- Water the plant for 4 second once request is received.
- Show the values of the sensors through 10-segment LED bars and control the water pump via the controller.
- The website can display the values of the sensors and compare with the preset threshold so that it can tell the user if the environment is good for the plant and the plant is in good condition. The website will also teach user how to take care of this type of plant and introduce some related background knowledge. Moreover, the website allows user to write diary/story between the user and the plant, which will form a valuable experience and story to motivate user to keep going.

What I need to improve:
- The website can be more vivid, such as using comic and graphic to teach user the background information of growing the plant.
- The prototype should be clearer how to fit in multiple plants and how to be flexible when the user wants to change plants
- If possible, should also add more sensors such as PH sensor, and fertilizer sensor.
- The photo part of the diary function can be automated. Then, a camera should be added and took a photo every certain time.
- Should expand the website to be a database driven website by using PHP or other languages. Current version only support one plant.

### Circuit Diagram

<img src="https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/final-sprint/Img/botany%20box.jpg" alt="alt text">

Box Part

<img src="https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/final-sprint/Img/controller_bb.png" alt="alt text">

Controller Part

### Photos of Box and Controller

<img src="https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/final-sprint/Img/box%20photo.JPG" alt="alt text">

Box Photo

<img src="https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/final-sprint/Img/controller%20photo.jpg" alt="alt text">

Controller Photo

### Screenshots of Website

<img src="https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/final-sprint/Img/Website-1.png" alt="alt text">

<img src="https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/final-sprint/Img/Website-2.png" alt="alt text">

<img src="https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/final-sprint/Img/website-3.png" alt="alt text">

<img src="https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/final-sprint/Img/website-4.png" alt="alt text">

<img src="https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/final-sprint/Img/website-5.png" alt="alt text">

### Product Retrospective 

This project is a pretty intense project as I need to design, develop, and prototype it by myself. This is also the first time that I tried to do both of the hardware design and coding. The good thing is that this open project gave me very valuable chance to explore the world, webhook, Alexa, Siri, HomeKit, website, and so on. Although I have some areas that need to be improved, I have achieved many features and functions that I did not expect at the very beginning. I once stuck at the pairing part, where I tried Particle webhook, Alexa, Homebridge(Siri&Homekit), Ruby Sinatra based web app, PHP based data-driven website and JavaScript/HTML/CSS based website. I spent a ton of time exploring every possiblity. Although I still need to use PHP to further perfect the website, I am happy with what I have explored and achieved. The value of this course is not only making me explore the world of IoT, but also pushing me to realize my potential. I have gained a lot of experience in developing a prototype through Agile Development. In the future, I will use my knowledge to combine the Agile Development with design thinking, finding an efficient, flexible, and feasible thinking in developing product from the ground up.

### Future Work

- Learn PHP to build data-driven website
- Explore the combination of Agile development with design thinking.

### Some Experience to Share
- [How to access the values of the sensors and control parts through HTML/CSS/JS based website](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/research/research-3.md)
- [How to use Homebridge to show your sensors in HomeKit](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/tutorial/README.md)
- [How to wire and use LM3914 with 10-segment LED bar](https://learn.sparkfun.com/tutorials/dotbar-display-driver-hookup-guide)
- [How to use LM3914 with Particle Photon analog output - Low Pass Filter](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/research/research-2.md)

For more questions about this project, please do not hesitate to leave a message.




