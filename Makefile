CC=g++
DIR=./src
MAIN=index

CFLAGS=-Wall -Wfatal-errors -Wextra
SRC = $(DIR)/aux.cpp $(DIR)/matrix.cpp
OBJS = $(SRC:.cpp=.o)

all: a.out
	./a.out

a.out: $(MAIN).cpp $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp %.h $(DIR)/defines.h 
	$(CC) $(CFLAGS) -c $< -o $@

cl:
	rm -f $(OBJS) a.out

dbg: a.out
	valgrind ./a.out

test: test.cpp $(SRC) 
	$(CC) $(CFLAGS) test.cpp $(SRC) -o test
	./test 50
