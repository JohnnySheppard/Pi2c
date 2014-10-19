#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), */
#include <sys/ioctl.h>

class pi2c {
		int i2cHandle;
	public:
		pi2c(int);
		int i2cRead(char*);
		int i2cWrite(char*);
};