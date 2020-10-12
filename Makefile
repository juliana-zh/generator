CC=g++
CFLAGS=-c -Wall

all: gen

gen: main.o 
	$(CC) main.o -o gen

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *.o gen