default: matvectmul
CC = mpicxx
CFLAGS = -std=c++11 -O3 -march=native -fopenmp
#CFLAGS = -std=c++11 -O2 -fopenmp
CLIBS = -fopenmp
p = 4
n = 3600
t = 8
matvectmul: prog3_6.o
	$(CC) $(CLIBS) prog3_6.o -o matvectmul
prog3_6.o: prog3_6.cpp
	$(CC) $(CFLAGS) -c prog3_6.cpp -o prog3_6.o
clean:
	rm -rf ./*.o matvectmul
run:
	srun -n $(p) -l matvectmul $(n) $(t)