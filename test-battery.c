#include "fpga.h"
#include "harness.h"
int test_battery(void) {
	harness_info(0, "Battery level: %d", read_battery());

	return 0;
}
