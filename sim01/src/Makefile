CC 		= gcc
DEBUG	= -g
CFLAGS	= -Wall -std=c99 -pedantic -c $(DEBUG)
LFLAGS	= -std=c99 -Wall -pedantic $(DEBUG)

simulator: driver.o sim.o strutils.o
	$(CC) $(LFLAGS) driver.o \
					sim.o \
					strutils.o \
					-o sim01
driver.o: driver.c
	$(CC) $(CFLAGS) driver.c

sim.o: sim.c sim.h
	$(CC) $(CFLAGS) sim.c

strutils.o: strutils.c strutils.h
	$(CC) $(CFLAGS) strutils.c

run:
	./sim01


clean:
	rm -f *.o sim01

