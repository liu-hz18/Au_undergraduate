default: matvectmul
CC = mpicxx
CFLAGS = -O3
CLIBS = 
p = 4
n = 12
matvectmul: prog3_5.o
	$(CC) $(CLIBS) prog3_5.o -o matvectmul
prog3_5.o: prog3_5.cpp
	$(CC) $(CFLAGS) -c prog3_5.cpp -o prog3_5.o
clean:
	rm -rf ./*.o matvectmul
run:
	srun -n $(p) -l ./matvectmul $(n)