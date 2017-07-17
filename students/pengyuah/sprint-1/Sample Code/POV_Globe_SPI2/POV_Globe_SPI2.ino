/////////////////////////////////////////////////////////////////
// POV Globe
// Ulli Schmerold
// 8/2016
// implemented with Serial Peripheral Interface (SPI)
/////////////////////////////////////////////////////////////////

 // SPI Pins Arduino Nano: 10 (SS), 11 (MOSI), 12 (MISO), 13 (SCK).
 // DATA_IN 12  ==> not used
 #define DATA_PIN  11
 #define CLOCK_PIN 13
 #define LATCH_PIN 10
 #define Hall_PIN 2

 long circulation_time;   // Time of one circulation as processor cycles
 byte segment_time;       // Length of one segment as processor cycles
 int current_segment=0;   // The curent segment
 int rotation = 0;        // Count the rotations (for slower image rotation)
 int actual_position=0;   // The actual position of the image
 boolean update=false;    // To start the data transmission

 // The data for the Globe are produced with the programm POV Globe Calculator
 // and stored in a two dimensional array
 // Each number (byte) drives 8 LEDs
byte registers = 4;    // Number of registers
byte segments = 140;   // Number of segments per rotation
byte byte_register [4][140] = {
 {0 , 3 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 7 , 7 , 7 , 7 , 7 , 7 , 3 , 3 , 3 , 3 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 32 , 96 , 96 , 112 , 124 , 126 , 255 , 255 , 255 , 255 , 124 , 120 , 56 , 56 , 16 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 3 , 3 , 3 , 7 , 6 , 12 , 8 , 14 , 14 , 15 , 15 , 11 , 11 , 11 , 3 , 3 , 7 , 7 , 7 , 7 , 7 , 7 , 15 , 15 , 15 , 31 , 15 , 7 , 15 , 15 , 15 , 31 , 31 , 63 , 63 , 63 , 63 , 63 , 127 , 127 , 127 , 63 , 31 , 31 , 31 , 31 , 31 , 31 , 15 , 15 , 15 , 15 , 15 , 15 , 30 , 30 , 30 , 30 , 14 , 14 , 13 , 13 , 12 , 14 , 14 , 14 , 14 , 12 , 12 , 12 , 12 , 4 , 0 , 0},
 {0 , 0 , 128 , 128 , 128 , 128 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 128 , 128 , 128 , 192 , 192 , 224 , 252 , 252 , 252 , 254 , 254 , 255 , 255 , 255 , 255 , 255 , 254 , 126 , 126 , 62 , 62 , 62 , 28 , 24 , 248 , 248 , 240 , 96 , 96 , 96 , 32 , 32 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 3 , 3 , 23 , 31 , 151 , 183 , 111 , 111 , 111 , 239 , 119 , 103 , 103 , 99 , 247 , 247 , 227 , 243 , 243 , 209 , 236 , 254 , 254 , 255 , 255 , 203 , 237 , 253 , 253 , 252 , 254 , 254 , 254 , 254 , 255 , 255 , 255 , 255 , 255 , 254 , 254 , 254 , 254 , 255 , 255 , 255 , 255 , 254 , 254 , 254 , 254 , 254 , 246 , 240 , 240 , 240 , 240 , 224 , 224 , 96 , 64 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 128 , 128 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0},
 {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 128 , 192 , 192 , 64 , 64 , 64 , 96 , 32 , 38 , 30 , 31 , 31 , 31 , 31 , 31 , 15 , 15 , 15 , 15 , 7 , 7 , 7 , 3 , 3 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 128 , 192 , 192 , 192 , 192 , 192 , 192 , 192 , 192 , 192 , 224 , 240 , 254 , 255 , 255 , 255 , 255 , 255 , 255 , 255 , 252 , 252 , 240 , 96 , 225 , 67 , 4 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 128 , 192 , 192 , 32 , 0 , 0 , 0 , 0 , 0 , 0 , 128 , 128 , 128 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 3 , 3 , 3 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0},
 {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 14 , 191 , 255 , 248 , 240 , 240 , 240 , 224 , 224 , 192 , 128 , 128 , 128 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 128 , 128 , 128 , 128 , 128 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 128 , 224 , 224 , 224 , 192 , 192 , 192 , 192 , 192 , 192 , 224 , 240 , 240 , 240 , 224 , 192 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0}
};


