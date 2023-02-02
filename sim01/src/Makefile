CC 		= gcc
DEBUG	= -g
CFLAGS	= -Wall -std=c99 -pedantic -c $(DEBUG)
LFLAGS	= -std=c99 -Wall -pedantic $(DEBUG)

simulator: driver.o sim.o strutils.o metadataops.o configops.o
	$(CC) $(LFLAGS) driver.o \
					sim.o \
					configops.o \
					strutils.o \
					metadataops.o \
					-o sim01
driver.o: driver.c 
	$(CC) $(CFLAGS) driver.c

sim.o: sim.c sim.h
	$(CC) $(CFLAGS) sim.c

strutils.o: strutils.c strutils.h
	$(CC) $(CFLAGS) strutils.c

metadataops.o: metadataops.c metadataops.h
	$(CC) $(CFLAGS) metadataops.c 

configops.o: configops.c configops.h
	$(CC) $(CFLAGS) configops.c 

run:
	./sim01


clean:
	rm -f *.o sim01

