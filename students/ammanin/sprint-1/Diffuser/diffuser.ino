 ////////////////////////////////////
//      ARTICULATE SMELL CODE     //
// this is part of an integrated  //
// system where a cookbook creates//
// an event that actuates a smell //
// on the photon with this code   //
//                                //
// Date: 5 March 2017             //
// Original Author: BZ            //
////////////////////////////////////

// Pin Variables
int smellPin1 = D0;

void setup()
{
  pinMode(smellPin1, OUTPUT);   //smell number 1 control pin
  //Particle.function("fan_time", change_fan_time);

}
//repeats
void loop()
{
      digitalWrite(smellPin1, HIGH); //turns smell 1 on the smell release
}
