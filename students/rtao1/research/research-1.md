# Research Sprint 1

## Behaviour / Product Research

### Summary

I firstly did some research on tips and knowledge of growing plant at home. Then, based on different needs of monitoring plants, I looked up how to utilize different sensors to achieve the effects.

**[Automatic watering system for plants](http://www.instructables.com/id/Arduino-Automatic-Watering-System-For-Plants/)** -  using a 3V water pump and moisture sensor to make an automatic watering system

**[Automated window blinds](http://homeawesomation.com/2013/02/26/automated-window-blinds-with-arduino/)** - using a step motor and light sensor to make an automatic controlled window blinds

**[Parrot-pot](https://www.parrot.com/us/connected-garden/parrot-pot#parrot-pot)** - I checked this product to check if I missed any key functions

### Findings

##### 1. Notes for growing plant at home

The key and basic elements of growing a plant at home are **temperature, light, water, and fertilizer.** 

**Water:** Different types of plants require different amount of water and frequency of watering. Moisture sensor will check if water is needed in soil or the environment. Therefore, two ways to water the plant are needed, one is directly watering the soil, another is spraying the water to the air.

**Temperature:** Two types of temperature are required to be monitored, one is the soil temperature and the other is the ambient temperature. The soil temperature can be measured through a probe. As some plants may need warm environment, a heating method may be necessary.

**Light:** There are light-demanding plants, light neutral plants, and shade plants. Therefore, the quantity of illumination should be measured to guarantee the growth of the plant. If a shade plant is exposed under too much light, it may get hurt. Therefore, a blind like protection should be provided. 

**Fertilizer:** Fertilizer helps the plant to grow faster and healthy. It also helps adjust the PH of the soil. User can usually fertilze the plant based on time. A PH sensor can be used to monitor the soil PH and notification can be pushed to notify the user once it is the time or needed to fertilize. 

##### 2. Notes for watering

Spraying effect can be achieved by drill holes on a section of sealed tube. 3V submersible water pump can be used to drain and pump water from tank.

##### 3. Notes from Parrot-pot

Besides the functions and features that I have covered before, I noticed this device can monitor fertilizer level. Then I looked it up and found out that an **[EC meter](https://www.plantcaretools.com/measure-fertilization-with-ec-meters-for-plants-faq)** can achieve the function. However, as a customizable EC meter is around $70, I decided to push this feature for later integration.

### Relevance

The research helps me realize my concept and start the prototyping process. In this sprint, I will focus on the hardware such as the product prototype and sensors. Therefore, I will do a lot of DIY and research on mechanism to achieve functions. Through this research, I get many inspirations such as how to DIY blinds, water pump, etc.
