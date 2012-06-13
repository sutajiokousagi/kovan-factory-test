#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "harness.h"

#define EXT_DEV_NAME "/dev/ttyS2"
#define INT_DEV_NAME "/dev/ttyS0"

int test_serial(void) {
	int ext_fd = 0;
	int int_fd = 0;
	int ret = 0;

	ext_fd = open(EXT_DEV_NAME, O_RDWR);
	if (-1 == ext_fd) {
		harness_error(0, "Unable to open external serial port: %s", strerror(errno));
		ret = 1;
		goto out;
	}


	int_fd = open(INT_DEV_NAME, O_RDWR);
	if (-1 == int_fd) {
		harness_error(1, "Unable to open internal serial port: %s", strerror(errno));
		ret = 1;
		goto out;
	}


	harness_info(5, "Serial test passed");

out:
	if (ext_fd)
		close(ext_fd);
	if (int_fd)
		close(int_fd);

	return ret;
}
