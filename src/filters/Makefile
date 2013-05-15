CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin

all: $(BIN)/sobel.o $(BIN)/gaussian.o $(BIN)/box.o $(BIN)/sharpen.o $(BIN)/threshold.o $(BIN)/dilation.o

$(BIN)/threshold.o: threshold.hpp threshold.cpp
	$(CC) -c threshold.cpp $(FLAGS) -o $(BIN)/threshold.o

$(BIN)/dilation.o: dilation.hpp dilation.cpp
	$(CC) -c dilation.cpp $(FLAGS) -o $(BIN)/dilation.o

$(BIN)/sharpen.o: sharpen.hpp sharpen.cpp
	$(CC) -c sharpen.cpp $(FLAGS) -o $(BIN)/sharpen.o

$(BIN)/box.o: box.hpp box.cpp
	$(CC) -c box.cpp $(FLAGS) -o $(BIN)/box.o

$(BIN)/sobel.o: sobel.hpp sobel.cpp
	$(CC) -c sobel.cpp $(FLAGS) -o $(BIN)/sobel.o

$(BIN)/gaussian.o: gaussian.hpp gaussian.cpp
	$(CC) -c gaussian.cpp $(FLAGS) -o $(BIN)/gaussian.o
