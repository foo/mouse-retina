CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin

all: $(BIN)/geometry.o $(BIN)/graph.o $(BIN)/skeleton_simplifier.o

$(BIN)/geometry.o: geometry.hpp geometry.cpp 
	$(CC) -c geometry.cpp $(FLAGS) -o $(BIN)/geometry.o

$(BIN)/graph.o: graph.hpp graph.cpp
	$(CC) -c graph.cpp $(FLAGS) -o $(BIN)/graph.o
	
$(BIN)/skeleton_simplifier.o: skeleton_simplifier.hpp skeleton_simplifier.cpp
	$(CC) -c skeleton_simplifier.cpp $(FLAGS) -o $(BIN)/skeleton_simplifier.o

