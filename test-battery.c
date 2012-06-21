#include <unistd.h>
#include "fpga.h"
#include "harness.h"
int test_battery(void) {
	uint32_t battery_level;

	harness_info(0, "Waiting for operator to unplug AC...");
	for (battery_level = read_battery();
	     battery_level > 12000;
	     battery_level = read_battery()) {
		harness_info(0, "Battery level: %d mV", battery_level);
		usleep(100000);
	}

	harness_info(1, "Battery level: %d mV", battery_level);

	return 0;
}
