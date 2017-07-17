

Basics of Code

// boolean
boolean state;      // an boolean named ledPin

// integers
int ledPin;      // an integer named ledPin
int val;              // an integer named val

// double
double decimal;      // an double named …

// char
char aSingleCharacter; 

// String
String text; 

Arrays... 

int myInts[6];
int myPins[] = {2, 4, 8, 3, 6};
int mySensVals[6] = {2, 4, -8, 3, 2};
char message[6] = "hello";

int myArray[10]={9,3,2,4,3,2,7,8,9,11};
// myArray[9]    contains 11
// myArray[10]   is invalid and contains random information (other memory address)    


To assign a value to an array:

mySensVals[0] = 10;
To retrieve a value from an array:

x = mySensVals[4];

Arrays and FOR Loops

Arrays are often manipulated inside for loops, where the loop counter is used as the index for each array element. For example, to print the elements of an array over the serial port, you could do something like this:

int i;
for (i = 0; i < 5; i = i + 1) {
  Serial.println(myPins[i]);
}