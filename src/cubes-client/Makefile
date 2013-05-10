CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin
LIB=$(BIN)/cube.o $(BIN)/grid.o $(BIN)/config.o $(BIN)/dataset.o

all: cubes-client.cpp
	$(CC) cubes-client.cpp $(LIB) $(FLAGS) -o $(BIN)/cubes-client
