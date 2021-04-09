CC=gcc
CFLAGS= -O3 -march=native


all: main

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $^

main: node0.o node1.o node2.o node3.o prog3.c
	$(CC) $(CFLAGS) -o $@ $^

clean: #make clean to run
	rm *.o *.h.gch main