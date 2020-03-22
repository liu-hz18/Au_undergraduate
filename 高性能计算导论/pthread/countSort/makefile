default: count_sort_omp
CC = g++
CFLAGS = -O3 -fopenmp -pthread
CLIBS = -fopenmp -pthread
p = 4
n = 1000

count_sort_omp: count_sort_omp.o
	$(CC) $(CLIBS) count_sort_omp.o -o count_sort_omp
count_sort_omp.o: count_sort_omp.cpp timer.h Thread.h Runnable.h
	$(CC) $(CFLAGS) -c count_sort_omp.cpp -o count_sort_omp.o
debug: count_sort_omp.cpp timer.h Thread.h Runnable.h
	$(CC) $(CFLAGS) count_sort_omp.cpp -DDEBUG -o count_sort_omp
clean:
	rm -rf ./*.o count_sort_omp
run:
	./count_sort_omp $(p) $(n)
