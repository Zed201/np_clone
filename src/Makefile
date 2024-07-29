# no arch é so instalar o c++ mais recente, mas no ubuntu por padrão ele não instala o mais recente, 
# então tem de instalar o g++-13, nesse caso so trocar o compilador
CPP_VERSION=$(shell g++ --version | grep "^g++" | cut -d' ' -f3)
MIN_VERSION=14.1.1
# no ubuntu tem de usar o g++-13, pois no g++ do ubuntu do wsl nao tem o format
# para adicionar ele usa o comando o `sudo add-apt-repository ppa:ubuntu-toolchain-r/test`
# depois só usar o `sudo apt install g++-13`
COMPARE_VERSION = $(shell printf "%s\n%s\n" $(1) $(2) | sort -V | head -n1)
ifeq ($(call COMPARE_VERSION, $(CPP_VERSION),$(MIN_VERSION)), 1)
	CC=g++
else
	CC=g++-13
endif

CFLAGS = -c -std=c++20
all: a.out
	@echo $(CC)
	./a.out

a.out: test.cpp matrix.o aux.o
	$(CC) test.cpp matrix.o aux.o -std=c++20

matrix.o: matrix.cpp
	$(CC) $(CFLAGS) matrix.cpp -o matrix.o

aux.o: aux.cpp aux.h
	$(CC) $(CFLAGS) aux.cpp -o aux.o

clean:
	rm -rf *.o a.out