CC=g++
LDLIBS=-lboost_system
CXX_FLAGS=-std=c++11 -Wall
INC=-I/usr/include/boost

getLeagueBoost:
	$(CC) $(CXX_FLAGS) $(INC) $@.cpp -o $@ $(LDLIBS)

clean:
	rm -f getLeagueBoost