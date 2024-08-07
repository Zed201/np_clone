CC=g++
DIR=./src
FLAGS= -Wall -Wextra -Werror

SRC = $(DIR)/matrix.cpp $(DIR)/aux.cpp
OBJS = $(SRC:.cpp=.o)

run: a.out
	./a.out

a.out: $(OBJS) index.cpp
	$(CC) $(FLAGS) -o $@ $^

%.o: %.cpp
	$(CC) -c %< -o $(DIR)/%@

cls:
	rm -f $(OBJS) a.out