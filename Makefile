CC=g++
DIR=./src

SRC = $(DIR)/aux.cpp $(DIR)/matrix.cpp
OBJS = $(SRC:.cpp=.o)

all: a.out
	./a.out

a.out: index.cpp $(OBJS)
	$(CC) -o $@ $^

%.o: %.cpp %.h $(DIR)/defines.h 
	$(CC) -c $< -o $@

cls:
	rm -f $(OBJS) a.out