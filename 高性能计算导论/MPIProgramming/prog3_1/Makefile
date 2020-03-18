default: histodist
CC = mpiicc
CFLAGS = -O3
CLIBS = 
p = 4
histodist: prog3_1.o
	$(CC) $(CLIBS) prog3_1.o -o histodist
prog3_1.o: prog3_1_histo_dist.c
	$(CC) $(CFLAGS) -c prog3_1_histo_dist.c -o prog3_1.o
clean:
	rm -rf ./*.o histodist
run:
	srun -n $(p) -l ./histodist
