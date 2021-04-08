CC=gcc
CFLAGS= -O3 -march=native


all: main

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $^

main: prog3.o node0.c node1.c node2.c node3.c
	$(CC) $(CFLAGS) -o $@ $^

clean: #make clean to run
	rm *.o *.h.gch main