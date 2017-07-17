void doEncoderA();
void doEncoderB();

int encoderA = D4;
int encoderB = D5;

volatile bool A_set = false;
volatile bool B_set = false;
volatile int encoderPos = 0;

int prevPos = 0;
int value = 0;
int prevTime = 0;

int countPerRound = 420;

void setup() {
  Serial.begin(9600);
  delay(1000);
  //Serial.println(encoderPos);
  pinMode(encoderA, INPUT_PULLUP);
  pinMode(encoderB, INPUT_PULLUP);
  attachInterrupt(encoderA, doEncoderA, CHANGE);
  //attachInterrupt(encoderB, doEncoderB, CHANGE);
}

void loop() {
    long lastPeriod = micros()-prevTime;
    float RPM = float(encoderPos - prevPos)/420/float(lastPeriod)*1000000*60;
    Serial.println(RPM);
    if (prevPos != encoderPos) {
        prevPos = encoderPos;
        //Serial.println(encoderPos);
    }
    prevTime = micros();
    delay(50);
}
//----------------------------------------------------------------

void doEncoderA(){
  if( digitalRead(encoderA) != A_set ) {  // debounce once more
    A_set = !A_set;
    // adjust counter + if A leads B
    if ( A_set != B_set )
      encoderPos += 1;
  }
}

/*// Interrupt on B changing state, same as A above
void doEncoderB(){
   if( digitalRead(encoderB) != B_set ) {
    B_set = !B_set;
    //  adjust counter - 1 if B leads A
    if( B_set != A_set )
      encoderPos -= 1;
  }
}*/
