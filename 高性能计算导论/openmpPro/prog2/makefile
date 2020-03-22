default: prog4
CC = g++
CFLAGS = -O3 -fopenmp
CLIBS = -fopenmp

prog4: prog4.o
	$(CC) $(CLIBS) prog4.o -o prog4
prog4.o: prog4.cpp timer.h
	$(CC) $(CFLAGS) -c prog4.cpp -o prog4.o
debug: prog4.cpp timer.h
	$(CC) $(CFLAGS) prog4.cpp -DDEBUG -o prog4
clean:
	rm -rf ./*.o prog4
run:
	./prog4
