MODULE=traverser-module
SUBMODULES=worker manager

CC=mpic++
FLAGS=-Wall -std=c++0x
BIN=../../bin

SUBMODULE_OBJS:=$(SUBMODULES:=.o)
MODULE_OBJ=$(BIN)/$(MODULE).o

$(MODULE_OBJ): $(SUBMODULE_OBJS)
	ld -r $^ -o $@

$(SUBMODULE_OBJS): %.o: %.cpp %.hpp
	$(CC) -c $< $(FLAGS) -o $@

clean:
	rm -f $(SUBMODULE_OBJS)
