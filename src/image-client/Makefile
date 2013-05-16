CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin
LIB=$(BIN)/image-module.o $(BIN)/dataset-module.o

all: image-client.cpp
	$(CC) image-client.cpp $(LIB) $(FLAGS) -o $(BIN)/image-client
