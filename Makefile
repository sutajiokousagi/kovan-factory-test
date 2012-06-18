SOURCES=test.c fpga.c harness.c \
	 test-serial.c test-audio.c test-usb.c test-io.c \
	 test-servo.c test-accel.c test-wifi.c
EXEC=test
OBJECTS=$(SOURCES:.c=.o)
MY_CFLAGS += -Wall -Werror -O0 -g `pkg-config alsa --cflags` `pkg-config libcurl --cflags`
MY_LIBS += -lpthread `pkg-config alsa --libs` `pkg-config libcurl --libs`

all: $(OBJECTS)
	$(CC) $(LIBS) $(LDFLAGS) $(OBJECTS) $(MY_LIBS) -o $(EXEC)

clean:
	rm -f $(EXEC) $(OBJECTS)

.c.o:
	$(CC) -c $(CFLAGS) $(MY_CFLAGS) $< -o $@

