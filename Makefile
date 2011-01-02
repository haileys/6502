CC=gcc
CFLAGS=-Wall -std=c99 -Iinc -ldl

all:
	$(CC) $(CFLAGS) src/*.c -o 6502

clean:
	rm 6502
