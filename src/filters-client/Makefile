CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin
LIB=$(BIN)/dataset-module.o $(BIN)/image-module.o $(BIN)/filters-module.o

all: filters-client.cpp
	$(CC) filters-client.cpp $(LIB) $(FLAGS) -o $(BIN)/filters-client
