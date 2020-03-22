default: prod_cons3
CC = g++
CFLAGS = -O3
CLIBS = -pthread
n = 10

prod_cons3: prod_cons3.o
	$(CC) $(CLIBS) prod_cons3.o -o prod_cons3
prod_cons3.o: prog4_7.cpp
	$(CC) $(CFLAGS) -c prog4_7.cpp -o prod_cons3.o
clean:
	rm -rf ./*.o prod_cons3
run:
	./prod_cons3 $(n) 
