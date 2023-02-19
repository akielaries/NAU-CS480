CC 		= gcc
DEBUG	= -g
CFLAGS	= -Wall -std=c99 -pedantic -c $(DEBUG)
LFLAGS	= -std=c99 -Wall -pedantic $(DEBUG)

simulator: driver.o simulator.o strutils.o metadataops.o configops.o simtimer.o
	$(CC) $(LFLAGS) driver.o \
					simulator.o \
					configops.o \
					strutils.o \
					metadataops.o \
					simtimer.o \
					-o sim02 -lpthread

driver.o: driver.c
	$(CC) $(CFLAGS) driver.c

sim.o: simulator.c simulator.h
	$(CC) $(CFLAGS) simulator.c

strutils.o: strutils.c strutils.h
	$(CC) $(CFLAGS) strutils.c

metadataops.o: metadataops.c metadataops.h
	$(CC) $(CFLAGS) metadataops.c 

configops.o: configops.c configops.h
	$(CC) $(CFLAGS) configops.c 

simtimer.o: simtimer.c simtimer.h
	$(CC) $(CFLAGS) simtimer.c

run:
	./sim02


clean:
	rm -f *.o sim02

