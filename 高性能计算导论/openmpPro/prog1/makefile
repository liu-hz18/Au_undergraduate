default: prog3
CC = g++
CFLAGS = -O3 -fopenmp
CLIBS = -fopenmp

prog3: prog3.o
	$(CC) $(CLIBS) prog3.o -o prog3
prog3.o: prog3.cpp timer.h
	$(CC) $(CFLAGS) -c prog3.cpp -o prog3.o
debug: prog3.cpp timer.h
	$(CC) $(CFLAGS) prog3.cpp -DDEBUG -o prog3
clean:
	rm -rf ./*.o prog3
run:
	./prog3
