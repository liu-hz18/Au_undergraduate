default: prod_cons1
CC = g++
CFLAGS = -O3
CLIBS = -pthread

prod_cons1: prod_cons1.o
	$(CC) $(CLIBS) prod_cons1.o -o prod_cons1
prod_cons1.o: prog4_7.cpp
	$(CC) $(CFLAGS) -c prog4_7.cpp -o prod_cons1.o
clean:
	rm -rf ./*.o prod_cons1
run:
	./prod_cons1
