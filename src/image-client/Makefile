CC=g++
BOOST=-lboost_filesystem -lboost_system -lboost_program_options
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin
LIB=$(BIN)/image-module.o $(BIN)/dataset-module.o $(BIN)/config-module.o

all: $(BIN)/image-client $(BIN)/image-client2

$(BIN)/image-client: image-client.cpp
	$(CC) image-client.cpp $(LIB) $(FLAGS) -o $(BIN)/image-client

$(BIN)/image-client2: image-client2.cpp
	$(CC) image-client2.cpp $(LIB) $(FLAGS) -o $(BIN)/image-client2
