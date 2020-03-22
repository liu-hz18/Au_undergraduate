default: prog2
CC = g++
CFLAGS = -O3 -pthread
CLIBS = -pthread

prog2: prog2.o
	$(CC) $(CLIBS) prog2.o -o prog2
prog2.o: prog2.cpp timer.h
	$(CC) $(CFLAGS) -c prog2.cpp -o prog2.o
debug: prog2.cpp timer.h
	$(CC) $(CFLAGS) prog2.cpp -DDEBUG -o prog2
clean:
	rm -rf ./*.o prog2
run:
	./prog2
