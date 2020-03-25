
CC = g++
STAND = -std=c++17
FPIC = -fPIC -c
SHARED = -shared -o

SRC_OBJCET = AI.cpp Judge.cpp Strategy.cpp utils.cpp
H_OBJCET = AI.h Judge.h Node.h Point.h Strategy.h Timer.h utils.h
OBJECT = AI.o Judge.o Strategy.o utils.o
LIB_OBJCET = Strategy.dll

$(LIB_OBJCET): $(OBJECT)
	$(CC) $(OBJECT) $(SHARED) -fPIC -o $(LIB_OBJCET)

$(OBJECT): $(SRC_OBJCET) $(H_OBJCET)
	$(CC) $(STAND) $(FPIC) $(SRC_OBJCET)

.PHONY: clean
clean:
	rm -rf $(OBJECT) $(LIB_OBJCET)

