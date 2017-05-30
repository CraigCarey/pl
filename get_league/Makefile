CC=g++
LDLIBS=-lboost_system -lpthread
CXX_FLAGS=-std=c++11 -Wall -g --coverage
INC=-I/usr/include/boost

all: getLeagueBoost jsonParser

getLeagueBoost:
	$(CC) $(CXX_FLAGS) $(INC) $@.cpp -o $@ $(LDLIBS)

jsonParser:
	$(CC) $(CXX_FLAGS) $@.cpp -o $@

clean:
	rm -f getLeagueBoost jsonParser a.out *.d *.o *.gc*

.PHONY: all clean getLeagueBoost jsonParser