void setup() {
 pinMode(LATCH_PIN,OUTPUT);       // LATCH_PIN (pin 12 of  74HC595) 
 pinMode(DATA_PIN,OUTPUT);        // DATA_PIN  (pin 14 of  74HC595)
 pinMode(CLOCK_PIN,OUTPUT);       // CLOCK_PIN (pin 11 of  74HC595)
 pinMode(Hall_PIN,INPUT_PULLUP);  // internal PULUP for the hallsensor-pin
 
 setup_hardware_spi();            // SPI configuration
 configure_interrupts();          // Interrupt configuration
}

void loop() {
  if (update==true)
  {
    update=false;
    if (current_segment++ >= (segments-1)) current_segment = 0; // for turning the POV-image
    next_element(current_segment);
  } 
}



void next_element(int Element){  
    digitalWrite(LATCH_PIN, LOW); //to start the data transmision we set the latchPin  LOW
    for (int i=0 ; i < registers ; i++)
      spi_shiftOut(byte_register[i][Element]); //now we are transmitting the data to 74HC595
    digitalWrite(LATCH_PIN, HIGH); // at least we set the latchPin  HIGH
}


//----------------------------------------------------------------
//                           Interrupts
//----------------------------------------------------------------

// macro to set bits
#define bitset(var,bitno) ((var) |= (1 << (bitno)))

// configure timer und interrupts 
void configure_interrupts(void)
{
  cli();    // disable interrupts

  //  timer0 - (8 bit timer)
  //  for timing the LED's
  TCCR0A = 0;
  TCCR0B = 0;  
  bitset(TCCR0A, WGM01);   // CTC mode
  bitset(TCCR0B, CS01);    // prescaler clk / 64
  bitset(TCCR0B, CS00);    // prescaler clk / 64
  bitset(TIMSK0, OCIE0A);  // compare interrupt

  //  timer1 - (16 bit timer)
  //  to get the processor cycles for one turn of the POV globe
  TCCR1B = 0;
  TCCR1A = 0;
  bitset(TCCR1B, CS11);   // prescaler clk / 64
  bitset(TCCR1B, CS10);   // prescaler clk / 64 
  bitset(TIMSK1, TOIE1);  // overflow interrupt

  // configure the hallsensor pin (Arduino Pin 2)
  EICRA = _BV(ISC01);    // Interrupt is triggered by falling edge
  EIMSK |= _BV(INT0);    // enable hardware interrupt 

  sei();  // enable all interrupts 
}


// This interrupt is triggert from each rotation
// Here both timers are set to 0
ISR(INT0_vect)
{
  // How many processor cycles have been passed since the last round?
  segment_time=(TCNT1 / segments);
  // To ensure a smoother image
  // the interval for Timer 0 for every tiny speed deviation
  // Dadurch wird der Globus ruhiger
  if ( ((OCR0A-segment_time)>1) || ((segment_time-OCR0A)>2)) OCR0A=segment_time;
  

  // set 16 bit Timer to 0  (timer1)
  TCNT1 = 0;
  // set 8 bit Timer to 0  (timer0) 
  TCNT0 = 0;
  
  // after 3 rotations move one sector (to rotate the image)
  if (rotation++ >=3)
  {
      rotation=0;
      if (actual_position-- <=0) actual_position = segments-1; // Clockwise rotation    
    }  
  current_segment=actual_position;
  update=true; 

}


// This interrupt is triggered by timer0
// The timer interval is calculated after each triggering of the hallsensor
// and set to the OCROA - register 
ISR(TIMER0_COMPA_vect) {
  // start the SPA data transmision
   update=true;
}







