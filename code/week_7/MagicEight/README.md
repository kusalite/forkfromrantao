# An Interactive Magic 8-Ball

This tutorial explores putting all of the pieces together. It incorporates sensor smoothing, calibration, API and data access, interactivity, states, behavior and an interface with a web interface to create an interactive customizable shake-to-select zero-UI [Magic Eight Ball](http://www.retroland.com/magic-8-ball/). Fun!

All of the code for the example including web hook templates can be found in this folder. 

It pulls data from this [spreadsheet](https://docs.google.com/spreadsheets/d/1TgbQRTXTUFpo0YPES0bFOt2D88zkdcKl8W5xSF2mcFw/edit#gid=1207899445)

### Working with EEPROM Memory

> "The EEPROM functions can be used to store small amounts of data in Flash that will persist even after the device resets after a deep sleep or is powered off."

EEMPROM is incredibly useful. You can use it to store user preferences, device settings, customisations, small chunks of data retrieved from web-services and lots of stuff that can be immediately restored and accessed when you power on the device again. 

A really useful and simple example: You have a servo. It spins and spins. When the device is on you know how many rotations it's made and can track this. When you power it off, that information is lost. That means you need to calibrate it or reset it each time. Imagine if it could remember what position it was last at, and use that when you restart the device and pick up from where you left off. This is where EEPROM comes in super useful.

The two main functions to know are: 

````
// This function will write an object to the EEPROM. 
// You can write single values like int and float 
// or group multiple values together using struct.

EEPROM.put(int address, object)

// This function will retrieve an object from the EEPROM. 
// Use the same type of object you used in the put call.

EEPROM.get(int address, object)
````

The main thing to know is that memory is limited. You can't store everything. You've only got 2047 bytes. This isn't even a full page of text so you've got to be selective about what you keep in memory. Always use simpler variable types if you can. uint8_t takes less memory to store than just a plain old int.  

Structs are incredibly useful too. They are written as an entire object and you only need to know the beginning address to access it. It handles the rest of putting the object into memory and getting it back out again. 

````
int eeprom_address = 10;
struct MagicEightSettings {
  uint8_t version;
  int waitTimeFromShake;
  char last_selection [256];
  char sheet_name[256];
};

MagicEightSettings settings; // stores the main settings
````

Read more about [EEPROM in the Particle Docs](https://docs.particle.io/reference/firmware/photon/#eeprom)


###  Working with WebHooks 

> Webhooks are a simple and flexible way for your devices to make requests to almost anything on the Internet. Webhooks listen for events from your devices. When you send a matching event, the hook will send a request to your web application with all the details!

**What is an API (or a web request)?** - first take a look at these [two](http://www.programmableweb.com/wp-content/api_infographic_smartfile.jpg) [infographics](http://www.getelastic.com/wp-content/uploads/api-infographic-full.jpg)

A webhook manages web requests. Web Requests are made to an API and an API provides structured access to online data. They are behind most online applications and services like Twitter, Flickr, etc. etc. You make your request by calling a URL, and providing parameters to that web request (like in a web browser). The server will then respond with some data normally in either [XML](http://www.w3.org/XML/) or [JSON](http://www.json.org) formats. This is passed back the client that made the request and then you can process it to extract the information you're interested in. 

In the case of the Particle framework the process has an extra middleman. Particle's cloud services help store, manage and make each web request for you. The process for a webhook is like this:

- First, you create and define a webhook. You setup a template in JSON which gives information on what URL (web link) it's going to call, how you want to make the request (GET, POST, etc) and what parameters you want to pass. Once you've set up a template, you give it a name and tell the Particle Cloud that you want your devices to access it. Then the template is stored on the Cloud (a remote server) and can be triggered using an event on your Device. 
- Next when you want to trigger your webhook, you simply use <code>Particle.publish('my_webhook_name')</code> anywhere in your program. Your webhooks are available to all your devices too. 
- The webhook will trigger, call a web request, gather some data and pass it back to your Photon. It also sends this information back as an event. The event will be named "hook-response/my_webhook_name". To [handle this response](https://docs.particle.io/guide/tools-and-features/webhooks/#handling-web-responses), you just subscribe to this event in your setup! Note that lots of other people could have a web request with the same name so make sure to subscribe to events only from "MY_DEVICES"

##### Creating a Webhook Template

There's two ways to create a webhook. 

1. Uou can do it [through the CLI](https://docs.particle.io/guide/tools-and-features/webhooks/#cli-command-reference) which gives you three commands to manage webhooks 

````
    particle webhook create - Creates a postback to the given url when your event is sent
    particle webhook list - Show your current Webhooks
    particle webhook delete - Deletes a Webhook
````

2. You can also use the [online IDE's Integration](https://dashboard.particle.io/user/integrations) option to create and delete webhooks

##### Responses and Response Templates

Events have limits. You can only get 512 bytes of data back from an event. This means that we can only get 512 characters back from a web-hook. More complex web-requests tend to give lots more data than this. 

There's two ways [we can handle this](https://docs.particle.io/guide/tools-and-features/webhooks/#handling-web-responses).

First, the will chunk the data into a series of events (e.g. hook-response/get_weather/0, hook-response/get_weather/1, hook-response/get_weather/2, etc.). In these the website responses are cut into chunks of 512 bytes and they're sent at a rate of up to 4 per second. But, this will only return the first 100KB of the request will be sent, and the rest will be dropped.

The other way we can deal with the response is to use the server side processing of Particle to filter the data to only what we really need before it's sent to the device as an event. This is where [response templates](https://docs.particle.io/guide/tools-and-features/webhooks/#responsetemplate) come in.


##### Limits

1. You can create up to 20 webhooks, you can send 10 hooks per minute per device.

2. The hook will be disabled if the server responds with errors 10 times in a row.

3. Any host will be limited to 120 requests per minute unless Particle are contacted by the site administrator.

Read [more about Webooks](https://docs.particle.io/guide/tools-and-features/webhooks/#introduction) 


##### In our example

We create a webhook to get Data from Google Spreadsheets. You can read more about doing that here:  [https://ctrlq.org/code/20004-google-spreadsheets-json](https://ctrlq.org/code/20004-google-spreadsheets-json)

##### More control

If you want more control over the web-request you can always manage it yourself. 

The [RestClient](https://github.com/llad/spark-restclient) Library let's you easily make your own calls to HTTP-based (not HTTPS) APIs. 

You can also use the in-built [TCPClient library](https://docs.particle.io/reference/firmware/photon/#tcpclient) to make your own calls to almost anything on the internet. 

##### Useful Tools

- [JSON Pretty Print](http://jsonprettyprint.com) lets you take an ugly JSON string and quickly format it into something much more human readable

- A good text editor. I recommend [TextMate](https://macromates.com)

###  Working with Web Applications

You can wire up a Particle device to an online webpage or even mobile application in a matter of minutes. That's the beauty of the Particle.variable, Particle.function and Particle.publish methods. They can be accessed by anything on the internet through a standard URL by who knows where they are and have the credentials to do that (an access token!)

Creating a web app connected to your device is quick and easy. Just add jquery to your HTML content and then

##### Settings

You need the 

- device ID of the Photon you want to control

- your personal access token (which can be found at [particle.io/build](http://particle.io/build) under Settings)


##### To call a Particle.function and control your device

Create a function in JQuery for the Particle.function URL _Note you need to have a variable created called deviceID and accessToken!_

````
function callParticleFunction( value ) {
  var requestURL = "https://api.particle.io/v1/devices/" +deviceID + "/functionname/";
	$.post( requestURL, { params: value, access_token: accessToken });
}
````

Then trigger it based on some activity, in this case a button push

````
	$( "#myButton" ).on('click', function(){
	    callParticleFunction( "data to pass" );
	});
````

##### To listen for an event

You can also listen for an event in just a few lines of code.

````
    var source = new EventSource("https://api.particle.io/v1/events?access_token=" + accessToken );
    if (typeof(EventSource) !== "undefined") {
        console.log("SSE is Supported!");
    } else {
        console.log("SSE is NOT Supported");
    }
    console.log("Done");
    source.addEventListener('my_event_name', function (e) {
        var obj = jQuery.parseJSON(e.data);
        console.log(obj.data +  " - " + obj.published_at );
    }, false);
	
````	


##### Useful Tools

- [Zurb Foundation](http://foundation.zurb.com/) is a great responsive HTML framework which gives you a tonne of components that you can use to quickly prototype an interactive web application

- [Ionic](http://ionicframework.com) is a HTML based framework for creating native iOS and Android applications

- [Adobe's PhoneGap](https://build.phonegap.com) let's you convert any HTML-based web content to a native mobile application in a matter of minutes. 


##### Code Improvements

Randomisation could also be sequential removal (i.e. draw from a hat, not wholly random)

- https://gist.github.com/wandrson/9816376
- http://playground.arduino.cc/Main/RandomHat



