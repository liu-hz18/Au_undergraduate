default: main
CC = g++
CFLAGS = -std=c++11 -O3 -lpthread
CLIBS = -lpthread
t = 10
n = 100

main: main.o
	$(CC) $(CLIBS) main.o -o main
main.o: main.cpp Mutex.h Locker.h orderedList.h Runnable.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o
debug: main.cpp Mutex.h Locker.h orderedList.h Runnable.h
	$(CC) $(CFLAGS) $(CLIBS) -DDEBUG main.cpp -o main
clean:
	rm -rf ./*.o main
run:
	./main $(t) $(n)