CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin

all: $(BIN)/sobel.o $(BIN)/gaussian.o

$(BIN)/sobel.o: sobel.hpp sobel.cpp
	$(CC) -c sobel.cpp $(FLAGS) -o $(BIN)/sobel.o

$(BIN)/gaussian.o: gaussian.hpp gaussian.cpp
	$(CC) -c gaussian.cpp $(FLAGS) -o $(BIN)/gaussian.o
