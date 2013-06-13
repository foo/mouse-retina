CC=g++
BOOST=-L/usr/local/boost-build/boost/bin.v2/libs -lboost_system -lboost_program_options -lboost_filesystem
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin
LIB=$(BIN)/image-module.o $(BIN)/filters-module.o $(BIN)/edge-detection-module.o $(BIN)/config-module.o $(BIN)/utils-module.o $(BIN)/dataset-module.o

all: edge-detection-client.cpp
	$(CC) edge-detection-client.cpp $(LIB) -o $(BIN)/edge-detection-client $(FLAGS) 
