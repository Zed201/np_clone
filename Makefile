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

clean:
	rm -f $(OBJS) a.out test.o tests.o

dbg: a.out
	valgrind ./a.out


GTESTS_FLAGS = -Lgoogletest/build/lib -lgtest -lgtest_main -pthread 

tests: tests.cpp $(OBJS)
	$(CC) tests.cpp $(OBJS) $(CFLAGS) $(GTESTS_FLAGS) -o tests.o
	./tests.o --gtest_color=yes

test: test.cpp $(OBJS)
	$(CC) test.cpp $(OBJS) $(CFLAGS) -o test.o
	# valgrind ./test.o
	./test.o
