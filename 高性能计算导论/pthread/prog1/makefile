default: prog1
CC = g++
CFLAGS = -O3 -fopenmp
CLIBS = -fopenmp
n = 12

prog1: prog1.o
	$(CC) $(CLIBS) prog1.o -o prog1
prog1.o: prog1.cpp
	$(CC) $(CFLAGS) -c prog1.cpp -o prog1.o
debug:
	$(CC) $(CFLAGS) prog1.cpp -DDEBUG -o prog1
clean:
	rm -rf ./*.o prog1
run:
	./prog1 $(n)
