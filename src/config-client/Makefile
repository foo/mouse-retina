CC=g++
BOOST=-lboost_filesystem -lboost_system -lboost_program_options
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin
LIB=$(BIN)/config-module.o

all: config-client.cpp
	$(CC) config-client.cpp $(LIB) $(FLAGS) -o $(BIN)/config-client
