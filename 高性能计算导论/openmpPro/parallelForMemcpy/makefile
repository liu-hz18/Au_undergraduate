default: test
CC = g++
CFLAGS = -std=c++11 -O3 -march=native -fopenmp
CLIBS = -fopenmp
p = 8
n = 1000000

test: test.o
	$(CC) $(CLIBS) test.o -o test
test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp -o test.o
debug: test.cpp
	$(CC) $(CFLAGS) test.cpp -DDEBUG -o test
clean:
	rm -rf ./*.o test
run:
	./test $(p) $(n)
