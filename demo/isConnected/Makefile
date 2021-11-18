platform = x86
CC = g++
CFLAGS = -ludev
LDFLAGS = -shared

all:filterwheel
filterwheel: main.cpp
	$(CC) main.cpp -o filterwheel $(CFLAGS) ../../lib/$(platform)/libEFWFilter.a -I../../include $(CFLAGS) -lpthread
	cp filterwheel bin/$(platform)/
clean:
	rm -f filterwheel


