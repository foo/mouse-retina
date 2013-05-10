CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin

all: $(BIN)/cube.o $(BIN)/grid.o $(BIN)/config.o $(BIN)/dataset.o

$(BIN)/cube.o: cube.hpp cube.cpp
	$(CC) -c cube.cpp $(FLAGS) -o $(BIN)/cube.o

$(BIN)/grid.o: grid.hpp grid.cpp $(BIN)/cube.o
	$(CC) -c grid.cpp $(FLAGS) -o $(BIN)/grid.o

$(BIN)/config.o: config.hpp config.cpp $(BIN)/grid.o
	$(CC) -c config.cpp $(FLAGS) -o $(BIN)/config.o

$(BIN)/dataset.o: dataset.hpp dataset.cpp $(BIN)/grid.o
	$(CC) -c dataset.cpp $(FLAGS) -o $(BIN)/dataset.o

