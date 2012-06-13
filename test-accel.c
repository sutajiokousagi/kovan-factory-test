#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include "harness.h"

#define ACCEL_ADDR 0x1d

static pthread_t i2c_thread;
static char *i2c_return_message;
static int i2c_return_code;
static int should_quit;


void *i2c_background(void *_ignored) {
	uint8_t start_reg = 0;
	int fd = open("/dev/i2c-1", O_RDWR);
	if (-1 == fd) {
		i2c_return_code = 2;
		i2c_return_message = "Unable to open I2C device";
		pthread_exit(NULL);
	}

	while (!should_quit) {
		char bfr[128];

		struct i2c_rdwr_ioctl_data packets;
		struct i2c_msg messages[2];

		messages[0].addr = ACCEL_ADDR;
		messages[0].flags = 0;
		messages[0].len = sizeof(start_reg);
		messages[0].buf = &start_reg;

		messages[1].addr = ACCEL_ADDR;
		messages[1].flags = I2C_M_RD;
		messages[1].len = sizeof(bfr);
		messages[1].buf = (void *)bfr;

		packets.msgs = messages;
		packets.nmsgs = 2;
		
		if(ioctl(fd, I2C_RDWR, &packets) < 0) {
			i2c_return_code = 1;
			i2c_return_message = "I2C failed";
			pthread_exit(NULL);
		}
	}
	return NULL;
}

int test_accel_start(void) {

	i2c_return_code = 0;
	i2c_return_message = "I2C stable";
	should_quit = 0;

	if (!pthread_create(&i2c_thread, NULL, i2c_background, NULL)) {
		harness_error(0, "Unable to create I2C thread");
		return 1;
	}
	harness_info(0, "Created I2C background thread");
	return 0;
}
