CC 		= gcc
DEBUG	= -g
CFLAGS = -Wall -std=c99 -pedantic -c $(DEBUG)
LFLAGS	= -std=c99 -Wall -pedantic $(DEBUG)

sim: main.o stringutils.o
	$(CC) $(LFLAGS) main.o \
					stringutils.o
					-o sim01
main.o: main.c
	$(CC) $(CFLAGS) main.c

stringutils.o: stringutils.c
	$(CC) $(CFLAGS) stringutils.c

run:
	./sim01


clean:
	rm -f *.o sim01

