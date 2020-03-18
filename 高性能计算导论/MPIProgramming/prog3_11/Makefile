default: prefixsum
CC = mpiicc
CFLAGS = -O3
CLIBS = 
p = 4
prefixsum: prog3_11.o
	$(CC) $(CLIBS) prog3_11.o -o prefixsum
prog3_11.o: mpi_prefix_sum.c
	$(CC) $(CFLAGS) -c mpi_prefix_sum.c -o prog3_11.o
debug:
	$(CC) mpi_prefix_sum.c -DDEBUG -o prefixsum
clean:
	rm -rf ./*.o prefixsum
run:
	srun -n $(p) -l ./prefixsum
