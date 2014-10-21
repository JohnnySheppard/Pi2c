// License:  This  program  is  free software; you can redistribute it and/or
// modify  it  under the terms of the GNU General Public License as published
// by  the  Free Software Foundation; either version 3 of the License, or (at
// your  option)  any  later version. This program is distributed in the hope
// that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty  of  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

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