default: vectoradd
CC = mpiicc
CFLAGS = -O3
CLIBS = 
p = 4
vectoradd: prog3_13.o
	$(CC) $(CLIBS) prog3_13.o -o vectoradd
prog3_13.o: mpi_vector_add.c
	$(CC) $(CFLAGS) -c mpi_vector_add.c -o prog3_13.o
clean:
	rm -rf ./*.o vectoradd
run:
	srun -n $(p) -l ./vectoradd
