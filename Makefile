CC=gcc
CFLAGS=-g -Wall -std=c99 -Iinc

all:
	$(CC) $(CFLAGS) src/*.c -o 6502
#	util/build

clean:
	rm 6502
