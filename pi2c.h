////////////////////////////////////////////////////////////////////////////////
// License:  This  program  is  free software; you can redistribute it and/or //
// modify  it  under the terms of the GNU General Public License as published //
// by  the  Free Software Foundation; either version 3 of the License, or (at //
// your  option)  any  later version. This program is distributed in the hope //
// that it will be useful, but WITHOUT ANY WARRANTY; without even the implied //
// warranty  of  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the //
// GNU General Public License for more details.                               //
////////////////////////////////////////////////////////////////////////////////
// pi2c.h: This is the header file for the pi2c class which allows for easy   //
// communication to an Arduino from the Raspberry Pi over the I2C bus.        //
// The default usage is for a Raspberry Pi Rev 1 - using the I2C bus          //
// "/dev/i2c-1".  Rev0 and the "/dev/i2c-0" bus can be specfied though if     //
// needed.                                                                    //
////////////////////////////////////////////////////////////////////////////////
// Example Usage:                                                             //
// #include "pi2c.h"                                                          //
//                                                                            //
// int main(){                                                                //
//     pi2c arduino(7); //Create a new object "arduino" using address "0x07"  //
//     char receive[16]; //Create a buffer of char (single bytes) for the data//
//                                                                            //
//     //Print out what the Arduino is sending...                             //
//	   arduino.i2cRead(receive,16);                                           //
//     std::cout << "Arduino Says: " << receive << std::endl;                 //
//                                                                            //
//     //Send an 16 bit integer                                               //
//     arduino.i2cWriteArduinoInt(4356);                                      //
//                                                                            //
//     return 0;                                                              //
// }                                                                          //
////////////////////////////////////////////////////////////////////////////////
//Example Arduino Program:                                                    //
// #include <Wire.h>                                                          //
//                                                                            //
// void setup() {                                                             //
//   Serial.begin(9600);// open the serial port at 9600 bps:                  //
//   Wire.begin(0x07); //Set Arduino up as an I2C slave at address 0x07       //
//   Wire.onRequest(requestEvent); //Prepare to send data                     //
//   Wire.onReceive(receiveEvent); //Prepare to recieve data                  //
// }                                                                          //
//                                                                            //
// void loop() {                                                              //
// }                                                                          //
//                                                                            //
// void requestEvent()                                                        //
// {                                                                          //
//   unsigned char char_ar[16] = "Hi Raspberry Pi"; //Create String           //
//   Wire.write(char_ar,16); //Write String to Pi.                            //
// }                                                                          //
//                                                                            //
// void receiveEvent(int numBytes){                                           //
//   //Set Up Vars                                                            //
//   int receive_int=0;                                                       //
//   int count=0;                                                             //
//                                                                            //  
//   //We'll recieve one byte at a time. Stop when none left                  //
//   while(Wire.available())                                                  //
//   {                                                                        //
//     char c = Wire.read();    // receive a byte as character                //
// 	   //Create Int from the Byte Array                                       //
//     receive_int = c << (8 * count) | receive_int;                          //
//     count++;                                                               //
//   }                                                                        //
//   //Print the Int out.                                                     //
//   Serial.print("Received Number: ");                                       //
//   Serial.println(receive_int);                                             //
// }                                                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), */
#include <sys/ioctl.h>

class pi2c {
		int i2cHandle;
	public:
		pi2c(int address, bool rev0 = false);
		int i2cRead(char*,int);
		int i2cWrite(char*,int);
		int i2cReadArduinoInt();
		int i2cWriteArduinoInt(int);
};