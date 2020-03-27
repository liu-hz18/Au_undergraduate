
CC = g++
STAND = -std=c++11
CFLAGS = -O3
CLIBS = 
SRC_OBJECT = main.cpp
H_OBJECT = Edge.h Heap.h Vertex.h Graph.h
OBJECT = main

all: main

main: $(SRC_OBJECT) $(H_OBJECT)
	$(CC) $(STAND) $(CFLAGS) $(SRC_OBJECT) -o $(OBJECT)

.PHONY: clean
clean:
	rm -rf ./*.o main

run:
	./main
