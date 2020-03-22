default: main
CC = g++
CFLAGS = -O3 -fopenmp -pthread
CLIBS = -fopenmp -pthread
t = 4
n = 1000
b = 50

main: main.o
	$(CC) $(CLIBS) main.o -o main
main.o: main.cpp Mutex.h Locker.h Cond.h ThreadPool.h Runnable.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o
debug: main.cpp Mutex.h Locker.h Cond.h ThreadPool.h Runnable.h
	$(CC) $(CFLAGS) $(CLIBS) -DDEBUG main.cpp -o main
clean:
	rm -rf ./*.o main
run:
	./main $(t) $(n) $(b)