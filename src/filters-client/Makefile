CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin
LIB=$(BIN)/grid.o $(BIN)/image.o $(BIN)/coord.o $(BIN)/cube.o $(BIN)/pgm-export.o $(BIN)/from-grid.o $(BIN)/dataset.o

all: filters-client.cpp
	$(CC) filters-client.cpp $(LIB) $(FLAGS) -o $(BIN)/filters-client
