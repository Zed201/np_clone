# no arch é so instalar o c++ mais recente, mas no ubuntu por padrão ele não instala o mais recente, 
# então tem de instalar o g++-13, nesse caso so trocar o compilador
CC=g++-13
CFLAGS = -c -std=c++20
all: a.out
	./a.out

a.out: test.cpp matrix.o aux.o
	$(CC) test.cpp matrix.o aux.o -std=c++20

matrix.o: matrix.cpp
	$(CC) $(CFLAGS) matrix.cpp -o matrix.o

aux.o: aux.cpp aux.h
	$(CC) $(CFLAGS) aux.cpp -o aux.o

clean:
	rm -rf *.o a.out