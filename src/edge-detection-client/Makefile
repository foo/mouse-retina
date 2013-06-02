CC=g++
BOOST=-lboost_filesystem -lboost_system -lboost_program_options
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin
LIB=$(BIN)/dataset-module.o $(BIN)/image-module.o $(BIN)/filters-module.o $(BIN)/edge-detection-module.o $(BIN)/config-module.o

all: edge-detection-client.cpp
	$(CC) edge-detection-client.cpp $(LIB) $(FLAGS) -o $(BIN)/edge-detection-client
