default: prod_cons2
CC = g++
CFLAGS = -O3
CLIBS = -pthread
n = 10

prod_cons2: prod_cons2.o
	$(CC) $(CLIBS) prod_cons2.o -o prod_cons2
prod_cons2.o: prog4_7.cpp
	$(CC) $(CFLAGS) -c prog4_7.cpp -o prod_cons2.o
clean:
	rm -rf ./*.o prod_cons2
run:
	./prod_cons2 $(n) 
