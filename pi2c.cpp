////////////////////////////////////////////////////////////////////////////////
// License:  This  program  is  free software; you can redistribute it and/or //
// modify  it  under the terms of the GNU General Public License as published //
// by  the  Free Software Foundation; either version 3 of the License, or (at //
// your  option)  any  later version. This program is distributed in the hope //
// that it will be useful, but WITHOUT ANY WARRANTY; without even the implied //
// warranty  of  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the //
// GNU General Public License for more details.                               //
////////////////////////////////////////////////////////////////////////////////
// pi2c.cpp:
//////////////////////////////////////////////////////////////////////////////// 
#include "pi2c.h"

Pi2c::Pi2c(int address, bool rev0){
	//Set up the filename of the I2C Bus. Choose appropriate bus for Raspberry Pi Rev.
	char filename[11] = "/dev/i2c-";
	if (rev0 == true){
		filename[9] = '0';
	}
	else {
		filename[9] = '1';
	}
	filename[10] = 0; //Add the null character onto the end of the array to make it a string
	
	i2cHandle_ = open(filename, O_RDWR); //Open the i2c file descriptor in read/write mode
	if (i2cHandle_ < 0) {
		std::cout << "Can't open I2C BUS" << std::endl; //If there's an error opening this, then display it.
	}
	if (ioctl(i2cHandle_, I2C_SLAVE, address) < 0) { //Using ioctl set the i2c device to talk to address in the "addr" variable.
		std::cout << "Can't set the I2C address for the slave device" << std::endl; //Display error setting the address for the slave.
	}
}

Pi2c::~Pi2c(){
	if (i2cHandle_){ //If the I2C File handle is still open...
		close(i2cHandle_); //...Close it.
	}
}

int Pi2c::i2cRead(char *data,int length){
	int er = read(i2cHandle_,data,length); //Read "length" number of bytes into the "data" buffer from the I2C bus.
	return er;
}
int Pi2c::i2cWrite(char *data,int length){
	int er = write(i2cHandle_,data,length);//Write "length" number of bytes from the "data" buffer to the I2C bus.
	return er;
}

int Pi2c::i2cReadArduinoInt(){
	const int arr_size = 2;
	char tmp[arr_size]; //We know an Arduino Int is 2 Bytes.
	int retval=-1;
	
	if (i2cRead(tmp,arr_size) > 0){
		retval = tmp[1] << 8 | tmp[0]; //Using bit shifting, turn the 2 byte array into an Int.
	}
	return retval;
}

int Pi2c::i2cWriteArduinoInt(int input){
	const int arr_size = 2;
	char tmp[arr_size]; //We know an Arduino Int is 2 Bytes.
	int retval=0;
	
	tmp[0] = input; //get lowest 8 bits into the first part of the array;
	tmp[1] = input >> 8; //get the highest 8 bits into the second part of the array;
	retval = (i2cWrite(tmp,arr_size) > 0);
	return retval;
}