#include "pi2c.h"

pi2c::pi2c(int address){
	//filename - need to autodetect which i2c bus to use.
	char filename[] = "/dev/i2c-0";
	i2cHandle = open(filename, O_RDWR); //Open the i2c file descriptor in read/write mode
	if (i2cHandle < 0) {
		//return 1;
		std::cout << "Can't open I2C BUS" << std::endl; //If there's an error opening this, then display it.
	}
	if (ioctl(i2cHandle, I2C_SLAVE, address) < 0) { //Using ioctl set the i2c device to talk to address in the "addr" variable.
		std::cout << "Can't set the I2C address for the slave device" << std::endl;
	}
}

int pi2c::i2cRead(char *data){
	int length = sizeof(data);
	int er = read(i2cHandle,data,length); //Need to work out how many bytes to read - possibly one at a time and add them to the full array.
	return er;
}
int pi2c::i2cWrite(char *data){
	int length = sizeof(data);
	int er = write(i2cHandle,data,length);
	return er;
}