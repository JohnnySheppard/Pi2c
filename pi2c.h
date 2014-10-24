////////////////////////////////////////////////////////////////////////////////
// License:  This  program  is  free software; you can redistribute it and/or //
// modify  it  under the terms of the GNU General Public License as published //
// by  the  Free Software Foundation; either version 3 of the License, or (at //
// your  option)  any  later version. This program is distributed in the hope //
// that it will be useful, but WITHOUT ANY WARRANTY; without even the implied //
// warranty  of  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the //
// GNU General Public License for more details.                               //
////////////////////////////////////////////////////////////////////////////////
// pi2c.h: This is the header file for the Pi2c class which allows for easy   //
// communication to an Arduino from the Raspberry Pi over the I2C bus.        //
// The default usage is for a Raspberry Pi Rev 1 - using the I2C bus          //
// "/dev/i2c-1".  Rev0 and the "/dev/i2c-0" bus can be specfied though if     //
// needed.                                                                    //
////////////////////////////////////////////////////////////////////////////////
// Example Usage:                                                             //
// Please see https://bitbucket.org/JohnnySheppard/pi2c for example usage.    //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), */
#include <sys/ioctl.h>

class Pi2c {
		//Var to hold the i2c communications handle, 
		//...this will only be needed by the class itself, so it's private
		int i2cHandle_;
	public:
		//Function: Constructor - First parameter is the I2C address of the slave being talked to.
		//...Second parameter is optional. Set true if using a Rev0 Raspberry Pi.
		//...Returns: Nothing.
		Pi2c(int address, bool rev0 = false);
		
		//Function: Destructor - Closes the I2C File handle.
		//...Returns: Nothing.
		~Pi2c();
		
		//Function: i2cRead - First parameter is a pointer to a char array. This will also contain the 
		//...values passed back from the Arduino.
		//...Second parameter is the length of the array.
		//...Returns: Error value. > 0 is ok. < 0 means there was an error.
		int i2cRead(char *data,int length);
		
		//Function: i2cWrite - First parameter is a pointer to a char array.containing the data to send.
		//...Second parameter is the length of the array.
		//...Returns: Error value. > 0 is ok. < 0 means there was an error.
		int i2cWrite(char *data,int length);
		
		//Function: i2cWrite - No Parameters.
		//...Returns: An Int value sent from the arduino, or -1 if there was an error.
		int i2cReadArduinoInt();
		
		//Function: i2cWrite - First parameter the int to send to the array.
		//...Returns: Error value. > 0 is ok. < 0 means there was an error.
		int i2cWriteArduinoInt(int input);
};