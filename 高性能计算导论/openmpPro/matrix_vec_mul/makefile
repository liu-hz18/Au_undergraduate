default: mat_vec_mul
CC = g++
CFLAGS = -O3 -fopenmp
CLIBS = -fopenmp
p = 4
n = 1000

mat_vec_mul: mat_vec_mul.o
	$(CC) $(CLIBS) mat_vec_mul.o -o mat_vec_mul
mat_vec_mul.o: mat_vec_mul.cpp timer.h
	$(CC) $(CFLAGS) -c mat_vec_mul.cpp -o mat_vec_mul.o
debug: mat_vec_mul.cpp timer.h
	$(CC) $(CFLAGS) mat_vec_mul.cpp -DDEBUG -o mat_vec_mul
clean:
	rm -rf ./*.o mat_vec_mul
run:
	./mat_vec_mul $(p) $(n)
