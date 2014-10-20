#include "pi2c.h"

pi2c::pi2c(int address, bool rev0){
	char filename[11] = "/dev/i2c-";
	if (rev0 == true){
		filename[9] = '0';
	}
	else {
		filename[9] = '1';
	}
	filename[10] = 0; //Add the null character onto the end of the array to make it a string
	
	i2cHandle = open(filename, O_RDWR); //Open the i2c file descriptor in read/write mode
	if (i2cHandle < 0) {
		//return 1;
		std::cout << "Can't open I2C BUS" << std::endl; //If there's an error opening this, then display it.
	}
	if (ioctl(i2cHandle, I2C_SLAVE, address) < 0) { //Using ioctl set the i2c device to talk to address in the "addr" variable.
		std::cout << "Can't set the I2C address for the slave device" << std::endl;
	}
}


int pi2c::i2cRead(char *data,int length){
	int er = read(i2cHandle,data,length); 
	return er;
}
int pi2c::i2cWrite(char *data,int length){
	int er = write(i2cHandle,data,length);
	return er;
}

int pi2c::i2cReadArduinoInt(){
	const int arr_size = 2;
	char tmp[arr_size]; //We know an Arduino Int is 2 Bytes.
	int retval=-1;
	
	if (i2cRead(tmp,arr_size) > 0){
		retval = tmp[1] << 8 | tmp[0];
	}
	return retval;
}

int pi2c::i2cWriteArduinoInt(int input){
	const int arr_size = 2;
	char tmp[arr_size]; //We know an Arduino Int is 2 Bytes.
	int retval=0;
	
	tmp[0] = input; //get lowest 8 bits into the first part of the array;
	tmp[1] = input >> 8; //get the highest 8 bits into the second part of the array;
	if (i2cRead(tmp,arr_size) > 0){
		retval = tmp[1] << 8 | tmp[0];
	}
	return retval;
}