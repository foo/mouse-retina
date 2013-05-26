CC=mpic++
BOOST=-lboost_filesystem -lboost_system -lboost_program_options
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin
LIB=$(BIN)/traverser-module.o $(BIN)/config-module.o

all: traverser-client.cpp
	$(CC) traverser-client.cpp $(LIB) $(FLAGS) -o $(BIN)/traverser-client
