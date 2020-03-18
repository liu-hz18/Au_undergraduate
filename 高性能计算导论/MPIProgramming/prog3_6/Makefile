default: matvectmul
CC = mpicxx
CFLAGS = -O3
CLIBS = 
p = 16
n = 100
matvectmul: prog3_6.o
	$(CC) $(CLIBS) prog3_6.o -o matvectmul
prog3_6.o: prog3_6.cpp
	$(CC) $(CFLAGS) -c prog3_6.cpp -o prog3_6.o
clean:
	rm -rf ./*.o matvectmul
run:
	srun -n $(p) -l matvectmul $(n)