CC=g++
DIR=./src
FLAGS= -Wall -Wextra -Werror

SRC = $(DIR)/aux.cpp $(DIR)/matrix.cpp
OBJS = $(SRC:.cpp=.o)
DEFINES = $(SRC:.cpp=.h)

run: a.out
	./a.out

a.out: $(OBJS) index.cpp 
	$(CC) $(FLAGS) -o $@ $^

com: $(OBJS) index.cpp
	$(CC) $(FLAGS) -o a.out $^

%.o: %.cpp
	$(CC) -c $< -o $@

cls:
	rm -f $(OBJS) a.out