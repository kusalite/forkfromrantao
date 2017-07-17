# Tutorial - Connect your Particle with HomeKit ![Alt text](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/tutorial/img/home_icon_large_2x.png)

Ran Tao

HomeKit is Apple’s proprietary software and hardware smart-home platform, letting you control many of the most popular smart-home devices, including lights, switches, door locks, and thermostats. HomeKit devices link up to each other with relatively little effort and can be controlled not only via an app but also with your voice via Apple’s virtual assistant, Siri.

![Alt text](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/tutorial/img/hero_lockup_large_2x.png)

It will be very cool if we can connect our device with HomeKit and use it to control our IoT devices. How can we do that?

## Introducing the Homebridge

Homebridge is a lightweight NodeJS server you can run on your home network that emulates the iOS HomeKit API. It supports Plugins, which are community-contributed modules that provide a basic bridge from HomeKit to various 3rd-party APIs provided by manufacturers of "smart home" devices.

Homebridge is published through NPM and should be installed "globally" by typing:
````
sudo npm install -g --unsafe-perm homebridge
````
After that, you can run the homebridge by typing:
````
$ homebridge
````
You will then see a result: 
````
"No plugins found. See the README for information on installing plugins." 
````
This is because you have no plugin installed. Let's see how to install the homebridge-particle plugin.

## Install Homebridge-Particle Plugin
To install homebridge-particle plugin, you can simply run the following code:
````
npm install -g homebridge-particle
````
However, you cannot use it untill you crease a `config.json` file in your `.homebridge` folder, which is inside of your home folder. To see the `.homebridge` folder which is a hidden folder, go to your home folder and press `Command + Shift + .`. You can create a `config.json` file using tools such as Sublime Text or Brackets.

## Write Your Config.json File
Homebridge supports 2 types of shims, **accessory** and **platforms**. Accessory is a single or multiple accessory device. Platform a bridge to another system. In HAP-Node-JS each accessory has require characteristics which must be implemented by the accessory and some optional characteristics.

Therefore, you need to configure the characteristics of the sensors you use in the .json file. A sample file can be like:
````JSON
{
    "bridge": {
        "name": "Homebridge",
        "username": "CC:22:3D:E3:CE:30",
        "port": 51826,
        "pin": "031-45-154"
    },
    "description": "This is an example configuration file with one Particle platform and 3 accessories, two lights and a temperature sensor. You should replace the access token and device id placeholder with your access token and device id",

    "platforms": [
        {
            "platform": "Particle",
            "name": "Particle Devices",
			"access_token": "<<access token>>",
			"cloudurl": "https://api.spark.io/v1/devices/",
			"devices": [
				{
					"accessory": "BedroomLight",
					"name": "Bedroom Light",
				    "deviceid": "<<device id>>",
					"type": "LIGHT",
					"function_name": "onoff",
					"args": "0={STATE}"
				},
				{
					"accessory": "KitchenLight",
					"name": "Kitchen Light",
					"deviceid": "<<device id>>",
					"type": "LIGHT",
					"function_name": "onoff",
					"args": "1={STATE}"
				},
				{
					"accessory": "KitchenTemperature",
					"name": "Kitchen Temperature",
					"deviceid": "<<device id>>",
					"type": "SENSOR",
					"sensorType": "temperature",
					"key": "temperature",
					"event_name": "tvalue"
				}
			]
        }
    ]
}
````
As you can see from the above example this `config.json` file defines 3 accessories. 2 Lights and one Temperature Sensor. The `access_token` defines the Particle Access Token and `cloudurl` defines the base Particle API url. If you are using the Particle Cloud, then the value of cloudurl should be `https://api.spark.io/v1/devices/`. If you are using local cloud, then replace with your sensor address.

The `devices` array contains all the accessories. You can see the accessory object defines following string objects:
* **accessory** - Accessory name, this is the name of the accessory.
* **name** - Display name, this is the name to be displayed on the HomeKit app.
* **deviceid** - Device ID of the Particle Device (Core, Photon or Electron). It is defined in accessory so that you can use different Particle Devices for different accessory.
* **type** - Type of the accessoy. As of now, the plugin supports 2 type, LIGHT and SENSOR. Type LIGHT represents a light, such as bedroom light, kitchen light, living room light, etc... Type SENSOR represents sensor accessory such as Temperature sensor, Humidity sensor, Light sensor, etc...
* **sensorType** - Optional Sensor Type, this string object is optional. This is only valid when the accessory type is SENSOR. As of now the plugin supports 3 types of sensors, Temperature Sensor, Humidity Sensor and Light Sensor. More sensor will be supports in future versions.
* **event_name** - The name of the event to listen for sensor value update. This is only valid if the accessory type is SENSOR. If the accessory is a type of SENSOR, then the plugin listens for events published from Particle Device (using Particle.publish). The device firmware should publish the sensor values in the format key=value. The key identifies the sensor value. For a temperature sensor the key should be temperature. For a humidity sensor the key should be humidity. For light sensor it should be light.
* **key** - Name of the key, this is not used in this version of the plugin. This is included for future purpose.

