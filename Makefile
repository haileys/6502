CC=gcc
CFLAGS=-Wall -std=c99

all:
	$(CC) $(CFLAGS) *.c -o 6502

clean:
	rm -rf *.o 6502
