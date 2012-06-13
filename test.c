#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "harness.h"

extern int test_servo(void);
extern int test_io(void);
extern int test_usb(void);
extern int test_audio(void);
extern int test_serial(void);
extern int test_accel_start(void);
extern int test_accel_finish(void);


struct tests {
	int (*func)(void);
	char *name;
};



static struct tests tests[] = {
	{ // 0
		.func = test_accel_start,
		.name = "Begin background accelerometer read",
	},
	{ // 1
		.func = test_audio,
		.name = "Test audio generation",
	},
	{ // 2
		.func = test_serial,
		.name = "Test serial ports",
	},
	{ // 3
		.func = test_servo,
		.name = "ADC and servos",
	},
	{ // 4
		.func = test_io,
		.name = "Digital I/O",
	},
	{ // 5
		.func = test_usb,
		.name = "USB ports",
	},
	{ // 6
		.func = test_accel_finish,
		.name = "Read accelerometer result",
	},
};
	

int main(int argc, char **argv) {
	int test_to_run;

	if (argc > 1) {
		if (!strcmp(argv[1], "--help")
		 || !strcmp(argv[1], "-h")
		 || !strcmp(argv[1], "-?)")) {
			printf("Usage: %s [test-number]\n", argv[0]);
			return 1;
		}

		argv++;
		while (--argc > 0) {
			test_to_run = strtoul(*argv, NULL, 0);
			if (test_to_run > (sizeof(tests) / sizeof(*tests))) {
				harness_error(test_to_run,
				 "Test %d is out of range!  %d tests available.",
				test_to_run, (sizeof(tests)/sizeof(*tests)));
				argv++;
				continue;
			}
			harness_info(test_to_run, "Starting test \"%s\"",
				tests[test_to_run].name);
			tests[test_to_run].func();
			argv++;
		}
	}

	else {
		harness_info(0, "Running %d tests",
			 (sizeof(tests) / sizeof(*tests)));

		for (test_to_run = 0;
		     test_to_run < (sizeof(tests) / sizeof(*tests));
		     test_to_run++) {
			harness_begin(tests[test_to_run].name, test_to_run);
			tests[test_to_run].func();
		}
	}
	return 0;
}
