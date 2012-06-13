#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#define RESET		0
#define BRIGHT 		1
#define DIM		2
#define UNDERLINE 	3
#define BLINK		4
#define REVERSE		7
#define HIDDEN		8

#define BLACK 		0
#define RED		1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define	WHITE		7


static void text_color(int attr, int fg, int bg)
{	char command[15];

	/* Command is the control command to the terminal */
	snprintf(command, sizeof(command)-1, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

void harness_error(uint32_t code, char *fmt, ...) {
	va_list ap;

	text_color(BLINK, WHITE, RED);
	printf("ERROR");
	text_color(RESET, WHITE, BLACK);
	printf(" ");
	text_color(BRIGHT, BLUE, BLACK);
	printf("%d", code);
	text_color(RESET, WHITE, BLACK);
	printf(" ");


	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	text_color(RESET, WHITE, BLACK);
}

void harness_info(uint32_t code, char *fmt, ...) {
	va_list ap;

	text_color(BRIGHT, BLACK, GREEN);
	printf("INFO");
	text_color(RESET, WHITE, BLACK);
	printf(" ");
	text_color(BRIGHT, BLUE, BLACK);
	printf("%d", code);
	text_color(RESET, WHITE, BLACK);
	printf(" ");

	
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	text_color(RESET, WHITE, BLACK);
}


void harness_debug(uint32_t code, char *fmt, ...) {
	va_list ap;

	text_color(BRIGHT, WHITE, BLUE);
	printf("ERROR");
	text_color(RESET, WHITE, BLACK);
	printf(" ");
	text_color(BRIGHT, BLUE, BLACK);
	printf("%d", code);
	text_color(RESET, WHITE, BLACK);
	printf(" ");


	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	text_color(RESET, WHITE, BLACK);
}
