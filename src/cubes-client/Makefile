CC=g++
FLAGS=-Wall -std=c++0x
BIN=../../bin
LIB=$(BIN)/cube.o $(BIN)/grid.o $(BIN)/dataset.o

all: cubes-client.cpp
	$(CC) cubes-client.cpp $(LIB) $(FLAGS) -o $(BIN)/cubes-client
