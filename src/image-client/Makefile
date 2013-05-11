CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin
LIB=$(BIN)/grid.o $(BIN)/image.o $(BIN)/coord.o $(BIN)/cube.o

all: image-client.cpp
	$(CC) image-client.cpp $(LIB) $(FLAGS) -o $(BIN)/image-client
