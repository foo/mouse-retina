CC=g++
BOOST=-lboost_filesystem -lboost_system
FLAGS=-Wall -std=c++0x $(BOOST)

all: geometry.o skeleton_simplifier.o

geometry.o: geometry.hpp geometry.cpp
	$(CC) -c geometry.cpp $(FLAGS) -o geometry.o

skeleton_simplifier.o: skeleton_simplifier.hpp skeleton_simplifier.cpp
	$(CC) -c skeleton_simplifier.cpp $(FLAGS) -o skeleton_simplifier.o

