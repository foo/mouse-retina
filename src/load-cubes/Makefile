CC=g++
FLAGS=-Wall -std=c++0x
BIN=../../bin

all: $(BIN)/cube.o $(BIN)/grid.o $(BIN)/config.o

$(BIN)/cube.o: cube.hpp cube.cpp
	$(CC) -c cube.cpp $(FLAGS) -o $(BIN)/cube.o

$(BIN)/grid.o: grid.hpp grid.cpp $(BIN)/cube.o
	$(CC) -c grid.cpp $(FLAGS) -o $(BIN)/grid.o

$(BIN)/config.o: config.hpp config.cpp $(BIN)/grid.o
	$(CC) -c config.cpp $(FLAGS) -o $(BIN)/config.o

