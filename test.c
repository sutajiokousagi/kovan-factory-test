int test_servo(void);
int test_io(void);

int main(int argc, char **argv) {
	test_io();
	test_servo();
	return 0;
}
