MODULES=cube dataset config dataset_files coord cross-section

CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)
BIN=../../bin

OBJS:=$(addprefix $(BIN)/,$(MODULES:=.o))

all: $(OBJS)

$(BIN)/cross-section.o: cross-section.hpp cross-section.cpp
	$(CC) -c cross-section.cpp $(FLAGS) -o $(BIN)/cross-section.o

$(BIN)/cube.o: cube.hpp cube.cpp
	$(CC) -c cube.cpp $(FLAGS) -o $(BIN)/cube.o

$(BIN)/dataset.o: dataset.hpp dataset.cpp
	$(CC) -c dataset.cpp $(FLAGS) -o $(BIN)/dataset.o

$(BIN)/config.o: config.hpp config.cpp
	$(CC) -c config.cpp $(FLAGS) -o $(BIN)/config.o

$(BIN)/dataset_files.o: dataset_files.hpp dataset_files.cpp
	$(CC) -c dataset_files.cpp $(FLAGS) -o $(BIN)/dataset_files.o

$(BIN)/coord.o: coord.hpp coord.cpp
	$(CC) -c coord.cpp $(FLAGS) -o $(BIN)/coord.o