## Adding Homebridge to iOS
HomeKit itself is actually not an app; it's a "database" similar to HealthKit and PassKit. Where HealthKit has the companion Health app and PassKit has Passbook, HomeKit has the Home app, introduced with iOS 10.

Using the Home app (or most other HomeKit apps), you should be able to add the single accessory "Homebridge", assuming that you're still running Homebridge and you're on the **same Wifi network**. Adding this accessory will automatically add all accessories and platforms defined in `config.json`.

It should look like this:

![Alt text](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/tutorial/img/Terminal%20Screenshot.png)

When you attempt to add Homebridge, it will ask for a "PIN code". The default code is 031-45-154 (but this can be changed in `config.json`).

![Alt text](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/tutorial/img/pair%20device.PNG) ![Alt text](https://github.com/daraghbyrne/advancediot2017/blob/master/students/rtao1/tutorial/img/added.PNG)

## Common Issues
##### My iOS App Can't Find Homebridge
Two reasons may cause this problem:
1. Homebridge server thinks it's been paired with, but iOS thinks otherwise. Fix: deleted `persist` directory which is next to your `config.json`.
2. iOS device has gotten your Homebridge `username` (looks like a MAC address) "stuck" somehow, where it's in the database but inactive. Fix: change your `username` in the "bridge" section of `config.json` to be some new value.
##### Errors on Startup
The following errors are experienced when starting Homebridge and can be safely ignored. The cost of removing the issue at the core of the errors isn't worth the effort.
````
*** WARNING *** The program 'nodejs' uses the Apple Bonjour compatibility layer of Avahi
*** WARNING *** Please fix your application to use the native API of Avahi!
*** WARNING *** For more information see http://0pointerde/avahi-compat?s=libdns_sd&e=nodejs
*** WARNING *** The program 'nodejs' called 'DNSServiceRegister()' which is not supported (or only supported partially) in the Apple Bonjour compatibility layer of Avahi
*** WARNING *** Please fix your application to use the native API of Avahi!
*** WARNING *** For more information see http://0pointerde/avahi-compat?s=libdns_sd&e=nodejs&f=DNSServiceRegister
````
## Firmware Code for Particle Photon
Here is an example of using a DHT22 Temperature and Humidity sensor.
````C
#include "DHT.h"
#define DHTPIN          D3
#define DHTTYPE         DHT22

// DHT Object
DHT dht(DHTPIN, DHTTYPE);
// Temperature
float currentTemperature;
// Humidity
float currentHumidity;

void setup() {
    // Begin Serial
    Serial.begin(9600);
    pinMode(A5, OUTPUT);
    // Initialize DHT
    dht.begin();
}

void loop() {
    currentTemperature = dht.readTemperature();
    currentHumidity = dht.readHumidity();
    Particle.publish("Temperature", currentTemperature);
    delay(5000);
    Particle.publish("Humidity", currentHumidity);
    delay(5000);
}
````
To control a LED light, simply use `Particle.function` to expose internal functions as cloud API.

## Siri

All HomeKit devices can be managed by Siri without any additional configuration. Here is a demo of using Siri to control a LED that is connected with Particle Photon.

[![video](https://www.dropbox.com/s/wfb5unfd5a8fkt8/vimeo.png?dl=1)](http://vimeo.com/nikitaleonov/siri-homekit-particle "video")

## Further Development

As you can see, only limited types of sensors are currently supported. If you want to further dig into it, you can start adding things in this [index.js](https://github.com/krvarma/homebridge-particle/blob/master/index.js) and push to npmjs.com to test it.

If you want to further contribute to homebridge or simply write other plugins, you can find the source codes and tutorials [here](https://github.com/nfarina/homebridge).

## References
https://github.com/krvarma/homebridge-particle

https://github.com/nfarina/homebridge

https://www.hackster.io/krvarma/homekit-and-particle-photon-e59cac

https://github.com/nikita-leonov/particleio-homekit
