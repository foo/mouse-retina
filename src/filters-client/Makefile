CC=g++
BOOST=-lboost_filesystem -lboost_system -lboost_program_options
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin
LIB=$(BIN)/dataset-module.o $(BIN)/image-module.o $(BIN)/filters-module.o $(BIN)/config-module.o

all: filters-client.cpp
	$(CC) filters-client.cpp $(LIB) $(FLAGS) -o $(BIN)/filters-client
