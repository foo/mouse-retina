CC=g++
FLAGS=-Wall -std=c++0x
BIN=../../bin

all: $(BIN)/cube.o $(BIN)/grid.o

$(BIN)/cube.o: cube.hpp cube.cpp $(BIN)/grid.o
	$(CC) -c cube.cpp $(FLAGS) -o $(BIN)/cube.o

$(BIN)/grid.o: grid.hpp grid.cpp
	$(CC) -c grid.cpp $(FLAGS) -o $(BIN)/grid.o

