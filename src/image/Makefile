CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin

all: $(BIN)/image.o $(BIN)/from-grid.o $(BIN)/pgm-export.o

$(BIN)/image.o: image.hpp image.cpp
	$(CC) -c image.cpp $(FLAGS) -o $(BIN)/image.o

$(BIN)/pgm-export.o: pgm-export.hpp pgm-export.cpp $(BIN)/image.o $(BIN)/grid.o $(BIN)/cube.o
	$(CC) -c pgm-export.cpp $(FLAGS) -o $(BIN)/pgm-export.o

$(BIN)/from-grid.o: from-grid.hpp from-grid.cpp $(BIN)/image.o
	$(CC) -c from-grid.cpp $(FLAGS) -o $(BIN)/from-grid.o
