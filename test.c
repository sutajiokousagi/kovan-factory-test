#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "harness.h"

int test_servo(void);
int test_io(void);

struct tests {
	int (*func)(void);
	char *name;
};

static struct tests tests[] = {
	{
		.func = test_io,
		.name = "Digital I/O",
	},
	{
		.func = test_servo,
		.name = "ADC and servos",
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
			char bfr[512];
			test_to_run = strtoul(*argv, NULL, 0);
			if (test_to_run > (sizeof(tests) / sizeof(*tests))) {
				harness_error(test_to_run, "Test is out of range!");
				argv++;
				continue;
			}
			snprintf(bfr, sizeof(bfr)-1, "Starting test \"%s\"",
				 tests[test_to_run].name);
			harness_info(test_to_run, bfr);
			tests[test_to_run].func();
			argv++;
		}
	}

	else {
		char bfr[512];
		snprintf(bfr, sizeof(bfr)-1, "Running %d tests",
			 (sizeof(tests) / sizeof(*tests)));
		harness_info(0, bfr);

		for (test_to_run = 0;
		     test_to_run < (sizeof(tests) / sizeof(*tests));
		     test_to_run++) {
			snprintf(bfr, sizeof(bfr)-1, "Starting test \"%s\"",
				 tests[test_to_run].name);
			harness_info(test_to_run, bfr);
			tests[test_to_run].func();
		}
	}
	return 0;
}
