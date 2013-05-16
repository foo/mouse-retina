CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin

all: $(BIN)/image.o $(BIN)/pgm-export.o $(BIN)/binary-operations.o

$(BIN)/image.o: image.hpp image.cpp
	$(CC) -c image.cpp $(FLAGS) -o $(BIN)/image.o

$(BIN)/binary-operations.o: binary-operations.hpp binary-operations.cpp
	$(CC) -c binary-operations.cpp $(FLAGS) -o $(BIN)/binary-operations.o

$(BIN)/pgm-export.o: pgm-export.hpp pgm-export.cpp $(BIN)/image.o $(BIN)/grid.o $(BIN)/cube.o
	$(CC) -c pgm-export.cpp $(FLAGS) -o $(BIN)/pgm-export.o
