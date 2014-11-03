# Pi2c #

Pi2c is a C++ is a class which allows for easy communication to an Arduino from the Raspberry Pi over the I2C bus.

**Version:** 1

## Compiling ##

Pi2c is already compiled for Raspbian running on the Raspberry Pi. If you want to compile it for another system, you just need to run:

```console

g++ -c pi2c.cpp
```
You may find you need to install **i2c-tools** in order for it to compile and it's a useful set of tools to have anyway in order help with problems on the I2C Bus.

## Using Pi2c ##

In order to use this on a Raspberry Pi running Raspbian, you just need to copy **pi2c.h** and **pi2c.o** into your project and then include the header in your program. You then need to add the object to your compile command. eg.
```console

g++ pi2c.o test.cpp -o test
```

###Example Usage###

Example C++ file:
```c++


#include "pi2c.h"

int main(){
    Pi2c arduino(7); //Create a new object "arduino" using address "0x07"
    char receive[16]; //Create a buffer of char (single bytes) for the data

    //Receive from the Arduino and put the contents into the "receive" char array
    arduino.i2cRead(receive,16);
     //Print out what the Arduino is sending...
    std::cout << "Arduino Says: " << receive << std::endl;

    //Send an 16 bit integer
    arduino.i2cWriteArduinoInt(4356);

    return 0;
}
```

Example Arduino file:

```c++

#include <Wire.h>

void setup() {
  Serial.begin(9600);// open the serial port at 9600 bps:
  Wire.begin(0x07); //Set Arduino up as an I2C slave at address 0x07
  Wire.onRequest(requestEvent); //Prepare to send data
  Wire.onReceive(receiveEvent); //Prepare to recieve data
}

void loop() {
}

void requestEvent()
{
  unsigned char char_ar[16] = "Hi Raspberry Pi"; //Create String
  Wire.write(char_ar,16); //Write String to Pi.
}

void receiveEvent(int numBytes){
  //Set Up Vars
  int receive_int=0;
  int count=0;

  //We'll recieve one byte at a time. Stop when none left
  while(Wire.available())
  {
    char c = Wire.read();    // receive a byte as character
    //Create Int from the Byte Array
    receive_int = c << (8 * count) | receive_int;
    count++;
  }
  //Print the Int out.
  Serial.print("Received Number: "); 
  Serial.println(receive_int);
}
```