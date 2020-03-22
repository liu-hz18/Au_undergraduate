default: prog5_8
CC = g++
CFLAGS = -O3 -openmp
CLIBS = -openmp
n = 12

prog5_8: prog5_8.o
	$(CC) $(CLIBS) prog5_8.o -o prog5_8
prog5_8.o: prog5_8.cpp
	$(CC) $(CFLAGS) -c prog5_8.cpp -o prog5_8.o
clean:
	rm -rf ./*.o prog5_8
run:
	./prog5_8 $(n)
