SOURCES=test.c test-io.c test-servo.c fpga.c harness.c
EXEC=test
#SOURCES=test-servo.c fpga.c harness.c
#EXEC=test-servo
OBJECTS=$(SOURCES:.c=.o)
MY_CFLAGS += -Wall -Werror -O0 -g
MY_LIBS += 

all: $(OBJECTS)
	$(CC) $(LIBS) $(LDFLAGS) $(OBJECTS) $(MY_LIBS) -o $(EXEC)

clean:
	rm -f $(EXEC) $(OBJECTS)

.c.o:
	$(CC) -c $(CFLAGS) $(MY_CFLAGS) $< -o $@

