CC=g++
LDLIBS=-lboost_system -lpthread
CXX_FLAGS=-std=c++11 -Wall -g --coverage
INC=-I/usr/include/boost

all: leaguePrinter

leaguePrinter:
	$(CC) $(CXX_FLAGS) $(INC) $@.cpp -o $@ $(LDLIBS)

clean:
	rm -f leaguePrinter a.out *.d *.o *.gc*

.PHONY: all clean leaguePrinter