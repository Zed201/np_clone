CC=g++
DIR=./src
MAIN=test

CFLAGS=-Wall -Wfatal-errors -Wextra -fopenmp
SRC = $(DIR)/aux.cpp $(DIR)/matrix.cpp
OBJS = $(SRC:.cpp=.o)

all: a.out
	./a.out

a.out: $(MAIN).cpp $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp %.h $(DIR)/defines.h 
	$(CC) $(CFLAGS) -c $< -o $@

cls:
	rm -f $(OBJS) a.out

dbg: a.out
	valgrind ./a.out