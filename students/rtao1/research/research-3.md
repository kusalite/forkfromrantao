# Research Sprint 3
## Connectivity and Preferences Research

_Prompt: Identify 3-5 opportunities around connectivity, networking or user preferences that would enhance your application and that you could potentially integrate_

### Summary

I want to find a way to pair my device since I hope the user to get access to the sensor and control the device remotely and conveniently. Although I have tried to make a controller which can visualize the values of the sensors, I somehow feel that it would be better if I can connect my device to a website or a web app. I looked into different ways to connect the Particle Photon to another platform.

### Findings
#### Webhook

The first one I looked into is the webhook. The way it works is to create a particle event and setup on cloud console.

![alt tag](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/research/webhooks-overview.png)

Through webhook, I could use a webhook to save valuable information in a database, visualize data being read from a sensor. I tried to connect it with thingspeak.com.

![alt tag](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/research/thingspeak-graph.png)

It is good for visualization, but thingspeak get update at least every 30 second. Therefore, it is not very ideal to me.

#### iPhone HomeKit

I have deeply looked into this plan. For detail introduction of this part, please see my [tutorial](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/tutorial/README.md). 

#### Website

For website connection, webhook is one possible way to achieve it. However, I can also deliver data and control sensor using JavaScript through Particle variable and Particle function. I found two detailed and nicely explained tutorial. 

- [Reading Spark Variables with Your Own HTML File](https://community.particle.io/t/reading-spark-variables-with-your-own-html-file/4148)
- [Spark Variable and Function on One Web Page](https://community.particle.io/t/tutorial-spark-variable-and-function-on-one-web-page/4181)

These two tutorials helped me a lot in creating a website that connects with my particle devices.

### Relevance

This expanded my vision in using Particle Photon, especially in designing and visioning in the future. It made me be able to achieve more possibilities and other cool functions, such as using Siri to control Particle.
