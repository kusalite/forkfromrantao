#include <google-maps-device-locator.h>

GoogleMapsDeviceLocator locator;

float latitude;
float longitude;

void setup() {
  Serial.begin(9600);

  // Option 1: Periodically scan for a location...
  // Scan for visible networks and publish to the cloud every 30 seconds
  // Pass the returned location to be handled by the locationCallback() method
  // You can do this however often you like.
  //locator.withSubscribe(locationCallback).withLocatePeriodic(30);

  // Option 2: Scan once at startup

  locator.withSubscribe(locationCallback).withLocateOnce();

  //locator.withLocatePeriodic(120);


}

void loop() {
  //With periodic and locate once modes, you must call
  locator.loop();

}


void locationCallback(float lat, float lon, float accuracy) {
  // Handle the returned location data for the device. This method is passed three arguments:
  // - Latitude
  // - Longitude
  // - Accuracy of estimated location (in meters)

  latitude = lat;
  longitude = lon;

  Serial.print( "lat: " );
  Serial.print( lat );
  Serial.print( "\tlon:");
  Serial.print( lon );
  Serial.print( "\taccuracy:" );
  Serial.print( accuracy );
}
