CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin
LIB=$(BIN)/cube.o $(BIN)/dataset.o $(BIN)/config.o $(BIN)/dataset_files.o $(BIN)/coord.o

all: dataset-client.cpp
	$(CC) dataset-client.cpp $(LIB) $(FLAGS) -o $(BIN)/dataset-client
