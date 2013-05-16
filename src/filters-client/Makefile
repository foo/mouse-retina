CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin
LIB=$(BIN)/grid.o $(BIN)/image.o $(BIN)/coord.o $(BIN)/cube.o $(BIN)/pgm-export.o $(BIN)/cross-section.o $(BIN)/dataset_files.o $(BIN)/sobel.o $(BIN)/gaussian.o $(BIN)/box.o $(BIN)/sharpen.o $(BIN)/threshold.o $(BIN)/dilation.o $(BIN)/binary-operations.o

all: filters-client.cpp
	$(CC) filters-client.cpp $(LIB) $(FLAGS) -o $(BIN)/filters-client
